cmake_minimum_required(VERSION 3.1)
project(ASD)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

add_executable(Graphs  graphs.cpp graphs.h graph_builder.h graph_plotter.h topological_sorting.h dfs.h find_cycles.h path_finder.h krusak.h union_find.h prim.h dijkstra.h bellman_ford.h relax.h flow_network_generator.h)
