#pragma once

#include "fractal_generator.h"

class mandelbrot_generator : public fractal_generator
{
public:
   mandelbrot_generator(sf::VideoMode window_res);

   std::array<unsigned int, 4> get_pixel_color(unsigned int x, unsigned int y) override;
};
