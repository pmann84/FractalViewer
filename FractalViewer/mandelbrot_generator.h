#pragma once

#include "fractal_generator.h"

class mandelbrot_generator : public fractal_generator
{
public:
   mandelbrot_generator();

   std::array<unsigned int, 4> get_pixel_color(unsigned int x, unsigned int y, const int fractal_resolution, const sf::VideoMode window_res) override;
};
