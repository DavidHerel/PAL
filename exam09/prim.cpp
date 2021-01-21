/**
 * This file contains useful implementation of algorithms which were teached in PAL
 */
#include <iostream>
#include <cstring>
#include <vector>
#include <queue>
#include <climits>
//does prim algorithm on adjency list
/*
 * How does it work?
 * Take random node - add vertex to subset which has edge with lowest value
 * Take lowest edge from that subset
 * CZ
 * Udelame si nenavstivene pole uzlu
 * pak si udelame nove adjency list kde bude nase vysledna kostra
 * udelame priority queue do ktere budeme pridavat hrany ale nahore bude ta s nejmensi cenou
 * koukneme se zda-li uzel na druhe strane hrany neni v nasi mnozine
 * a kd
 */
int prim_algorithm(std::vector<std::vector<std::pair<int, int>>> &adjency_list, int starting_vertex, int ending_cond){
    //mark all vertexes as non visited
    bool *visited = new bool[adjency_list.size()];
    memset(visited, false, sizeof(bool)*adjency_list.size());

    //sort by weight
    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> priority_queue;

    //cost
    int spanning_tree_cost = 0;

    //push the starting one with weight 0
    int weight = 0;
    priority_queue.push(std::make_pair(weight, starting_vertex));

    //num of vertices
    int vertices = 0;

    //check all vertices added
    while(!priority_queue.empty()){
        if(vertices >= ending_cond){
            //std::cout << "MST: " << spanning_tree_cost << "\n";
            return spanning_tree_cost;
        }
        //take first one (lowest) from the set
        std::pair<int, int> vertex_pair = priority_queue.top();
        priority_queue.pop();

        int vertex = vertex_pair.second;
        int weight = vertex_pair.first;
        if (!visited[vertex]){
            //std::cout<< "Vertex " << vertex << " added" << " to MST with cost: " << weight<<"\n";
            //mark it as visited
            visited[vertex]=true;
            spanning_tree_cost+= weight;
            vertices++;

            //look at all edges coming out from that vertex
            for (std::pair<int, int> &neighbor : adjency_list[vertex]){
                int neighbor_vertex = neighbor.second;
                int neighbor_weight = neighbor.first;
                //if it is not in set
                if (!visited[neighbor_vertex]){
                    //push
                    priority_queue.push(std::make_pair(neighbor_weight, neighbor_vertex));
                }
            }
        }


    }
    //std::cout << "MST: " << spanning_tree_cost << "\n";
}


int main() {
    int V,M;
    scanf("%d %d", &V, &M);
    std::vector<std::vector<std::pair<int, int>>> adjency_list(V);
    int weight;
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            std::cin >> weight;
            //starting node, ending node, weight
            if (weight!=0) {
                adjency_list[i].push_back(std::make_pair(weight, j));
                //std::cout << "Added " << i << ":" << j << " weight: " << weight << "\n";
            }
        }
    }
    int min = INT_MAX;
    for (int k = 0; k < V; ++k) {
        int temp_min = prim_algorithm(adjency_list, k, V-M);
        if(temp_min<min){
            min = temp_min;
        }
    }
    std::cout<<min;
    return 0;
}