#include "julia_generator.h"

julia_generator::julia_generator(unsigned int res_x, unsigned int res_y, std::complex<double> c)
   : fractal_generator(std::complex<double>(-2.0, -1.5),
      std::complex<double>(2.0, 1.5),
      res_x,
      res_y)
   , m_c(c)
{
}

std::array<unsigned int, 4> julia_generator::get_pixel_color(unsigned int x, unsigned int y)
{
   std::complex<double> zn = complex_from_pixel(x, y);
   // Initialise iteration count to 0
   int iteration = 0;
   // condition for general polynomial for some R > 0 such that |c| < R^2 - R (Mandelbrot has R=2)
   const double escape_r = 2.0;
   const double r_cond = std::pow(escape_r, 2.0) - escape_r;

   while (zn.real() * zn.real() + zn.imag() * zn.imag() < escape_r && iteration < m_fractal_resolution)
   {
      // keep updating until condition reached or max iterations hit
      zn = zn * zn + m_c;
      ++iteration;
   }
   // Assign colour based on iteration value
   return generator_utils::get_colour_for_iteration_count(iteration, m_fractal_resolution);
}
