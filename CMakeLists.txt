cmake_minimum_required(VERSION 3.7)
project(tablic)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp
        backtrack.cpp
        backtrack.h
        greedy.cpp
        greedy.h
        utils.cpp
        utils.h)

add_executable(tablic ${SOURCE_FILES})