cmake_minimum_required(VERSION 2.8.4)
project(ThreadSafeCache)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -g -Wall")

# Generate shared library libThreadCache.so file.
ADD_LIBRARY(ThreadSafeCache SHARED ThreadSafeCache.cpp)

add_executable(Example1.out Example1.cpp)

target_link_libraries(Example1.out ThreadSafeCache pthread)
