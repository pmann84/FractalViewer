#pragma once
#include <array>
#include <complex>

#include <SFML/Window.hpp>

template<typename T>
struct complex_range
{
   std::complex<T> min;
   std::complex<T> max;
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

   inline std::complex<double> complex_from_pixel(unsigned int x_pixel, unsigned int x_res, unsigned int y_pixel, unsigned int y_res, const complex_range<double> range)
   {
      const double xmin = range.min.real();
      const double xmax = range.max.real();
      const double ymin = range.min.imag();
      const double ymax = range.max.imag();
      return { xmin + x_pixel * ((xmax - xmin) / x_res), ymin + y_pixel * ((ymax - ymin) / y_res) };
   }
}

class fractal_generator
{
public:
   virtual ~fractal_generator() = default;

   virtual std::array<unsigned int, 4> get_pixel_color(unsigned int x, unsigned int y, const int fractal_resolution, const sf::VideoMode window_res) = 0;
};
