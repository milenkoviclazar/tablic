cmake_minimum_required(VERSION 3.7)
project(tablic)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp
        utils.cpp
        utils.h
        greedy.cpp
        greedy.h
        backtrack6.cpp
        backtrack6.h
        backtrack.cpp
        backtrack.h
        genetic.cpp
        genetic.h)

add_executable(tablic ${SOURCE_FILES})

set(SOURCE_FILES ga_training.cpp
        utils.cpp
        utils.h
        greedy.cpp
        greedy.h
        backtrack6.cpp
        backtrack6.h
        backtrack.cpp
        backtrack.h
        genetic.cpp
        genetic.h)

add_executable(training ${SOURCE_FILES})