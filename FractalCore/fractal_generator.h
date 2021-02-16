#ifndef __FRACTAL_CORE_FRACTAL_GENERATOR_H__
#define __FRACTAL_CORE_FRACTAL_GENERATOR_H__

#include "colour_palette.h"
#include "complex_bounds.h"
#include "resolution.h"

#include <array>
#include <functional>
#include <utility>

namespace fractal_core
{
   class fractal_generator
   {
   public:
      fractal_generator(
         std::complex<double> min, std::complex<double> max, 
         resolution res, palette::colour_from_palette_func_t c_func, colouring::colour_algorithm_func_t algo_func)
         : m_fractal_resolution(30)
         , m_init_fractal_resolution(m_fractal_resolution)
         , m_bounds(min, max)
         , m_res(res)
         , m_colour_from_palette_func(std::move(c_func))
         , m_colour_algo_func(std::move(algo_func))
      {
      }

      virtual ~fractal_generator() = default;

      virtual std::array<uint8_t, 4> get_pixel_color(uint32_t x, uint32_t y) = 0;

      std::complex<double> complex_from_pixel(uint32_t x_pixel, uint32_t y_pixel) const
      {
         return m_bounds.complex_from_pixel(x_pixel, m_res.x, y_pixel, m_res.y);
      }

      complex_bounds get_bounds() const { return m_bounds; }

      void set_fractal_colour_palette(palette::colour_from_palette_func_t func)
      {
         m_colour_from_palette_func = std::move(func);
      }

      void set_fractal_colouring_algorithm(colouring::colour_algorithm_func_t func)
      {
         m_colour_algo_func = std::move(func);
      }

      void set_fractal_resolution(int32_t fractal_resolution)
      {
         m_fractal_resolution = fractal_resolution;
      }

      int32_t fractal_resolution() const { return m_fractal_resolution; }

      void set_fractal_zoom(zoom_action fractal_zoom)
      {
         m_fractal_zoom = fractal_zoom;
         m_bounds.zoom(fractal_zoom, m_res.x, m_res.y);
      }

      zoom_action fractal_zoom() const { return m_fractal_zoom; }

      void set_fractal_offset(offset_action fractal_offset)
      {
         m_bounds.offset(fractal_offset);
      }

      void reset_bounds()
      {
         m_bounds.reset();
      }

      void reset_resolution()
      {
         m_fractal_resolution = m_init_fractal_resolution;
      }

      void reset_zoom()
      {
         m_fractal_zoom = {1.0f, 0, 0};
      }
   protected:
      int32_t m_fractal_resolution;
      int32_t m_init_fractal_resolution;
      zoom_action m_fractal_zoom;
      complex_bounds m_bounds;
      resolution m_res;
      palette::colour_from_palette_func_t m_colour_from_palette_func;
      colouring::colour_algorithm_func_t m_colour_algo_func;
   };
}
#endif // __FRACTAL_CORE_FRACTAL_GENERATOR_H__