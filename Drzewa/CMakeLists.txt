cmake_minimum_required(VERSION 3.1)
project(ASD)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    drzewa.h
    drzewa.cpp
    )

add_executable(Drzewa ${SOURCE_FILES} )
