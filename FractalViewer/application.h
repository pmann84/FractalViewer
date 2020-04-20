#pragma once
#include <SFML/Graphics.hpp>
#include "fractal_renderer.h"

class application
{
public:
   application(std::string app_name);
   ~application();

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
   sf::Clock m_gui_clock;

   unsigned int m_render_time_ms;

   bool m_state_changed;
   int m_fractal_generator_index = 0;
   int m_last_fractal_generator_index = m_fractal_generator_index;

   int m_fractal_resolution = 30;
   int m_fractal_res_delta = 4;
   int m_fractal_res_min = 1;
   int m_fractal_res_max = 1000;

   double m_fractal_zoom = 1.0;
   double m_fractal_zoom_factor = 1.3;
   double m_fractal_zoom_min = 1.0;

   fractal_renderer m_renderer;

   void update_gui();
   bool check_if_generator_changed() const;
   void update_generator();

   void zoom_in();
   void zoom_out();

   void increase_fractal_res();
   void decrease_fractal_res();
};
