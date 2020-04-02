#pragma once

#include <SFML/Graphics.hpp>

#include "fractal_generator.h"
//#include <functional>

class fractal_renderer
{
public:
   //using set_pixel_func_t = std::function<
   //   void(
   //      unsigned int, // x
   //      unsigned int, // y
   //      std::array<unsigned int, 4>) // color
   //>;

   fractal_renderer(
      sf::VideoMode resolution, 
      std::unique_ptr<fractal_generator> generator, 
      int fractal_resolution);

   void render(sf::Image& image);

   void set_fractal_resolution(int resolution) const;
   void set_fractal_zoom(zoom_action zoom) const;

private:
   sf::VideoMode m_resolution;
   std::unique_ptr<fractal_generator> m_fractal_generator;
};
