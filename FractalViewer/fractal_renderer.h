#pragma once

#include <SFML/Graphics.hpp>

#include "fractal_generator.h"

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
      std::unique_ptr<fractal_generator> generator);

   void render();
   void render_range(pixel_range x_range, pixel_range y_range);
   const pixel_buffer_t& data() const { return m_fractal_data; }
   uint32_t core_count() const { return m_num_cores; }

   void set_fractal_generator(std::unique_ptr<fractal_generator> generator);
   void set_fractal_colour_algorithm(colour_gen_func_t func);
   void set_fractal_resolution(int resolution) const;
   void set_fractal_zoom(zoom_action zoom) const;
   void set_fractal_offset(offset_action offset) const;

   complex_bounds get_bounds() const { return m_fractal_generator->get_bounds(); }
   void reset_bounds() const { m_fractal_generator->reset_bounds(); }

private:
   uint32_t m_res_x;
   uint32_t m_res_y;
   uint32_t m_num_cores;
   std::unique_ptr<fractal_generator> m_fractal_generator;
   pixel_buffer_t m_fractal_data;
};
