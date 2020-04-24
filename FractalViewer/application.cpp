#include "application.h"

#include <iostream>
#include <windows.h>
#include "fractal_generator_factory.h"
#include "input_actions.h"
#include <imgui-SFML.h>
#include <imgui.h>

application::application(std::string app_name)
   : m_app_name(app_name)
   , m_resolution(sf::VideoMode::getDesktopMode())
   , m_window(m_resolution, m_app_name, sf::Style::Fullscreen)
   , m_render_time_ms(0)
   , m_state_changed(true)
   , m_julia_c{ -0.8, 0.156 }
   , m_renderer(m_resolution.width, m_resolution.height, fractal_generator_factory::create_mandelbrot_generator(m_resolution.width, m_resolution.height, get_selected_colour_palette(), get_selected_colour_algorithm()))
{
   m_renderer.set_fractal_zoom({
      1.0,
      static_cast<int32_t>(m_resolution.width) / 2,
      static_cast<int32_t>(m_resolution.height) / 2
   });
   m_renderer.set_fractal_resolution(m_fractal_resolution);
   m_window.setFramerateLimit(0); // May not need this eventually
   // Init ImGui
   ImGui::SFML::Init(m_window);
   // No SFML call for this so need to resort to windows specific code
   ::ShowWindow(m_window.getSystemHandle(), SW_MAXIMIZE);
   m_fractal_texture.create(m_resolution.width, m_resolution.height);
   m_fractal_texture.setSmooth(true);
}

application::~application()
{
   ImGui::SFML::Shutdown();
}

bool application::is_open() const
{
   return m_window.isOpen();
}

void application::update_gui()
{
   ImGui::SFML::Update(m_window, m_gui_clock.restart());
   ImGui::Begin("Render Controls"); // begin window
   // Render time
   std::stringstream ss;
   ss << std::to_string(m_render_time_ms) << "ms";
   ImGui::LabelText(ss.str().c_str(), "Render Time");
   /////////////////
   /// Core count
   std::stringstream core_ss;
   core_ss << std::to_string(m_renderer.core_count());
   ImGui::LabelText(core_ss.str().c_str(), "Core Count");
   /////////////////
   /// Zoom
   std::stringstream zoom_ss;
   zoom_ss << std::to_string(1.0/m_fractal_zoom);
   ImGui::LabelText(zoom_ss.str().c_str(), "Zoom Factor");
   /////////////////
   /// Resolution
   std::stringstream res_ss;
   res_ss << std::to_string(m_fractal_resolution);
   ImGui::LabelText(res_ss.str().c_str(), "Fractal Resolution");
   /////////////////
   /// Fractal bounds
   std::stringstream min_ss;
   auto min = m_renderer.get_bounds().min();
   min_ss << min.real() << " + " << min.imag() << "i";
   ImGui::LabelText(min_ss.str().c_str(), "Bounds Min");
   std::stringstream max_ss;
   auto max = m_renderer.get_bounds().max();
   max_ss << max.real() << " + " << max.imag() << "i";
   ImGui::LabelText(max_ss.str().c_str(), "Bounds Max");
   /////////////////
   /// Colour algo picker
   ImGui::LabelText("", "Colouring Algorithm");
   ImGui::SameLine();
   const char* algo_items[] = { "Escape Time", "Continuous Potential" };
   ImGui::Combo("colour_algo", &m_fractal_colouring_index, algo_items, IM_ARRAYSIZE(algo_items));
   /////////////////
   /// Colour palette picker
   ImGui::LabelText("", "Colour Palette");
   ImGui::SameLine();
   const char* palette_items[] = { "Default", "Rainbow" };
   ImGui::Combo("palette", &m_colour_palette_index, palette_items, IM_ARRAYSIZE(palette_items));
   /////////////////
   /// Fractal picker
   ImGui::LabelText("", "Fractal Generator");
   ImGui::SameLine();
   const char* generator_items[] = { "Mandelbrot", "Julia" };
   ImGui::Combo("fractal", &m_fractal_generator_index, generator_items, IM_ARRAYSIZE(generator_items));
   /////////////////
   /// Fractal paramaters
   switch (m_fractal_generator_index)
   {
   case 0:
      break; // Mandelbrot - no params
   case 1:
      ImGui::DragFloat2("C", m_julia_c, 0.001f, -10.0f, 10.0f);
      break; // Julia
   }

   /////////////////
   /// Reset Button
   if(ImGui::Button("Reset Bounds", {100, 30}))
   {
      m_renderer.reset();
      m_fractal_resolution = m_renderer.fractal_resolution();
      m_fractal_zoom = m_renderer.fractal_zoom().factor;
      m_state_changed = true;
   }
   /////////////////
   ImGui::End();
}

