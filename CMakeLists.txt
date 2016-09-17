cmake_minimum_required(VERSION 3.6)
project(graph)

include_directories(src)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -std=c++14")

add_subdirectory(src)
add_subdirectory(test)
