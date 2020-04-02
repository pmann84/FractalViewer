#include "application.h"

// TODO: Implement scrolling with arrow keys
// TODO: Speed up image render - cache parts of the image so they dont need to be rendered again?
// TODO: Logging
// TODO: Implement different colouring strategies
// TODO: Implement UI
// TODO: Plug in all parameters to UI
// TODO: Remove sf::Videomode from the fractal renderer classes
// TODO: Remove sf::Image from the renderer call to render. We should just pass in a vector of unsigned char* or something and then add that data to an image

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
}