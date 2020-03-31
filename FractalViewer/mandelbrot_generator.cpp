#include "mandelbrot_generator.h"

mandelbrot_generator::mandelbrot_generator()
{
}

std::array<unsigned int, 4> mandelbrot_generator::get_pixel_color(unsigned int x, unsigned int y, const sf::VideoMode window_res)
{
   // Mandelbrot (-2.5 - i) to (1 + i)
   // Get scaled mandelbrot coordinate z0
   const complex_range<double> range {
   std::complex<double>(-3.0, -1.5),
   std::complex<double>(1.5, 1.5)
   };
   const std::complex<double> c = generator_utils::complex_from_pixel(
      x, 
      window_res.width, 
      y, 
      window_res.height, 
      range);
   // Initialise iteration count to 0
   int iteration = 0;
   // Initialise z to 0
   std::complex<double> zn(0.0, 0.0);
   // check whether |z| < 4
   // condition for general polynomial for some R > 0 such that |c| < R^2 - R (Mandelbrot has R=2)
   const double escape_r = 2.0;
   while (zn.real() * zn.real() + zn.imag() * zn.imag() < escape_r && iteration < m_fractal_resolution)
   {
      // keep updating until condition reached or max iterations hit
      zn = zn * zn + c;
      ++iteration;
   }
   // Assign colour based on iteration value
   return generator_utils::get_colour_for_iteration_count(iteration, m_fractal_resolution);
}
