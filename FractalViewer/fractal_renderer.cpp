#include "fractal_renderer.h"

#include <thread>
#include <future>
#include <iostream>
#include <utility>

fractal_renderer::fractal_renderer(
   uint32_t res_x,
   uint32_t res_y,
   std::unique_ptr<fractal_generator> generator)
      : m_res_x(res_x)
      , m_res_y(res_y)
      , m_fractal_generator(std::move(generator))
{
   const auto processor_count = std::thread::hardware_concurrency();
   m_num_cores = processor_count == 0 ? 1 : processor_count;
   m_fractal_data.resize(m_res_x * m_res_y * 4);
   std::cout << "Fractal Renderer initialised with access to " << processor_count << " threads." << std::endl;
}

void fractal_renderer::render()
{
   // Because the buffer (and texture) accepts the buffer in columns i.e. col1, col2, ....
   // We split the domain by the vertical resolution, so its easy to combine them all
   const uint32_t y_pixel_interval = m_res_y / m_num_cores;
   const pixel_range x_range = { 0, m_res_x };
   std::vector<std::future<void>> tasks;
   for (uint32_t i = 0; i < m_num_cores; ++i)
   {
      pixel_range y_range = { i * y_pixel_interval, (i + 1) * y_pixel_interval };
      if (y_range.end > m_res_y) y_range.end = m_res_y;
      tasks.emplace_back(std::async(std::launch::async, &fractal_renderer::render_range, this, x_range, y_range));
   }

   for (auto &task : tasks) 
   {
      task.get();
   }
}

void fractal_renderer::render_range(pixel_range x_range, pixel_range y_range)
{
   for (uint32_t i = x_range.begin; i < x_range.end; ++i)
   {
      for (uint32_t j = y_range.begin; j < y_range.end; ++j)
      {
         // TODO: Make the m_fractal_data contain uint32_t's instead! Check if the texture takes data in this form!
         const std::array<uint8_t, 4> pixel_colour = m_fractal_generator->get_pixel_color(i, j);
         const uint32_t current_idx = (j * m_res_x + i) * 4;
         m_fractal_data[current_idx + 0] = pixel_colour[0]; // R
         m_fractal_data[current_idx + 1] = pixel_colour[1]; // G
         m_fractal_data[current_idx + 2] = pixel_colour[2]; // B
         m_fractal_data[current_idx + 3] = pixel_colour[3]; // A
      }
   }
}

const std::vector<uint8_t>& fractal_renderer::data() const
{
   return m_fractal_data;
}

void fractal_renderer::set_fractal_generator(std::unique_ptr<fractal_generator> generator)
{
   m_fractal_generator = std::move(generator);
}

void fractal_renderer::set_fractal_colour_algorithm(colour_gen_func_t func)
{
   m_fractal_generator->set_fractal_colouring_algorithm(std::move(func));
}

void fractal_renderer::set_fractal_resolution(int32_t resolution) const
{
   m_fractal_generator->set_fractal_resolution(resolution);
}

void fractal_renderer::set_fractal_zoom(zoom_action zoom) const
{
   m_fractal_generator->set_fractal_zoom(zoom);
}

void fractal_renderer::set_fractal_offset(offset_action offset) const
{
   m_fractal_generator->set_fractal_offset(offset);
}
