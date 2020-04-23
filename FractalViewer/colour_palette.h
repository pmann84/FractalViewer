#pragma once
#include "colour.h"

namespace palette
{
   namespace
   {
      float get(float t, float amplitude, float frequency, float horizontal_offset, float vertical_offset)
      {
         static const float pi = 3.141592654f;
         return amplitude * sin(2.0f*pi*(frequency*t + horizontal_offset)) + vertical_offset;
      }

      colour get(float t, colour amplitude, colour frequency, colour horizontal_offset, colour vertical_offset)
      {
         const float r = get(t, amplitude.r(), frequency.r(), horizontal_offset.r(), vertical_offset.r());
         const float g = get(t, amplitude.g(), frequency.g(), horizontal_offset.g(), vertical_offset.g());
         const float b = get(t, amplitude.b(), frequency.b(), horizontal_offset.b(), vertical_offset.b());
         return { r, g, b };
      }
   }

   namespace default_palette
   {
      static colour get(float t)
      {
         const colour amplitude = { 0.5f, 0.5f, 0.5f };
         const colour frequency = { 0.00390635f, 0.00390635f, 0.00390635f };
         const colour horizontal_off = { 0.644f, 1.76067f, 2.87733f };
         const colour vertical_off = { 0.5f, 0.5f, 0.5f };
         return palette::get(t, amplitude, frequency, horizontal_off, vertical_off);
      }
   }

   namespace rainbow
   {
      static colour get(float t)
      {
         const colour amplitude = { 0.5f, 0.5f, 0.5f };
         const colour frequency = { 0.00390635f, 0.00390635f, 0.00390635f };
         const colour horizontal_off = { 0.0f, 0.6666f, 1.333333f };
         const colour vertical_off = { 0.5f, 0.5f, 0.5f };
         return palette::get(t, amplitude, frequency, horizontal_off, vertical_off);
      }
   }
}

//#include <array>
//#include <initializer_list>
//#include <vector>

//namespace palette
//{
//   static colour get(float x)
//   {
//      colour amplitude = { 0.5f, 0.5f, 0.5f };
//      colour frequency = { 0.00390635f, 0.00390635f, 0.00390635f };
//      colour horizontal_off = { 0.644f, 1.76067f, 2.87733f };
//      colour vertical_off = { 0.5f, 0.5f, 0.5f };
//      static const float pi = 3.141592654f;
//      const float r = amplitude.r() * sin(2.0f*pi*(frequency.r()*x + horizontal_off.r())) + vertical_off.r();
//      const float g = amplitude.g() * sin(2.0f*pi*(frequency.g()*x + horizontal_off.g())) + vertical_off.g();
//      const float b = amplitude.b() * sin(2.0f*pi*(frequency.b()*x + horizontal_off.b())) + vertical_off.b();
//      return { r, g, b };
//   }
//}

//inline float lerp(float a, float b, float p)
//{
//   return a + p * (b - a);
//}
//
//inline colour lerp(const colour& col_a, const colour& col_b, float p)
//{
//   const float r = lerp(col_a.r(), col_b.r(), p);
//   const float g = lerp(col_a.g(), col_b.g(), p);
//   const float b = lerp(col_a.b(), col_b.b(), p);
//   const float a = lerp(col_a.a(), col_b.a(), p);
//   return { r, g, b, a };
//}
//
//// A palette of discrete colours of arbitrary size
//class colour_palette
//{
//public:
//   colour_palette(std::initializer_list<colour> palette)
//   {
//      m_palette = { palette };
//   }
//
//   std::array<unsigned int, 4> get_colour(unsigned int idx)
//   {
//      return palette::get(static_cast<float>(idx)).rgba();
//      //return m_palette[idx % m_palette.size()].rgba();
//   }
//
//   //std::array<unsigned int, 4> get_colour(float p)
//   //{
//   //   float fidx = p * m_palette.size();
//   //   float fractpart, intpart;
//   //   fractpart = modf(fidx, &intpart);
//   //   colour first = m_palette[intpart];
//   //   colour last = m_palette[intpart + 1];
//   //   return lerp(first, last, fractpart).rgba();
//   //}
//
//   //std::array<unsigned int, 4> get_colour(unsigned int idx, unsigned int max_idx)
//   //{
//   //   const float prop = idx / static_cast<float>(max_idx); // Between 0 and 1
//   //   const float index_prop = prop * m_palette.size(); // The float index that corresponds to prop
//   //   float fractpart, intpart;
//   //   fractpart = modf(index_prop, &intpart);
//   //   colour first = m_palette[intpart];
//   //   colour last = m_palette[intpart + 1];
//   //   return lerp(first, last, fractpart).rgba();
//   //   //return m_palette[static_cast<int>(index_prop)].rgba();
//   //}
//
//private:
//   std::vector<colour> m_palette;
//};