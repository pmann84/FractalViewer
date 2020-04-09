#pragma once

#include <SFML/Graphics.hpp>
#include "fractal_generator.h"
#include <complex>

class julia_generator : public fractal_generator
{
public:
   julia_generator(unsigned int res_x, unsigned int res_y, std::complex<double> c);

   std::array<unsigned int, 4> get_pixel_color(unsigned int x, unsigned int y) override;

private:
   std::complex<double> m_c;
};
