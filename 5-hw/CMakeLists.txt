cmake_minimum_required(VERSION 3.3)
project(5_hw)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    fl.c
    fl.h
    process.c
    wordstore13.c
    ws13.h)

add_executable(5_hw ${SOURCE_FILES})