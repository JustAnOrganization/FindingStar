cmake_minimum_required(VERSION 3.3)
project(FinalProject)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp glad/glad.c Game.cpp Game.h Player.cpp Player.h ModelImporter.cpp ModelImporter.h Table.cpp Table.h Basic.h Utils.cpp Utils.h TextRenderer.cpp TextRenderer.h)

set(SDL2_INCLUDE_DIR /usr/local/Cellar/sdl2/2.0.8/include/SDL2/)
set(SDL2_LIBRARY /usr/local/Cellar/sdl2/2.0.8/lib/libSDL2.so)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIR})

add_executable(FinalProject ${SOURCE_FILES})
target_link_libraries(FinalProject ${SDL2_LIBRARY})