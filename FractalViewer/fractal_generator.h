#pragma once
#include <array>

#include "complex_bounds.h"
#include "colour_palette_generator.h"


namespace generator_utils
{
   inline std::array<unsigned int, 4> escape_time_colour_wrapped(const unsigned int iteration_count)
   {
      colour_palette p = palette::create::blue();
      return p.get_colour(iteration_count);
   }

   inline std::array<unsigned int, 4> escape_time_colour(const unsigned int iteration_count, const unsigned int max_iterations)
   {
      colour_palette p = palette::create::blue();
      return p.get_colour(iteration_count, max_iterations);
   }

   inline std::array<unsigned int, 4> continuous_potential(const unsigned iteration_count, double z_abs)
   {
      colour_palette p = palette::create::blue();
      float d = log(z_abs) / std::pow(2.0, iteration_count);
      return p.get_colour(d);
   }

   //inline std::array<unsigned int, 4> get_colour_for_iteration_count(const unsigned int iteration, const unsigned int max_iterations)
   //{
   //   if (iteration == max_iterations)
   //   {
   //      return { 255, 255,255, 255 };
   //   }
   //   const auto colour_grad = static_cast<unsigned int>(iteration * (255 / max_iterations));
   //   return { 0, 0, colour_grad, 255 };
   //}

   //inline double colour_transform(double grad, double c)
   //{
   //   return 0.5 + 0.5*cos(3.0 + grad * 0.075*2.0 + c);
   //}

   //inline std::array<unsigned int, 4> get_colour_for_iteration_count(const unsigned int iteration, const double z_abs, const double escape_r)
   //{
   //   const double log_grad = static_cast<double>(iteration) - log(log(z_abs) / (log(escape_r))) / log(2.0);
   //   return { static_cast<unsigned int>(colour_transform(log_grad, 0.0) * 255.0), static_cast<unsigned int>(colour_transform(log_grad, 0.6) * 255.0), static_cast<unsigned int>(colour_transform(log_grad, 1.0) * 255.0), 255 };
   //}
}

class fractal_generator
{
public:
   fractal_generator(
      std::complex<double> min, std::complex<double> max, 
      unsigned int x_res, unsigned int y_res)
         : m_bounds(min, max)
         , m_x_res(x_res)
         , m_y_res(y_res)
   {
   }
   virtual ~fractal_generator() = default;

   virtual std::array<unsigned int, 4> get_pixel_color(unsigned int x, unsigned int y) = 0;

   std::complex<double> complex_from_pixel(unsigned int x_pixel, unsigned int y_pixel) const
   {
      return m_bounds.complex_from_pixel(x_pixel, m_x_res, y_pixel, m_y_res);
   }

   void set_fractal_resolution(int fractal_resolution)
   {
      m_fractal_resolution = fractal_resolution;
   }

   void set_fractal_zoom(zoom_action fractal_zoom)
   {
      m_fractal_zoom = fractal_zoom;
      m_bounds.zoom(fractal_zoom, m_x_res, m_y_res);
   }

   void set_fractal_offset(offset_action fractal_offset)
   {
      m_bounds.offset(fractal_offset);
   }

protected:
   int m_fractal_resolution = 127;
   zoom_action m_fractal_zoom;
   complex_bounds m_bounds;
   unsigned int m_x_res;
   unsigned int m_y_res;
};
