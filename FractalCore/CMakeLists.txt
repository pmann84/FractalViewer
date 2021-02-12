set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(PROJECT_NAME "FractalCore")

add_library(${PROJECT_NAME})

target_sources(
	${PROJECT_NAME}
	PRIVATE
                julia_generator.cpp
                mandelbrot_generator.cpp
	PUBLIC
                colour.h
                colour_algorithms.h
                colour_palette.h
                complex_bounds.h
                fractal_generator.h
                fractal_generator_factory.h
                input_actions.h
                julia_generator.h
                mandelbrot_generator.h
)

# This tells applications that use this
# library what the include directory is
target_include_directories(
        ${PROJECT_NAME}
	PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)