#include "fractal_renderer.h"

fractal_renderer::fractal_renderer(
   sf::VideoMode resolution, 
   std::unique_ptr<fractal_generator> generator,
   int fractal_resolution,
   int fractal_zoom)
      : m_resolution(resolution)
      , m_fractal_generator(std::move(generator))
      , m_fractal_resolution(fractal_resolution)
      , m_fractal_zoom(fractal_zoom)
{
}

void fractal_renderer::render(sf::Image& image)
{
   for (unsigned int i = 0; i < m_resolution.width; ++i)
   {
      for (unsigned int j = 0; j < m_resolution.height; ++j)
      {
         const std::array<unsigned int, 4> pixel_colour = m_fractal_generator->get_pixel_color(i, j, m_fractal_resolution, m_resolution);
         image.setPixel(i, j, sf::Color(pixel_colour[0], pixel_colour[1], pixel_colour[2], pixel_colour[3]));
      }
   }
}

void fractal_renderer::set_fractal_resolution(int resolution)
{
   m_fractal_resolution = resolution;
}

void fractal_renderer::set_fractal_zoom(double zoom)
{
   m_fractal_zoom = zoom;
}
