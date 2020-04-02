#pragma once

#include "fractal_generator.h"
#include "mandelbrot_generator.h"
#include "julia_generator.h"

class fractal_generator_factory
{
public:
   static std::unique_ptr<fractal_generator> create_mandelbrot_generator(sf::VideoMode resolution)
   {
      return std::make_unique<mandelbrot_generator>(resolution);
   }

   static std::unique_ptr<fractal_generator> create_julia_generator(sf::VideoMode resolution, std::complex<double> c)
   {
      return std::make_unique<julia_generator>(resolution, c);
   }
};
