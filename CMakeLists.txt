cmake_minimum_required(VERSION 3.1)
project(graph)

include_directories(include)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -std=c++14")

add_subdirectory(test)
