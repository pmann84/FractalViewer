#include "application.h"

#include <iostream>
#include <windows.h>
#include "fractal_generator_factory.h"

application::application(std::string app_name)
   : m_app_name(app_name)
   , m_resolution(sf::VideoMode::getDesktopMode())
   , m_window(m_resolution, m_app_name)
   , m_state_changed(true)
   , m_renderer(m_resolution, fractal_generator_factory::create_mandelbrot_generator())
{
   m_window.setFramerateLimit(0); // May not need this eventually
   // No SFML call for this so need to resort to windows specific code
   ::ShowWindow(m_window.getSystemHandle(), SW_MAXIMIZE);
   m_fractal_image.create(m_resolution.width, m_resolution.height, sf::Color(0, 0, 0));
   m_fractal_texture.setSmooth(true);
}

bool application::is_open() const
{
   return m_window.isOpen();
}

void application::set_pixel(unsigned x, unsigned y, std::array<unsigned, 4> colour)
{
   m_fractal_image.setPixel(
      x, 
      y, 
      sf::Color(colour[0], colour[1], colour[2], colour[3])
   );
}

void application::handle_events()
{
   // Poll Events
   sf::Event event;
   while (m_window.pollEvent(event))
   {
      switch (event.type)
      {
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
      sf::Clock render_timer;
      //auto set_pixel_func = std::bind(&application::set_pixel, *this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
      m_renderer.render(m_fractal_image);
      sf::Time render_time = render_timer.getElapsedTime();
      std::cout << "Fractal Render completed in " << render_time.asMilliseconds() << "ms." << std::endl;

      m_state_changed = false;
   }
}

void application::display()
{
   m_fractal_texture.loadFromImage(m_fractal_image);
   m_sprite.setTexture(m_fractal_texture);
   m_window.draw(m_sprite);
   m_window.display();
}
