#include "fractal_renderer.h"

namespace fractal_core
{
    renderer::renderer(acceleration acceleration, resolution resolution, std::unique_ptr<fractal_generator> generator)
        : m_acceleration(acceleration)
        , m_resolution(resolution)
        , m_generator(std::move(generator))
    {

    }

    void renderer::render()
    {

    }

    void renderer::set_acceleration(acceleration acceleration)
    {
        m_acceleration = acceleration;
    }

    void renderer::set_fractal_generator(std::unique_ptr<fractal_generator> generator)
    {
        m_generator = std::move(generator);
    }

    void renderer::set_fractal_colour_algorithm(colouring::colour_algorithm_func_t func)
    {
        m_generator->set_fractal_colouring_algorithm(std::move(func));
    }

    void renderer::set_fractal_colour_palette(palette::colour_from_palette_func_t func)
    {
        m_generator->set_fractal_colour_palette(std::move(func));
    }

    void renderer::set_fractal_resolution(int32_t resolution) const
    {
        m_generator->set_fractal_resolution(resolution);
    }

    int32_t renderer::fractal_resolution() const
    {
        return m_generator->fractal_resolution();
    }

    void renderer::set_fractal_zoom(zoom_action zoom) const
    {
        m_generator->set_fractal_zoom(zoom);
    }

    zoom_action renderer::fractal_zoom() const
    {
        return m_generator->fractal_zoom();
    }

    void renderer::set_fractal_offset(offset_action offset) const
    {
        m_generator->set_fractal_offset(offset);
    }

    void renderer::reset() const
    {
        m_generator->reset_bounds();
        m_generator->reset_resolution();
        m_generator->reset_zoom();
    }

}