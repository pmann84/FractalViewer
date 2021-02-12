#pragma once

#include "fractal_generator.h"
#include <complex>

class julia_generator : public fractal_generator
{
public:
   julia_generator(uint32_t res_x, uint32_t res_y, palette::colour_from_palette_func_t c_func, colouring::colour_algorithm_func_t algo_func, std::complex<double> c);

   std::array<uint8_t, 4> get_pixel_color(uint32_t x, uint32_t y) override;

private:
   std::complex<double> m_c;
};
