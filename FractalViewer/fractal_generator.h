#pragma once
#include <array>
#include <complex>

#include <SFML/Window.hpp>
#include "zoom_action.h"

class complex_bounds
{
public:
   complex_bounds(std::complex<double> min, std::complex<double> max)
      : m_min(min), m_max(max), m_original_min(min), m_original_max(max)
   {
   }

   std::complex<double> centre() const
   {
      return m_min + (m_max - m_min) / 2.0;
   }

   std::complex<double> complex_from_pixel(unsigned int x_pixel, unsigned int x_res, unsigned int y_pixel, unsigned int y_res) const
   {
      // We do this outside of complex numbers because its about 50ms quicker!
      double r = m_min.real() + x_pixel * (m_max.real() - m_min.real()) / static_cast<double>(x_res);
      double i = m_max.imag() - y_pixel * (m_max.imag() - m_min.imag()) / static_cast<double>(y_res);;
      return { r, i };
   }

   void zoom(zoom_action z, unsigned int x_res, unsigned int y_res)
   {
      const std::complex<double> new_limits = z.factor * (m_max - m_min);
      const std::complex<double> new_centre = complex_from_pixel(z.x, x_res, z.y, y_res);
      m_min = new_centre - new_limits / 2.0;
      m_max = new_centre + new_limits / 2.0;
   }

   void reset()
   {
      m_min = m_original_min;
      m_max = m_original_max;
   }
private:
   std::complex<double> m_min;
   std::complex<double> m_max;

   std::complex<double> m_original_min;
   std::complex<double> m_original_max;

};

namespace generator_utils
{
   inline std::array<unsigned int, 4> get_colour_for_iteration_count(const unsigned int iteration, const unsigned int max_iterations)
   {
      if (iteration == max_iterations)
      {
         return { 255, 255,255, 255 };
      }
      const auto colour_grad = static_cast<unsigned int>(iteration * (255 / max_iterations));
      return { 0, 0, colour_grad, 255 };
   }
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

protected:
   int m_fractal_resolution = 127;
   zoom_action m_fractal_zoom;
   complex_bounds m_bounds;
   unsigned int m_x_res;
   unsigned int m_y_res;
};
