#include "julia_generator.h"

julia_generator::julia_generator(const std::complex<double> c) : m_c(c)
{
}

std::array<unsigned int, 4> julia_generator::get_pixel_color(unsigned int x, unsigned int y, const sf::VideoMode window_res)
{
   // Get scaled fractal coordinate z0
   const complex_range<double> range {
      std::complex<double>(-2.0, -1.5),
      std::complex<double>(2.0, 1.5)
   };

   // TODO: For zoom, need to recalculate the range, first get the mouse position
   // and calculate the complex coordinate equivalent, then calculate the range of the
   // original and add this to the mouse position to get the new range
   const std::complex<double> c(-0.8, 0.156);
   std::complex<double> zn = generator_utils::complex_from_pixel(
      x, 
      window_res.width, 
      y, 
      window_res.height, 
      range);
   // Initialise iteration count to 0
   int iteration = 0;
   // condition for general polynomial for some R > 0 such that |c| < R^2 - R (Mandelbrot has R=2)
   const double escape_r = 2.0;
   const double r_cond = std::pow(escape_r, 2.0) - escape_r;

   while (zn.real() * zn.real() + zn.imag() * zn.imag() < escape_r && iteration < m_fractal_resolution)
   {
      // keep updating until condition reached or max iterations hit
      zn = zn * zn + c;
      ++iteration;
   }
   // Assign colour based on iteration value
   return generator_utils::get_colour_for_iteration_count(iteration, m_fractal_resolution);
}
