#pragma once

#include <array>

class colour
{
public:
   colour()
      : m_channels{ 0.0f, 0.0f, 0.0f, 1.0f }
   {
   }

   colour(float r, float g, float b, float a = 1.0f)
      : m_channels{ r, g, b, a }
   {
   }

   colour(float c[4]) : m_channels{ c[0], c[1], c[2], c[3] }
   {
   }

   colour(uint32_t c)
      : m_channels{
         static_cast<float>(c & 0x000000ff) / 255.0f,
         static_cast<float>((c & 0x0000ff00) >> 8) / 255.0f,
         static_cast<float>((c & 0x00ff0000) >> 16) / 255.0f,
         static_cast<float>((c & 0xff000000) >> 24) / 255.0f }
   {
   }

   uint32_t to_int() const
   {
      // Convert internal format to 32 bit colour representation
      // Bits 0 - 7 are the red channel
      // bits 8 - 15 the green channel,
      // bits 16 - 23 the blue channel,
      // and bits 24 -  31 the alpha channel
      const uint8_t r = static_cast<uint8_t>(m_channels[0] * 255);
      const uint8_t g = static_cast<uint8_t>(m_channels[1] * 255);
      const uint8_t b = static_cast<uint8_t>(m_channels[2] * 255);
      const uint8_t a = static_cast<uint8_t>(m_channels[3] * 255);
      return a | (b << 8) | (g << 16) | (r << 24);
   }

   std::array<uint8_t, 4> rgba() const
   {
      return {
         static_cast<uint8_t>(m_channels[0] * 255),
         static_cast<uint8_t>(m_channels[1] * 255),
         static_cast<uint8_t>(m_channels[2] * 255),
         static_cast<uint8_t>(m_channels[3] * 255)
      };
   }

   float r() const { return m_channels[0]; }
   float g() const { return m_channels[1]; }
   float b() const { return m_channels[2]; }
   float a() const { return m_channels[3]; }
   void set(float r, float g, float b, float a = 1.0f)
   {
      m_channels[0] = r;
      m_channels[1] = g;
      m_channels[2] = b;
      m_channels[3] = a;
   }

private:
   std::array<float, 4> m_channels;
};
