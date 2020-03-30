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
      int fractal_resolution, 
      int fractal_zoom);

   void render(sf::Image& image);

   void set_fractal_resolution(int resolution);
   void set_fractal_zoom(double zoom);

private:
   sf::VideoMode m_resolution;
   std::unique_ptr<fractal_generator> m_fractal_generator;

   int m_fractal_resolution;
   double m_fractal_zoom;
};
