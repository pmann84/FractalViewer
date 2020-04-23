#pragma once

#include "fractal_generator.h"
#include <complex>

class julia_generator : public fractal_generator
{
public:
   julia_generator(uint32_t res_x, uint32_t res_y, colour_gen_func_t func, std::complex<double> c);

   std::array<uint8_t, 4> get_pixel_color(uint8_t x, uint8_t y) override;

private:
   std::complex<double> m_c;
};
