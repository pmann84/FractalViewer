#pragma once
#include <SFML/Graphics.hpp>

class application
{
public:
   application(std::string app_name);

   void handle_events();
   void update();
   void display();

   bool is_open();

private:
   std::string m_app_name;
   sf::RenderWindow m_window;
};
