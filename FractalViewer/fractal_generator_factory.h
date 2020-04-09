#pragma once

#include "fractal_generator.h"
#include "mandelbrot_generator.h"
#include "julia_generator.h"

class fractal_generator_factory
{
public:
   static std::unique_ptr<fractal_generator> create_mandelbrot_generator(unsigned int res_x, unsigned int res_y)
   {
      return std::make_unique<mandelbrot_generator>(res_x, res_y);
   }

   static std::unique_ptr<fractal_generator> create_julia_generator(unsigned int res_x, unsigned int res_y, std::complex<double> c)
   {
      return std::make_unique<julia_generator>(res_x, res_y, c);
   }
};
