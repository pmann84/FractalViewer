#include "application.h"

#include <iostream>
#include <windows.h>

application::application(std::string app_name) : m_app_name(app_name), m_window(sf::VideoMode::getDesktopMode(), m_app_name)
{
   m_window.setFramerateLimit(0); // May not need this eventually
   // No SFML call for this so need to resort to windows specific code
   ::ShowWindow(m_window.getSystemHandle(), SW_MAXIMIZE); 
}

bool application::is_open()
{
   return m_window.isOpen();
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
      }
   }
}

void application::update()
{
}

void application::display()
{
   m_window.display();
}