bool application::check_if_generator_changed() const
{
   return m_fractal_generator_index != m_last_fractal_generator_index;
}

void application::update_generator()
{
   switch (m_fractal_generator_index)
   {
   case 0:
      m_renderer.set_fractal_generator(fractal_generator_factory::create_mandelbrot_generator(m_resolution.width, m_resolution.height, get_selected_colour_palette(), get_selected_colour_algorithm()));
      m_renderer.set_fractal_resolution(m_fractal_resolution);
      break;
   case 1:
      m_renderer.set_fractal_generator(fractal_generator_factory::create_julia_generator(m_resolution.width, m_resolution.height, get_selected_colour_palette(), get_selected_colour_algorithm(), {m_julia_c[0], m_julia_c[1]}));
      m_renderer.set_fractal_resolution(m_fractal_resolution);
      break;
   default:
      break;
   }
}

bool application::check_if_colour_algorithm_changed() const
{
   return m_fractal_colouring_index != m_last_fractal_colouring_index;
}

void application::update_colour_algorithm()
{
   m_renderer.set_fractal_colour_algorithm(get_selected_colour_algorithm());
}

colouring::colour_algorithm_func_t application::get_selected_colour_algorithm() const
{
   switch (m_fractal_colouring_index)
   {
   case 0:
      return colouring::algorithm::escape_time;
   case 1:
      return colouring::algorithm::continuous_potential;
   default:
      break;
   }
}

bool application::check_if_colour_palette_changed() const
{
   return m_colour_palette_index != m_last_colour_palette_index;
}

void application::update_colour_palette()
{
   m_renderer.set_fractal_colour_palette(get_selected_colour_palette());
}

palette::colour_from_palette_func_t application::get_selected_colour_palette() const
{
   switch (m_colour_palette_index)
   {
   case 0:
      return palette::default_palette::get;
   case 1:
      return palette::rainbow::get;
   default:
      break;
   }
}

void application::zoom_in()
{
   m_fractal_zoom /= m_fractal_zoom_factor;
   const zoom_action zoom{ m_fractal_zoom, sf::Mouse::getPosition().x, sf::Mouse::getPosition().y };
   //std::cout << "Setting zoom factor " << m_fractal_zoom << " at (" << sf::Mouse::getPosition().x << "," << sf::Mouse::getPosition().y << ")" << std::endl;
   m_renderer.set_fractal_zoom(zoom);
   m_state_changed = true;
}

void application::zoom_out()
{
   m_fractal_zoom *= m_fractal_zoom_factor;
   if (m_fractal_zoom >= m_fractal_zoom_min)
   {
      m_fractal_zoom = m_fractal_zoom_min;
   }
   const zoom_action zoom{ m_fractal_zoom, sf::Mouse::getPosition().x, sf::Mouse::getPosition().y };
   //std::cout << "Setting zoom factor " << m_fractal_zoom << " at (" << sf::Mouse::getPosition().x << "," << sf::Mouse::getPosition().y << ")" << std::endl;
   m_renderer.set_fractal_zoom(zoom);
   m_state_changed = true;
}

