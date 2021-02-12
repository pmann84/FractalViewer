#include "mandelbrot_generator.h"

#include <utility>

namespace fractal_core
{
   mandelbrot_generator::mandelbrot_generator(uint32_t res_x, uint32_t res_y, palette::colour_from_palette_func_t c_func, colouring::colour_algorithm_func_t algo_func)
      : fractal_generator(std::complex<double>(-3.0, -1.5),
                        std::complex<double>(1.5, 1.5),
                        res_x,
                        res_y,
                        std::move(c_func),
                        std::move(algo_func))
   {
   }

   std::array<uint8_t, 4> mandelbrot_generator::get_pixel_color(uint32_t x, uint32_t y)
   {
      const std::complex<double> c = complex_from_pixel(x, y);

      // Initialise iteration count to 0
      int32_t iteration = 0;
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
      const double z_abs = sqrt(zn.real() * zn.real() + zn.imag() * zn.imag());
      return m_colour_from_palette_func(m_colour_algo_func(iteration, m_fractal_resolution, z_abs)).rgba();
      //return m_colour_gen_func(iteration, m_fractal_resolution, z_abs);
   }
}