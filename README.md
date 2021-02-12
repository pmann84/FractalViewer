# FractalViewer
This is a simple fractal viewer written in C++ using SFML for graphics and ImGui for interactivity.

## Info
- Multithreaded CPU based fractal renderer
- Ability to pick from predefined colour palettes (limited - need to add more)
- Ability to render different fractals (hardcoded to render only Mandelbrot and Julia sets)
- Ability to choose different colouring algorithms (limited to escape-time and continuous potential)

## Development
### Prerequisites
CMake (minimum version 3.14)
C++14 enabled compiler

### Build
Do an out of source build in either Release or Debug
```
mkdir cmake-debug
cd cmake-debug
cmake -DCMAKE_BUILD_TYPE=Release ..
cmake --build . --config Release 
```
Note if using the Visual Studio generator you can omit the `CMAKE_BUILD_TYPE` and just pass in the `--config` option on the build command.

## Screenshots
![image](https://user-images.githubusercontent.com/9325892/80220502-d7352c00-863b-11ea-917c-ba2c0c479f7d.png)
![image](https://user-images.githubusercontent.com/9325892/80220639-0b105180-863c-11ea-8b2b-00aee2229ca1.png)
