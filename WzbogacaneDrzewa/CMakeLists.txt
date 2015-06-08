cmake_minimum_required(VERSION 3.1)
project(ASD)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

add_executable(WzbogacaneDrzewa wzbogacone_drzewa.cpp wzbogacone_drzewa.h sum_tree.h)
