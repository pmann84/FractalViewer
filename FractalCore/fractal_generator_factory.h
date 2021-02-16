#ifndef __FRACTAL_CORE_FRACTAL_GENERATOR_FACTORY_H__
#define __FRACTAL_CORE_FRACTAL_GENERATOR_FACTORY_H__

#include "resolution.h"
#include "fractal_generator.h"
#include "mandelbrot_generator.h"
#include "julia_generator.h"

namespace fractal_core
{
   class fractal_generator_factory
   {
   public:
      static std::unique_ptr<fractal_generator> create_mandelbrot_generator(resolution res, palette::colour_from_palette_func_t c_func, colouring::colour_algorithm_func_t algo_func)
      {
         return std::make_unique<mandelbrot_generator>(res, c_func, algo_func);
      }

      static std::unique_ptr<fractal_generator> create_julia_generator(resolution res, palette::colour_from_palette_func_t c_func, colouring::colour_algorithm_func_t algo_func, std::complex<double> c)
      {
         return std::make_unique<julia_generator>(res, c_func, algo_func, c);
      }
   };
}
#endif // __FRACTAL_CORE_FRACTAL_GENERATOR_FACTORY_H__