void application::increase_fractal_res()
{
   m_fractal_resolution += m_fractal_res_delta;
   if (m_fractal_resolution >= m_fractal_res_max)
   {
      m_fractal_resolution = m_fractal_res_max;
   }
   //std::cout << "Increasing fractal resolution to " << m_fractal_resolution << std::endl;
   m_renderer.set_fractal_resolution(m_fractal_resolution);
   m_state_changed = true;
}

void application::decrease_fractal_res()
{
   m_fractal_resolution -= m_fractal_res_delta;
   if (m_fractal_resolution <= m_fractal_res_min)
   {
      m_fractal_resolution = m_fractal_res_min;
   }
   //std::cout << "Decreasing fractal resolution to " << m_fractal_resolution << std::endl;
   m_renderer.set_fractal_resolution(m_fractal_resolution);
   m_state_changed = true;
}

void application::handle_events()
{
   // Poll Events
   sf::Event event;
   while (m_window.pollEvent(event))
   {
      ImGui::SFML::ProcessEvent(event);
      switch (event.type)
      {
         case sf::Event::KeyPressed:
         {
            switch (event.key.code)
            {
               case sf::Keyboard::Q:
               {
                  decrease_fractal_res();
                  break;
               }
               case sf::Keyboard::E:
               {
                  increase_fractal_res();
                  break;
               }
               case sf::Keyboard::LBracket:
               {
                  zoom_out();
                  break;
               }
               case sf::Keyboard::RBracket:
               {
                  zoom_in();
                  break;
               }
               case sf::Keyboard::Left:
               {
                  const offset_action l_offset{ -1, 0 };
                  m_renderer.set_fractal_offset(l_offset);
                  m_state_changed = true;
                  break;
               }
               case sf::Keyboard::Right:
               {
                  const offset_action r_offset{ 1, 0 };
                  m_renderer.set_fractal_offset(r_offset);
                  m_state_changed = true;
                  break;
               }
               case sf::Keyboard::Up:
               {
                  const offset_action u_offset{ 0, 1 };
                  m_renderer.set_fractal_offset(u_offset);
                  m_state_changed = true;
                  break;
               }
               case sf::Keyboard::Down:
               {
                  const offset_action offset{ 0, -1 };
                  m_renderer.set_fractal_offset(offset);
                  m_state_changed = true;
                  break;
               }
               default: break;
            }
            break;
         }
         case sf::Event::MouseWheelMoved:
         {
            if (event.mouseWheel.delta == 1)
            {
               zoom_in();
            }
            else
            {
               zoom_out();
            }
            break;
         }
         case sf::Event::Closed:
         {
            m_window.close();
            break;
         }
         default: break;
      }
   }

   // Check here for generator changes
   if (check_if_generator_changed())
   {
      update_generator();
      m_last_fractal_generator_index = m_fractal_generator_index;
      m_state_changed = true;
   }

   if (check_if_colour_algorithm_changed())
   {
      update_colour_algorithm();
      m_last_fractal_colouring_index = m_fractal_colouring_index;
      m_state_changed = true;
   }

   if (check_if_colour_palette_changed())
   {
      update_colour_palette();
      m_last_colour_palette_index = m_colour_palette_index;
      m_state_changed = true;
   }
}

void application::update()
{
   // Only update if we flag that the state has changed
   if (m_state_changed)
   {
      const sf::Clock render_timer;
      m_renderer.render();
      m_fractal_texture.update(&(m_renderer.data().front()));
      const sf::Time render_time = render_timer.getElapsedTime();
      m_render_time_ms = render_time.asMilliseconds();

      m_state_changed = false;
   }

   // Always update ImGui
   // Do this after so we get render stats from the run
   update_gui();
}

void application::display()
{
   m_window.clear(sf::Color::Black); // fill background with color
   m_sprite.setTexture(m_fractal_texture);
   m_window.draw(m_sprite);
   ImGui::SFML::Render(m_window);
   m_window.display();
}
