#pragma once
#include <SFML/Graphics.hpp>
#include "fractal_renderer.h"

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
   sf::Texture m_fractal_texture;
   sf::Sprite m_sprite;

   bool m_state_changed;

   int m_fractal_resolution = 30;
   int m_fractal_res_delta = 4;
   int m_fractal_res_min = 1;
   int m_fractal_res_max = 1000;

   double m_fractal_zoom = 1.0;
   double m_fractal_zoom_factor = 1.3;
   double m_fractal_zoom_min = 1.0;

   fractal_renderer m_renderer;

   //void set_pixel(unsigned int x, unsigned y, std::array<unsigned int, 4> colour);
};
