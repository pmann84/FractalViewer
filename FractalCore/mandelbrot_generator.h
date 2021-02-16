#ifndef __FRACTAL_CORE_MANDELBROT_GENERATOR_H__
#define __FRACTAL_CORE_MANDELBROT_GENERATOR_H__

#include "fractal_generator.h"

namespace fractal_core
{
   class mandelbrot_generator : public fractal_generator
   {
   public:
      mandelbrot_generator(resolution res, palette::colour_from_palette_func_t c_func, colouring::colour_algorithm_func_t algo_func);

      std::array<uint8_t, 4> get_pixel_color(uint32_t x, uint32_t y) override;
   };
}
#endif // __FRACTAL_CORE_MANDELBROT_GENERATOR_H__