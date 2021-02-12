#pragma once

struct zoom_action
{
   double factor; // Factor to zoom in by
   int32_t x; // x pixel of zoom centre
   int32_t y; // y pixel of zoom centre
};

struct offset_action
{
   int32_t x;
   int32_t y;
};