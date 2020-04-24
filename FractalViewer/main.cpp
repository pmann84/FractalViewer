#include "application.h"

// TODO: THE ARTICLE FOR COLOURING https://www.paridebroggi.com/blogpost/2015/05/06/fractal-continuous-coloring/
// and for generating colour palettes - https://bpb.opendns.com/b/https/www.krazydad.com/tutorials/makecolors.php
// https://softologyblog.wordpress.com/2019/03/23/automatic-color-palette-creation/
//
// TODO: Make some more colour palettes! :D
// TODO: Implement zooming properly - needs to zoom in and out, also needs to handle the change in fractal resolution
// TODO: Histogram colouring - single colour range over all histogram
// TODO: Histogram with multiple colour ranges over the histogram
// TODO: Work out how to plug in arbitrary fractal parameters to the ui e.g. julia parameter
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