#ifndef __FRACTAL_VIEWER_FRACTAL_RENDERER_H__
#define __FRACTAL_VIEWER_FRACTAL_RENDERER_H__

#include "fractal_generator.h"

#include <SFML/Graphics.hpp>

namespace fc = fractal_core;



class pixel_buffer
{
public:

};

// class cpu_pixel_buffer : public pixel_buffer
// {

// };

// class cuda_pixel_buffer : public pixel_buffer
// {

// };

// class pixel_buffer_factory
// {
// public:
//    std::unique_ptr<pixel_buffer> create(renderer::platform platform)
//    {
//       switch (platform)
//       {
//          case renderer::platform::CPU: return std::make_unique<cpu_pixel_buffer>();
//          case renderer::platform::CUDA: return std::make_unique<cuda_pixel_buffer>();
//       }
//    }
// };


// // context 
// class fractal_render_context
// {
// public:
//    static std::unique_ptr<fractal_render_context> create(renderer::platform platform)
//    {
//       switch (platform)
//       {
//          case renderer::platform::CPU: return std::make_unique<cpu_render_context>();
//          case renderer::platform::CUDA: return std::make_unique<cuda_render_context>();
//       }
//    }
// private:
//    resolution m_resolution;
//    std::unique_ptr<pixel_buffer> m_buffer;
// };

// class cpu_render_context : public

class render_context
{
public:
   render_context(fc::resolution res, fc::fractal_generator& generator) 
      : m_resolution(res)
      , m_generator(generator)
   {
      // Initia
   }
   virtual void render() = 0;

protected:
   virtual void render_range(pixel_range x, pixel_range y) = 0;

protected:
   fc::resolution m_resolution;
   std::unique_ptr<pixel_buffer> m_buffer;
   fc::fractal_generator& m_generator;
};

class cpu_render_context : public render_context
{
public:
   void render() override
   {
      // Because the buffer (and texture) accepts the buffer in rows i.e. row1, row2, ....
      // We split the domain by the vertical resolution, so its easy to combine them all
      const uint32_t y_pixel_interval = m_resolution.y / m_num_cores;
      const pixel_range x_range = { 0, m_resolution.x };
      std::vector<std::future<void>> tasks;
      for (uint32_t i = 0; i < m_num_cores; ++i)
      {
         pixel_range y_range = { i * y_pixel_interval, (i + 1) * y_pixel_interval };
         if (y_range.end > m_resolution.y) y_range.end = m_res_y;
         tasks.emplace_back(std::async(std::launch::async, &fractal_renderer::render_range, this, x_range, y_range));
      }

      for (auto& task : tasks) 
      {
         task.get();
      }
   }

   void render_range(pixel_range x_range, pixel_range y_range) override
   {
      for (uint32_t j = y_range.begin; j < y_range.end; ++j)
      {
         for (uint32_t i = x_range.begin; i < x_range.end; ++i)
         {
            // TODO: Try stuffing a uint32_t into here!
            const std::array<uint8_t, 4> pixel_colour = m_fractal_generator->get_pixel_color(i, j);
            const uint64_t current_idx = (j * m_res_x + i) * 4;
            m_fractal_data[current_idx + 0] = pixel_colour[0]; // R
            m_fractal_data[current_idx + 1] = pixel_colour[1]; // G
            m_fractal_data[current_idx + 2] = pixel_colour[2]; // B
            m_fractal_data[current_idx + 3] = pixel_colour[3]; // A
         }
      }
   }
private:

};

class render_context_factory
{
public:
   static std::unique_ptr<render_context> create_cpu_context()
   {
      return std::make_unique<cpu_render_context>();
   }
}


class fractal_renderer
{
public:
   //using pixel_buffer_t = std::vector<uint8_t>;

   fractal_renderer(
      acceleration acceleration,
      fc::resolution resolution,
      std::unique_ptr<fc::fractal_generator> generator
   );

   void render();
   // void render_range(pixel_range x_range, pixel_range y_range);
   const pixel_buffer_t& data() const { return m_fractal_data; }
   uint32_t core_count() const { return m_num_cores; }


private:
   //uint32_t m_res_x;
   //uint32_t m_res_y;
   //uint32_t m_num_cores;
   std::unique_ptr<fc::fractal_generator> m_fractal_generator;
   std::unique_ptr<render_context> m_render_context;
   //pixel_buffer_t m_fractal_data;
};

#endif // __FRACTAL_VIEWER_FRACTAL_RENDERER_H__