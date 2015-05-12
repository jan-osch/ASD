cmake_minimum_required(VERSION 3.1)
project(ASD)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    ASD.h
    ASD.cpp
    )


add_executable(ASD ${SOURCE_FILES} )
add_subdirectory(Sortowania)
add_subdirectory(DrzewaTest)
add_subdirectory(QuickerSort)
add_subdirectory(Drzewa)
add_subdirectory(SkipListy)
add_subdirectory(SkipListyTest)
add_subdirectory(HashTables)
add_subdirectory(RedBlackTrees)
add_subdirectory(WzbogacaneDrzewa)
add_subdirectory(Graphs)
add_subdirectory(AVLTrees)



