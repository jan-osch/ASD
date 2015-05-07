cmake_minimum_required(VERSION 3.1)
project(ASD)

enable_testing()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

enable_testing()

add_executable(SkipListyTest  skip_listy_test.cpp)
#target_link_libraries(SkipListyTesty gtest gtest_main)
add_test( SkipListyTest runUnitTests )