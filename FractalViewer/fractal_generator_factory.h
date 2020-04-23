#pragma once

#include "fractal_generator.h"
#include "mandelbrot_generator.h"
#include "julia_generator.h"

class fractal_generator_factory
{
public:
   static std::unique_ptr<fractal_generator> create_mandelbrot_generator(uint32_t res_x, uint32_t res_y, colour_gen_func_t func)
   {
      return std::make_unique<mandelbrot_generator>(res_x, res_y, func);
   }

   static std::unique_ptr<fractal_generator> create_julia_generator(uint32_t res_x, uint32_t res_y, colour_gen_func_t func, std::complex<double> c)
   {
      return std::make_unique<julia_generator>(res_x, res_y, func, c);
   }
};
