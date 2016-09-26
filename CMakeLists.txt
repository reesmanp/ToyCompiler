cmake_minimum_required(VERSION 3.2.2) # CMake version check
project(ToyCompiler)               # Create project "simple_example"
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c99") # Enable c99 standard

set(SOURCE_FILES main.c Utils/Util.c Intro/A_.c Test/prog1.c Test/prog1Main.c Lex/errormsg.c Lex/tokens.h Lex/Tiger.l)

find_package(FLEX)

FLEX_TARGET(Tiger Lex/Tiger.l  ${CMAKE_CURRENT_SOURCE_DIR}/Lex/tiger.c)

include_directories(${CMAKE_CURRENT_BINARY_DIR} Lex Utils)
add_executable(ToyCompiler
        ${SOURCE_FILES}
        Lex/Tiger.c
        ${FLEX_Tiger_OUTPUTS})