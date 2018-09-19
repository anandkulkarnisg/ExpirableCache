cmake_minimum_required(VERSION 2.8.4)
project(ExpirableCache)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -g -Wall")

# Generate shared library libThreadCache.so file.
ADD_LIBRARY(ExpirableCache SHARED ExpirableCache.cpp)

add_executable(Example1.out Example1.cpp)
add_executable(Example2.out Example2.cpp)

target_link_libraries(Example1.out ExpirableCache pthread)
target_link_libraries(Example2.out ExpirableCache pthread)
