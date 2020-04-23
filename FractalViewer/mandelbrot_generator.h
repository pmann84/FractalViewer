#pragma once

#include "fractal_generator.h"

class mandelbrot_generator : public fractal_generator
{
public:
   mandelbrot_generator(uint32_t res_x, uint32_t res_y, colour_gen_func_t func);

   std::array<uint8_t, 4> get_pixel_color(uint8_t x, uint8_t y) override;
};
