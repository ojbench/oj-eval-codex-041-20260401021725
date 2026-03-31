cmake_minimum_required(VERSION 3.10)
project(problem_041_map_extra)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if (CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
  add_compile_options(-O2 -pipe -static -s)
endif()

add_executable(code src/main.cpp)

# Ensure headers are found
include_directories(${CMAKE_SOURCE_DIR})
