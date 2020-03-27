#pragma once
#include <SFML/Graphics.hpp>

class application
{
public:
   application(std::string app_name);

   void handle_events();
   void update();
   void display();

   bool is_open() const;

private:
   std::string m_app_name;
   sf::VideoMode m_resolution;
   sf::RenderWindow m_window;
   sf::Image m_fractal_image;
   sf::Texture m_fractal_texture;
   sf::Sprite m_sprite;
   bool m_state_changed;
};
