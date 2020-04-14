#include "mandelbrot_generator.h"
#include <iostream>

mandelbrot_generator::mandelbrot_generator(unsigned int res_x, unsigned int res_y)
   : fractal_generator(std::complex<double>(-3.0, -1.5),
                       std::complex<double>(1.5, 1.5),
                       res_x,
                       res_y)
{
}

std::array<unsigned int, 4> mandelbrot_generator::get_pixel_color(unsigned int x, unsigned int y)
{
   const std::complex<double> c = complex_from_pixel(x, y);

   //std::cout << "Complex coord: " << c << " at pixel (" << x << "," << y << ")" << std::endl;
   // Initialise iteration count to 0
   int iteration = 0;
   // Initialise z to 0
   std::complex<double> zn(0.0, 0.0);
   // check whether |z| < 4
   // condition for general polynomial for some R > 0 such that |c| < R^2 - R (Mandelbrot has R=2)
   const double escape_r = 4.0;
   while (zn.real() * zn.real() + zn.imag() * zn.imag() <= escape_r && iteration < m_fractal_resolution)
   {
      // keep updating until condition reached or max iterations hit
      zn = zn * zn + c;
      ++iteration;
   }
   // Assign colour based on iteration value
   return generator_utils::get_colour_for_iteration_count(iteration, m_fractal_resolution);
}