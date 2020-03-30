#include "application.h"

// TODO: Logging
// TODO: Implement different colouring strategies
// TODO: Implement updatable fractal resolution
// TODO: Implement zooming
// TODO: Implement UI
// TODO: Plug in all parameters to UI

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