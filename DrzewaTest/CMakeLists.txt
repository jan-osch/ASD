cmake_minimum_required(VERSION 3.1)
project(ASD)

ADD_SUBDIRECTORY (gtest-1.7.0)
enable_testing()
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

enable_testing()

set(SOURCE_FILES
    TreeTest.cpp
    ../Drzewa/Drzewa.h
    )

add_executable(DrzewaTest ${SOURCE_FILES} )
target_link_libraries(DrzewaTest gtest gtest_main)
add_test( DrzewaTest runUnitTests )