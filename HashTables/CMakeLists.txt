cmake_minimum_required(VERSION 3.1)
project(ASD)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/Graph_Printer")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

add_executable(HashTables tablice_haszujace.cpp tablice_haszujace.h)
