cmake_minimum_required(VERSION 3.13)
project(utils)

set(CMAKE_CXX_STANDARD 14)

add_executable(utils prim.cpp kruskal.cpp subset_combination.cpp kosaraju.cpp tarjan.cpp DFS.cpp lev_dist.cpp automata.cpp ranking.cpp sieve_erast.cpp)