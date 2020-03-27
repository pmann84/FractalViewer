#pragma once
#include <SFML/Graphics.hpp>

class application
{
public:
   application(std::string app_name);

   void init();
   void update();

private:
   std::string m_app_name;
   sf::RenderWindow m_window;
};
