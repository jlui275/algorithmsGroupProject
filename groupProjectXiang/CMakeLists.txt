cmake_minimum_required(VERSION 3.13)
project(groupProject)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -lmingw32")
set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++")

add_executable(groupProject main.cpp SDL_Plotter.h point.h line.h color_rgb.cpp color_rgb.h)
target_link_libraries(groupProject SDL2main SDL2 SDL2_mixer)