#pragma once

#include "fractal_generator.h"
#include "mandelbrot_generator.h"
#include "julia_generator.h"

class fractal_generator_factory
{
public:
   static std::unique_ptr<fractal_generator> create_mandelbrot_generator()
   {
      return std::make_unique<mandelbrot_generator>();
   }

   static std::unique_ptr<fractal_generator> create_julia_generator(std::complex<double> c)
   {
      return std::make_unique<julia_generator>(c);
   }
};
