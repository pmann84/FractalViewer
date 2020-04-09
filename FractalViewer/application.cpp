#include "application.h"

#include <iostream>
#include <windows.h>
#include "fractal_generator_factory.h"
#include "input_actions.h"

application::application(std::string app_name)
   : m_app_name(app_name)
   , m_resolution(sf::VideoMode::getDesktopMode())
   , m_window(m_resolution, m_app_name, sf::Style::Fullscreen)
   , m_state_changed(true)
   , m_renderer(m_resolution.width, m_resolution.height, fractal_generator_factory::create_mandelbrot_generator(m_resolution.width, m_resolution.height), m_fractal_resolution)
   //, m_renderer(m_resolution, fractal_generator_factory::create_julia_generator(m_resolution, { -0.8, 0.156 }), m_fractal_resolution)
{
   m_renderer.set_fractal_zoom({ 1.0, static_cast<int>(m_resolution.width) / 2, static_cast<int>(m_resolution.height) / 2 });
   m_window.setFramerateLimit(0); // May not need this eventually
   // No SFML call for this so need to resort to windows specific code
   ::ShowWindow(m_window.getSystemHandle(), SW_MAXIMIZE);
   m_fractal_texture.create(m_resolution.width, m_resolution.height);
   m_fractal_texture.setSmooth(true);
}

bool application::is_open() const
{
   return m_window.isOpen();
}

//void application::set_pixel(unsigned x, unsigned y, std::array<unsigned, 4> colour)
//{
//   m_fractal_image.setPixel(
//      x, 
//      y, 
//      sf::Color(colour[0], colour[1], colour[2], colour[3])
//   );
//}

void application::handle_events()
{
   // Poll Events
   sf::Event event;
   while (m_window.pollEvent(event))
   {
      switch (event.type)
      {
         case sf::Event::KeyPressed:
         {
            switch (event.key.code)
            {
               case sf::Keyboard::Q:
               {
                  m_fractal_resolution -= m_fractal_res_delta;
                  if (m_fractal_resolution <= m_fractal_res_min)
                  {
                     m_fractal_resolution = m_fractal_res_min;
                  }
                  std::cout << "Decreasing fractal resolution to " << m_fractal_resolution << std::endl;
                  m_renderer.set_fractal_resolution(m_fractal_resolution);
                  m_state_changed = true;
                  break;
               }
               case sf::Keyboard::E:
               {
                  m_fractal_resolution += m_fractal_res_delta;
                  if (m_fractal_resolution >= m_fractal_res_max)
                  {
                     m_fractal_resolution = m_fractal_res_max;
                  }
                  std::cout << "Increasing fractal resolution to " << m_fractal_resolution << std::endl;
                  m_renderer.set_fractal_resolution(m_fractal_resolution);
                  m_state_changed = true;
                  break;
               }
               case sf::Keyboard::LBracket:
               {
                  m_fractal_zoom *= m_fractal_zoom_factor;
                  if (m_fractal_zoom >= m_fractal_zoom_min)
                  {
                     m_fractal_zoom = m_fractal_zoom_min;
                  }
                  const zoom_action zoom{ m_fractal_zoom, sf::Mouse::getPosition().x, sf::Mouse::getPosition().y };
                  std::cout << "Setting zoom factor " << m_fractal_zoom << " at (" << sf::Mouse::getPosition().x << "," << sf::Mouse::getPosition().y << ")" << std::endl;
                  m_renderer.set_fractal_zoom(zoom);
                  m_state_changed = true;
                  break;
               }
               case sf::Keyboard::RBracket:
               {
                  m_fractal_zoom /= m_fractal_zoom_factor;
                  const zoom_action zoom{ m_fractal_zoom, sf::Mouse::getPosition().x, sf::Mouse::getPosition().y };
                  std::cout << "Setting zoom factor " << m_fractal_zoom << " at (" << sf::Mouse::getPosition().x << "," << sf::Mouse::getPosition().y << ")" << std::endl;
                  m_renderer.set_fractal_zoom(zoom);
                  m_state_changed = true;
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
            if (event.mouseWheel.delta == -1)
            {
               m_fractal_zoom /= m_fractal_zoom_factor;
               if (m_fractal_zoom <= m_fractal_zoom_min)
               {
                  m_fractal_zoom = m_fractal_zoom_min;
               }
               const zoom_action zoom{ m_fractal_zoom, event.mouseWheel.x, event.mouseWheel.y };
               std::cout << "Setting zoom factor " << m_fractal_zoom << " at (" << event.mouseWheel.x << "," << event.mouseWheel.y << ")" << std::endl;
               m_renderer.set_fractal_zoom(zoom);
               m_state_changed = true;
            }
            else
            {
               m_fractal_zoom *= m_fractal_zoom_factor;
               const zoom_action zoom{ m_fractal_zoom, event.mouseWheel.x, event.mouseWheel.y };
               std::cout << "Setting zoom factor " << m_fractal_zoom << " at (" << event.mouseWheel.x << "," << event.mouseWheel.y << ")" << std::endl;
               m_renderer.set_fractal_zoom(zoom);
               m_state_changed = true;
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
      std::cout << "Fractal Render (" << m_resolution.width * m_resolution.height << " pxs) completed in " << render_time.asMilliseconds() << "ms." << std::endl;

      m_state_changed = false;
   }
}

void application::display()
{
   m_sprite.setTexture(m_fractal_texture);
   m_window.draw(m_sprite);
   m_window.display();
}
