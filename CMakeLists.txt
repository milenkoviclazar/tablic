cmake_minimum_required(VERSION 3.7)
project(tablic)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES dp_simple.cpp)
add_executable(tablic ${SOURCE_FILES})