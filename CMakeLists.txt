cmake_minimum_required(VERSION 3.14)

project(
    FractalViewer
    VERSION 0.0.1
    DESCRIPTION "Interactive Fractal Viewer"
    LANGUAGES CXX
)

# Disable the ZERO_CHECK project generation
set(CMAKE_SUPPRESS_REGENERATION true)

# Check if cuda is supported on this system 
# and enable it in cmake if so
include(CheckLanguage)
check_language(CUDA)
if(CMAKE_CUDA_COMPILER)
    enable_language(CUDA)
else()
    message(STATUS "No CUDA support")
endif()

# Third party libs
add_subdirectory(vendor)

# Fractal Library
add_subdirectory(FractalCore)

# Fractal Viewer
add_subdirectory(FractalViewer)