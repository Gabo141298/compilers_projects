#Minimum version of CMake to build this project
cmake_minimum_required(VERSION 2.6)
set(CMAKE_VERBOSE_MAKEFILE ON)
include_directories(/usr/lib/llvm/include/)

project(parser)

set(CXX "clang++")
set(CMAKE_CXX_FLAGS_DEBUG "-Wall -W -Werror")
set(CMAKE_CXX_FLAGS "-O3 -Wall -W -pedantic")

#Defines subdirectory
add_subdirectory(src/)
