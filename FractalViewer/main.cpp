#include <SFML/Graphics.hpp>
#include <iostream>
#include <complex>
#include "application.h"

struct fractal_resolution_info
{
   int delta;
   int min;
   int max;
};

struct resolution
{
   unsigned int width;
   unsigned int height;

   sf::VideoMode video_mode() const
   {
      return { width, height };
   }

   static resolution from_video_mode(sf::VideoMode video_mode)
   {
      return resolution{ video_mode.width, video_mode.height };
   }
};

template<typename T>
struct complex_range
{
   std::complex<T> min;
   std::complex<T> max;
};

sf::Color get_colour_for_iteration_count(const unsigned int iteration, const unsigned int max_iterations)
{
   if (iteration == max_iterations)
   {
      return { 255, 255,255, 255 };
   }
   const auto colour_grad = static_cast<sf::Uint8>(iteration * (255 / max_iterations));
   return { 0, 0, colour_grad, 255 };
}

std::complex<double> complex_from_pixel(unsigned int x_pixel, unsigned int x_res, unsigned int y_pixel, unsigned int y_res, const complex_range<double> range)
{
   const double xmin = range.min.real();
   const double xmax = range.max.real();
   const double ymin = range.min.imag();
   const double ymax = range.max.imag();
   return { xmin + x_pixel * ((xmax - xmin) / x_res), ymin + y_pixel * ((ymax - ymin) / y_res) };
}

sf::Color get_julia_pixel_colour(unsigned int x, unsigned int y, const resolution& window_res, const int fractal_res, const double& zoom)
{
   // Get scaled fractal coordinate z0
   const complex_range<double> range {
      std::complex<double>(-2.0, -1.5),
      std::complex<double>(2.0, 1.5)
   };

   // TODO: For zoom, need to recalculate the range, first get the mouse position
   // and calculate the complex coordinate equivalent, then calculate the range of the
   // original and add this to the mouse position to get the new range
   const std::complex<double> c(-0.8, 0.156);
   std::complex<double> zn = complex_from_pixel(
      x, 
      window_res.width, 
      y, 
      window_res.height, 
      range);
   // Initialise iteration count to 0
   int iteration = 0;
   // Set a max iteration count
   const int max_iterations = fractal_res;
   // condition for general polynomial for some R > 0 such that |c| < R^2 - R (Mandelbrot has R=2)
   const double escape_r = 2.0;
   const double r_cond = std::pow(escape_r, 2.0) - escape_r;

   while (zn.real() * zn.real() + zn.imag() * zn.imag() < escape_r && iteration < max_iterations)
   {
      // keep updating until condition reached or max iterations hit
      zn = zn * zn + c;
      ++iteration;
   }
   // Assign colour based on iteration value
   return get_colour_for_iteration_count(iteration, max_iterations);
}

sf::Color get_mandelbrot_pixel_colour(unsigned int x, unsigned int y, const resolution& window_res, const int fractal_res, const double& zoom)
{
   // Mandelbrot (-2.5 - i) to (1 + i)
   // Get scaled mandelbrot coordinate z0
   const complex_range<double> range {
   std::complex<double>(-3.0, -1.5),
   std::complex<double>(1.5, 1.5)
   };
   const std::complex<double> c = complex_from_pixel(
      x, 
      window_res.width, 
      y, 
      window_res.height, 
      range);
   // Initialise z to 0
   std::complex<double> zn(0.0, 0.0);
   // Initialise iteration count to 0
   int iteration = 0;
   // Set a max iteration count
   const int max_iterations = fractal_res;
   // check whether |z| < 4
   // condition for general polynomial for some R > 0 such that |c| < R^2 - R (Mandelbrot has R=2)
   const double escape_r = 2.0;
   while (zn.real() * zn.real() + zn.imag() * zn.imag() < escape_r && iteration < max_iterations)
   {
      // keep updating until condition reached or max iterations hit
      zn = zn * zn + c;
      ++iteration;
   }
   // Assign colour based on iteration value
   return get_colour_for_iteration_count(iteration, max_iterations);
}

void handle_key_press(
   sf::Keyboard::Key key_code, 
   int& fractal_resolution, 
   const fractal_resolution_info& f_res, 
   double& zoom, 
   bool& state_changed)
{
   double zoom_factor = 1.3;
   switch (key_code)
   {
   case sf::Keyboard::Q:
   {
      fractal_resolution -= f_res.delta;
      if (fractal_resolution <= f_res.min)
      {
         fractal_resolution = f_res.min;
      }
      state_changed = true;
      break;
   }
   case sf::Keyboard::E:
   {
      fractal_resolution += f_res.delta;
      if (fractal_resolution >= f_res.max)
      {
         fractal_resolution = f_res.max;
      }
      state_changed = true;
      break;
   }
   case sf::Keyboard::LBracket:
   {
      zoom /= zoom_factor;
      if (zoom <= 1.0)
      {
         zoom = 1.0;
      }
      state_changed = true;
      break;
   }
   case sf::Keyboard::RBracket:
   {
      zoom *= zoom_factor;
      state_changed = true;
      break;
   }
   default: break;
   }
}

int main()
{
   application app("Fractal Viewer");

   while (app.is_open())
   {
      app.handle_events();
      app.update();

      app.display();
   }

   return 0;

   //// Renderer state parameters
   //bool state_changed = true;
   //int fractal_resolution = 30;
   //fractal_resolution_info f_res{ 4, 1, 1000 };
   //double zoom = 1.0;

   //while (window.isOpen())
   //{
   //   // Poll Events
   //   sf::Event event;
   //   while (window.pollEvent(event))
   //   {
   //      switch (event.type)
   //      {
   //         case sf::Event::Closed:
   //         {
   //            window.close();
   //            break;
   //         }
   //         case sf::Event::KeyPressed:
   //         {
   //            handle_key_press(event.key.code, fractal_resolution, f_res, zoom, state_changed);
   //            break;
   //         }
   //         case sf::Event::MouseWheelMoved:
   //         {
   //            double zoom_factor = 1.3;
   //            if (event.mouseWheel.delta == -1)
   //            {
   //               zoom /= zoom_factor;
   //               if (zoom <= 1.0)
   //               {
   //                  zoom = 1.0;
   //               }
   //               state_changed = true;
   //            }
   //            else
   //            {
   //               zoom *= zoom_factor;
   //               state_changed = true;
   //            }
   //            std::cout << "mouse x: " << event.mouseWheel.x << std::endl;
   //            std::cout << "mouse y: " << event.mouseWheel.y << std::endl;
   //         }
   //         default: break;
   //      }
   //   }
   //    image.setPixel(i, j, get_julia_pixel_colour(i, j, resolution::from_video_mode(desktop_res), fractal_resolution, zoom));
   //}
}