cmake_minimum_required(VERSION 3.2.2) # CMake version check
project(ToyCompiler)               # Create project "simple_example"
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c99") # Enable c99 standard

set(SOURCE_FILES main.c Utils/Util.c Intro/A_.c Test/prog1.c Test/prog1Main.c)
add_executable(ToyCompiler ${SOURCE_FILES})       # Add executable target with source files listed in SOURCE_FILES variable