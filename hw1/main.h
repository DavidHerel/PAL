//
// Created by Fuji on 23.09.2020.
//
#include <vector>
#include <list>
#include <iostream>
#include <queue>
#include <cstring>

#ifndef HW1_MAIN_H
#define HW1_MAIN_H

void printGraph(std::vector<std::vector <std::pair<int, int>>> &adj);
int modified_prim_algorithm(std::vector<std::vector <std::pair<int, int>>> &adj, int capital);

#endif //HW1_MAIN_H
