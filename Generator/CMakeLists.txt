cmake_minimum_required(VERSION 3.15)
project(Generator)

set(CMAKE_CXX_STANDARD 14)

include_directories(generator)

add_executable(Generator
        generator/generator.cpp
        generator/plane.cpp
        generator/plane.h
        generator/write.cpp
        generator/write.h generator/box.cpp generator/box.h)
