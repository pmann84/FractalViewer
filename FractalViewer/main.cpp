#include "application.h"

// TODO: Logging
//struct fractal_resolution_info
//{
//   int delta;
//   int min;
//   int max;
//};
//
//struct resolution
//{
//   unsigned int width;
//   unsigned int height;
//
//   sf::VideoMode video_mode() const
//   {
//      return { width, height };
//   }
//
//   static resolution from_video_mode(sf::VideoMode video_mode)
//   {
//      return resolution{ video_mode.width, video_mode.height };
//   }
//};
//
//void handle_key_press(
//   sf::Keyboard::Key key_code, 
//   int& fractal_resolution, 
//   const fractal_resolution_info& f_res, 
//   double& zoom, 
//   bool& state_changed)
//{
//   double zoom_factor = 1.3;
//   switch (key_code)
//   {
//   case sf::Keyboard::Q:
//   {
//      fractal_resolution -= f_res.delta;
//      if (fractal_resolution <= f_res.min)
//      {
//         fractal_resolution = f_res.min;
//      }
//      state_changed = true;
//      break;
//   }
//   case sf::Keyboard::E:
//   {
//      fractal_resolution += f_res.delta;
//      if (fractal_resolution >= f_res.max)
//      {
//         fractal_resolution = f_res.max;
//      }
//      state_changed = true;
//      break;
//   }
//   case sf::Keyboard::LBracket:
//   {
//      zoom /= zoom_factor;
//      if (zoom <= 1.0)
//      {
//         zoom = 1.0;
//      }
//      state_changed = true;
//      break;
//   }
//   case sf::Keyboard::RBracket:
//   {
//      zoom *= zoom_factor;
//      state_changed = true;
//      break;
//   }
//   default: break;
//   }
//}

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
   //}
}