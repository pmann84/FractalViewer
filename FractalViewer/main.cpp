#include "application.h"

// TODO: Fix resolution changes after zooming
// TODO: Fix zooming with mouse, doesnt work properly
// TODO: Fix zoom out! Doesn't quite work properly
// TODO: Logging
// TODO: Implement different colouring strategies
// TODO: Get imgui working
// TODO: Implement UI
// TODO: Plug in all parameters to UI
// TODO: Investigate more speedups

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