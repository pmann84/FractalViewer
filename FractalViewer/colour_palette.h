#pragma once

#include <array>
#include <initializer_list>
#include <vector>

class colour
{
public:
   colour(float r, 
          float g, 
          float b, 
          float a = 1.0f)
   {
      m_colour[0] = r;
      m_colour[1] = g;
      m_colour[2] = b;
      m_colour[3] = a;
   }

   std::array<unsigned int, 4> rgba() const
   {
      return {
         static_cast<unsigned int>(m_colour[0] * 255),
         static_cast<unsigned int>(m_colour[1] * 255),
         static_cast<unsigned int>(m_colour[2] * 255),
         static_cast<unsigned int>(m_colour[3] * 255)
      };
   }

   float r() const { return m_colour[0]; }
   float g() const { return m_colour[1]; }
   float b() const { return m_colour[2]; }
   float a() const { return m_colour[3]; }

   friend colour lerp(const colour& a, const colour& b, float p);

private:
   std::array<float, 4> m_colour;
};

inline float lerp(float a, float b, float p)
{
   return a + p * (b - a);
}

inline colour lerp(const colour& col_a, const colour& col_b, float p)
{
   const float r = lerp(col_a.r(), col_b.r(), p);
   const float g = lerp(col_a.g(), col_b.g(), p);
   const float b = lerp(col_a.b(), col_b.b(), p);
   const float a = lerp(col_a.a(), col_b.a(), p);
   return { r, g, b, a };
}

// A palette of discrete colours of arbitrary size
class colour_palette
{
public:
   colour_palette(std::initializer_list<colour> palette)
   {
      m_palette = { palette };
   }

   std::array<unsigned int, 4> get_colour(unsigned int idx)
   {
      return m_palette[idx % m_palette.size()].rgba();
   }

   std::array<unsigned int, 4> get_colour(float p)
   {
      float fidx = p * m_palette.size();
      float fractpart, intpart;
      fractpart = modf(fidx, &intpart);
      colour first = m_palette[intpart];
      colour last = m_palette[intpart + 1];
      return lerp(first, last, fractpart).rgba();
   }

   std::array<unsigned int, 4> get_colour(unsigned int idx, unsigned int max_idx)
   {
      const float prop = idx / static_cast<float>(max_idx); // Between 0 and 1
      const float index_prop = prop * m_palette.size(); // The float index that corresponds to prop
      float fractpart, intpart;
      fractpart = modf(index_prop, &intpart);
      colour first = m_palette[intpart];
      colour last = m_palette[intpart + 1];
      return lerp(first, last, fractpart).rgba();
      //return m_palette[static_cast<int>(index_prop)].rgba();
   }

private:
   std::vector<colour> m_palette;
};