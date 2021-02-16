#ifndef __FRACTAL_CORE_FRACTAL_RENDERER_H__
#define __FRACTAL_CORE_FRACTAL_RENDERER_H__

#include "resolution.h"
#include "fractal_generator.h"

namespace fractal_core
{
    struct pixel_range
    {
        uint32_t begin;
        uint32_t end;
    };

    enum class acceleration
    {
        CPU,
        CUDA,
        OPENCL,
    };

    class renderer
    {
    public:
        renderer(acceleration acceleration, resolution resolution, std::unique_ptr<fractal_generator> generator);

        void render();

        void set_acceleration(acceleration acceleration);
        void set_fractal_generator(std::unique_ptr<fractal_generator> generator);
        void set_fractal_colour_algorithm(colouring::colour_algorithm_func_t func);
        void set_fractal_colour_palette(palette::colour_from_palette_func_t func);

        void set_fractal_resolution(int resolution) const;
        int32_t fractal_resolution() const;
        
        void set_fractal_zoom(zoom_action zoom) const;
        zoom_action fractal_zoom() const;

        void set_fractal_offset(offset_action offset) const;

        complex_bounds get_bounds() const { return m_generator->get_bounds(); }
        void reset() const;

    private:
        acceleration m_acceleration;
        resolution m_resolution;
        std::unique_ptr<fractal_generator> m_generator;
    };
}
#endif // __FRACTAL_CORE_FRACTAL_RENDERER_H__