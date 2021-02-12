#ifndef __FRACTAL_CORE_FRACTAL_GENERATOR_FACTORY_H__
#define __FRACTAL_CORE_FRACTAL_GENERATOR_FACTORY_H__

#include "fractal_generator.h"
#include "mandelbrot_generator.h"
#include "julia_generator.h"

namespace fractal_core
{
   class fractal_generator_factory
   {
   public:
      static std::unique_ptr<fractal_generator> create_mandelbrot_generator(uint32_t res_x, uint32_t res_y, palette::colour_from_palette_func_t c_func, colouring::colour_algorithm_func_t algo_func)
      {
         return std::make_unique<mandelbrot_generator>(res_x, res_y, c_func, algo_func);
      }

      static std::unique_ptr<fractal_generator> create_julia_generator(uint32_t res_x, uint32_t res_y, palette::colour_from_palette_func_t c_func, colouring::colour_algorithm_func_t algo_func, std::complex<double> c)
      {
         return std::make_unique<julia_generator>(res_x, res_y, c_func, algo_func, c);
      }
   };
}
#endif // __FRACTAL_CORE_FRACTAL_GENERATOR_FACTORY_H__