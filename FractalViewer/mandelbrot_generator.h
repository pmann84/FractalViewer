#pragma once

#include "fractal_generator.h"
#include <SFML/Graphics.hpp>

class mandelbrot_generator : public fractal_generator
{
public:
   mandelbrot_generator(unsigned int res_x, unsigned int res_y);

   std::array<unsigned int, 4> get_pixel_color(unsigned int x, unsigned int y) override;
};
