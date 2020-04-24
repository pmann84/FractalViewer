#pragma once

#include "complex_bounds.h"
#include "colour_palette.h"

#include <array>
#include <functional>
#include <utility>

using colour_gen_func_t = std::function<std::array<uint8_t, 4>(const uint32_t, const uint32_t, double)>;

namespace generator_utils
{
   // TODO: Make these just return a single uint32_t to put into the buffer (might not be possible)
   inline std::array<uint8_t, 4> escape_time_colour(const uint32_t iteration_count, const uint32_t max_iterations, double)
   {
      //const float p = static_cast<float>(iteration_count);
      const float p = static_cast<float>(iteration_count) * 256.0f / static_cast<float>(max_iterations);
      auto colour = palette::default_palette::get(static_cast<float>(p)).rgba();
      return {
         static_cast<uint8_t>(colour[0] * 255),
         static_cast<uint8_t>(colour[1] * 255),
         static_cast<uint8_t>(colour[2] * 255),
         static_cast<uint8_t>(colour[3] * 255)
      };
   }

   inline std::array<uint8_t, 4> continuous_potential(const uint32_t iteration_count, const uint32_t max_iterations, double z_abs)
   {
      const float iter_p = static_cast<float>(iteration_count) + 1.0f - logf(logf(z_abs) / (logf(2.0f))) / logf(2.0f);
      const float p =  iter_p * 256.0f / static_cast<float>(max_iterations);
      auto colour = palette::default_palette::get(static_cast<float>(p)).rgba();
      return {
         static_cast<uint8_t>(colour[0] * 255),
         static_cast<uint8_t>(colour[1] * 255),
         static_cast<uint8_t>(colour[2] * 255),
         static_cast<uint8_t>(colour[3] * 255)
      };
   }
}

class fractal_generator
{
public:
   fractal_generator(
      std::complex<double> min, std::complex<double> max, 
      uint32_t x_res, uint32_t y_res, colour_gen_func_t func)
         : m_bounds(min, max)
         , m_x_res(x_res)
         , m_y_res(y_res)
         , m_colour_gen_func(std::move(func))
   {
   }
   virtual ~fractal_generator() = default;

   virtual std::array<uint8_t, 4> get_pixel_color(uint32_t x, uint32_t y) = 0;

   std::complex<double> complex_from_pixel(uint32_t x_pixel, uint32_t y_pixel) const
   {
      return m_bounds.complex_from_pixel(x_pixel, m_x_res, y_pixel, m_y_res);
   }

   complex_bounds get_bounds() const { return m_bounds; }

   void set_fractal_colouring_algorithm(colour_gen_func_t func)
   {
      m_colour_gen_func = std::move(func);
   }

   void set_fractal_resolution(int32_t fractal_resolution)
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

   void reset_bounds()
   {
      m_bounds.reset();
   }
protected:
   int32_t m_fractal_resolution = 127;
   zoom_action m_fractal_zoom;
   complex_bounds m_bounds;
   uint32_t m_x_res;
   uint32_t m_y_res;
   colour_gen_func_t m_colour_gen_func;
};
