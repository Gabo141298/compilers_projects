#Minimum version of CMake to build this project
cmake_minimum_required(VERSION 2.6)
set(CMAKE_VERBOSE_MAKEFILE ON)
include_directories(/usr/lib/llvm/include/)

project(parser)

set(CXX "clang++")
set(CMAKE_CXX_FLAGS_DEBUG "-Wall -W -Werror")
set(CMAKE_CXX_FLAGS "-g -I/usr/lib/llvm-7/include -D_GNU_SOURCE -D__STDC_CONSTANT_MACROS -D__STDC_FORMAT_MACROS -D__STDC_LIMIT_MACROS")

#Defines subdirectory
add_subdirectory(src/)
