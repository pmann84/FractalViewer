#ifndef __FRACTAL_CORE_JULIA_GENERATOR_H__
#define __FRACTAL_CORE_JULIA_GENERATOR_H__

#include "fractal_generator.h"

#include <complex>

namespace fractal_core
{
   class julia_generator : public fractal_generator
   {
   public:
      julia_generator(resolution res, palette::colour_from_palette_func_t c_func, colouring::colour_algorithm_func_t algo_func, std::complex<double> c);

      std::array<uint8_t, 4> get_pixel_color(uint32_t x, uint32_t y) override;

   private:
      std::complex<double> m_c;
   };
}
#endif // __FRACTAL_CORE_JULIA_GENERATOR_H__