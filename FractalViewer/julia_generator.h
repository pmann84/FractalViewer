#pragma once

#include "fractal_generator.h"
#include <complex>

class julia_generator : public fractal_generator
{
public:
   julia_generator(sf::VideoMode window_res, std::complex<double> c);

   std::array<unsigned int, 4> get_pixel_color(unsigned int x, unsigned int y) override;

private:
   std::complex<double> m_c;
};
