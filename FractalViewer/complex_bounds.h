#pragma once
#include <complex>
#include "input_actions.h"

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

   void offset(offset_action offset)
   {
      std::complex<double> delta = 0.1*(m_max - m_min);
      std::complex<double> off{ offset.x * delta.real(), offset.y * delta.imag() };
      m_min += off;
      m_max += off;
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
