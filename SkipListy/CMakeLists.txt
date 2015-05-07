cmake_minimum_required(VERSION 3.1)
project(ASD)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

add_executable(SkipListy skip_listy.h skip_listy.cpp)
