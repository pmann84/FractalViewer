#pragma once

#include <SFML/Graphics.hpp>

#include "fractal_generator.h"

struct pixel_range
{
   unsigned int begin;
   unsigned int end;
};

class fractal_renderer
{
public:
   using pixel_buffer_t = std::vector<unsigned char>;

   fractal_renderer(
      unsigned int res_x,
      unsigned int res_y,
      std::unique_ptr<fractal_generator> generator, 
      int fractal_resolution);

   void render();
   void render_range(pixel_range x_range, pixel_range y_range);
   const pixel_buffer_t& data() const;

   void set_fractal_resolution(int resolution) const;
   void set_fractal_zoom(zoom_action zoom) const;
   void set_fractal_offset(offset_action offset) const;

private:
   unsigned int m_res_x;
   unsigned int m_res_y;
   unsigned int m_num_cores;
   std::unique_ptr<fractal_generator> m_fractal_generator;
   pixel_buffer_t m_fractal_data;
};
