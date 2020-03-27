#include <iostream>

#include "application.h"

application::application(std::string app_name) : m_app_name(app_name)
{

}

void application::init()
{
   sf::VideoMode desktop_res = sf::VideoMode::getDesktopMode();
   std::cout << "Starting Fractal Renderer with window resolution " << desktop_res.width << "x" << desktop_res.height << std::endl;
   sf::RenderWindow window(desktop_res, m_app_name);
   window.setFramerateLimit(0); // May not need this eventually
}

void application::update()
{
}
