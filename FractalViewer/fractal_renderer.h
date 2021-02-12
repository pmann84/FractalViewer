#ifndef __FRACTAL_VIEWER_FRACTAL_RENDERER_H__
#define __FRACTAL_VIEWER_FRACTAL_RENDERER_H__

#include "fractal_generator.h"

#include <SFML/Graphics.hpp>

namespace fc = fractal_core;

struct pixel_range
{
   uint32_t begin;
   uint32_t end;
};

class fractal_renderer
{
public:
   using pixel_buffer_t = std::vector<uint8_t>;

   fractal_renderer(
      uint32_t res_x,
      uint32_t res_y,
      std::unique_ptr<fc::fractal_generator> generator);

   void render();
   void render_range(pixel_range x_range, pixel_range y_range);
   const pixel_buffer_t& data() const { return m_fractal_data; }
   uint32_t core_count() const { return m_num_cores; }

   void set_fractal_generator(std::unique_ptr<fc::fractal_generator> generator);
   void set_fractal_colour_algorithm(fc::colouring::colour_algorithm_func_t func);
   void set_fractal_colour_palette(fc::palette::colour_from_palette_func_t func);
   void set_fractal_resolution(int resolution) const;
   int32_t fractal_resolution() const;
   void set_fractal_zoom(fc::zoom_action zoom) const;
   fc::zoom_action fractal_zoom() const;
   void set_fractal_offset(fc::offset_action offset) const;

   fc::complex_bounds get_bounds() const { return m_fractal_generator->get_bounds(); }
   void reset() const;

private:
   uint32_t m_res_x;
   uint32_t m_res_y;
   uint32_t m_num_cores;
   std::unique_ptr<fc::fractal_generator> m_fractal_generator;
   pixel_buffer_t m_fractal_data;
};

#endif // __FRACTAL_VIEWER_FRACTAL_RENDERER_H__