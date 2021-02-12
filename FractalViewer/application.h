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

   uint64_t m_render_time_ms;

   bool m_state_changed;
   int32_t m_fractal_generator_index = 0;
   int32_t m_last_fractal_generator_index = m_fractal_generator_index;

   int32_t m_fractal_colouring_index = 0;
   int32_t m_last_fractal_colouring_index = m_fractal_colouring_index;

   int32_t m_colour_palette_index = 0;
   int32_t m_last_colour_palette_index = m_colour_palette_index;

   uint32_t m_fractal_resolution = 30;
   uint32_t m_fractal_res_delta = 4;
   uint32_t m_fractal_res_min = 1;
   uint32_t m_fractal_res_max = 1000;

   double m_fractal_zoom = 1.0;
   double m_fractal_zoom_factor = 1.3;
   double m_fractal_zoom_min = 1.0;

   float m_julia_c[2];

   fractal_renderer m_renderer;

   void update_gui();
   bool check_if_generator_changed() const;
   void update_generator();

   bool check_if_colour_algorithm_changed() const;
   void update_colour_algorithm();
   fc::colouring::colour_algorithm_func_t get_selected_colour_algorithm() const;

   bool check_if_colour_palette_changed() const;
   void update_colour_palette();
   fc::palette::colour_from_palette_func_t get_selected_colour_palette() const;

   void zoom_in();
   void zoom_out();

   void increase_fractal_res();
   void decrease_fractal_res();
};
