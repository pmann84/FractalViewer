#pragma once

#include <functional>

// Signature for a function that generates a float given
// - the number of iterations it took to converge
// - the max number of iterations
// - the final absolute value of z at the end of the iteration


namespace colouring
{
   using colour_algorithm_func_t = std::function<float(const uint32_t, const uint32_t, double)>;

   namespace algorithm
   {
      static float escape_time(const uint32_t iteration_count, const uint32_t max_iterations, double)
      {
         return static_cast<float>(iteration_count) / static_cast<float>(max_iterations);
      }

      static float continuous_potential(const uint32_t iteration_count, const uint32_t max_iterations, double z_abs)
      {
         const float iter_p = static_cast<float>(iteration_count) + 1.0f - logf(logf(z_abs) / (logf(2.0f))) / logf(2.0f);
         return iter_p / static_cast<float>(max_iterations);
      }
   }
}
   //// TODO: Make these just return a single uint32_t to put into the buffer (might not be possible)
   //inline std::array<uint8_t, 4> escape_time_colour(const uint32_t iteration_count, const uint32_t max_iterations, double)
   //{
   //   //const float p = static_cast<float>(iteration_count);
   //   const float p = static_cast<float>(iteration_count) * 256.0f / static_cast<float>(max_iterations);
   //   auto colour = palette::default_palette::get(static_cast<float>(p)).rgba();
   //   return {
   //      static_cast<uint8_t>(colour[0] * 255),
   //      static_cast<uint8_t>(colour[1] * 255),
   //      static_cast<uint8_t>(colour[2] * 255),
   //      static_cast<uint8_t>(colour[3] * 255)
   //   };
   //}

   //inline std::array<uint8_t, 4> continuous_potential(const uint32_t iteration_count, const uint32_t max_iterations, double z_abs)
   //{
   //   const float iter_p = static_cast<float>(iteration_count) + 1.0f - logf(logf(z_abs) / (logf(2.0f))) / logf(2.0f);
   //   const float p = iter_p * 256.0f / static_cast<float>(max_iterations);
   //   auto colour = palette::default_palette::get(static_cast<float>(p)).rgba();
   //   return {
   //      static_cast<uint8_t>(colour[0] * 255),
   //      static_cast<uint8_t>(colour[1] * 255),
   //      static_cast<uint8_t>(colour[2] * 255),
   //      static_cast<uint8_t>(colour[3] * 255)
   //   };
   //}
//}