#include "application.h"

// TODO: THE ARTICLE FOR COLOURING https://www.paridebroggi.com/blogpost/2015/05/06/fractal-continuous-coloring/
// and for generating colour palettes - https://bpb.opendns.com/b/https/www.krazydad.com/tutorials/makecolors.php
// https://softologyblog.wordpress.com/2019/03/23/automatic-color-palette-creation/
//
// TODO: Fix resolution changes after zooming
// TODO: Fix zooming with mouse, doesnt work properly
// TODO: Fix zoom out! Doesn't quite work properly
// TODO: Logging
// TODO: Implement different colouring strategies
// TODO: Histogram colouring - single colour range over all histogram
// TODO: Histogram with multiple colour ranges over the histogramW
// TODO: Get imgui working
// TODO: Implement UI
// TODO: Plug in all parameters to UI
// TODO: Investigate more speedups
// TODO: Colouring goes black when zoomed in and resolution increased too much

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