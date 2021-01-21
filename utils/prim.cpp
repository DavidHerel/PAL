/**
 * This file contains useful implementation of algorithms which were teached in PAL
 */
#include <iostream>
#include <cstring>
#include <vector>
#include <queue>
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
void prim_algorithm(std::vector<std::vector<std::pair<int, int>>> &adjency_list){
    //mark all vertexes as non visited
    bool *visited = new bool[adjency_list.size()];
    memset(visited, false, sizeof(bool)*adjency_list.size());

    //sort by weight
    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> priority_queue;

    //cost
    int spanning_tree_cost = 0;

    //push the starting one with weight 0
    int starting_vertex = 1;
    int weight = 0;
    priority_queue.push(std::make_pair(weight, starting_vertex));

    //check all vertices added
    while(!priority_queue.empty()){
        //take first one (lowest) from the set
        std::pair<int, int> vertex_pair = priority_queue.top();
        priority_queue.pop();

        int vertex = vertex_pair.second;
        int weight = vertex_pair.first;
        if (!visited[vertex]){
            std::cout<< "Vertex " << vertex << " added" << " to MST with cost: " << weight<<"\n";
            //mark it as visited
            visited[vertex]=true;
            spanning_tree_cost+= weight;

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
    std::cout << "MST: " << spanning_tree_cost << "\n";
}

//MINIMUM SPANNING TREE
void minimum_spanning_tree_test(){
    //adjency_list
    std::vector<std::vector<std::pair<int, int>>> adjency_list(9);
    //starting, weight, ending
    adjency_list[1].push_back(std::make_pair(5,3));
    adjency_list[1].push_back(std::make_pair(3,2));
    adjency_list[2].push_back(std::make_pair(4,4));
    adjency_list[2].push_back(std::make_pair(3,1));
    adjency_list[3].push_back(std::make_pair(12,4));
    adjency_list[3].push_back(std::make_pair(5,1));
    adjency_list[4].push_back(std::make_pair(9,5));
    adjency_list[4].push_back(std::make_pair(8,8));
    adjency_list[4].push_back(std::make_pair(4,2));
    adjency_list[4].push_back(std::make_pair(12,3));
    adjency_list[5].push_back(std::make_pair(4,6));
    adjency_list[5].push_back(std::make_pair(9,4));
    adjency_list[5].push_back(std::make_pair(5,7));
    adjency_list[5].push_back(std::make_pair(1,8));
    adjency_list[6].push_back(std::make_pair(4,5));
    adjency_list[6].push_back(std::make_pair(6,7));
    adjency_list[7].push_back(std::make_pair(6,6));
    adjency_list[7].push_back(std::make_pair(5,5));
    adjency_list[7].push_back(std::make_pair(20,8));
    adjency_list[8].push_back(std::make_pair(20,7));
    adjency_list[8].push_back(std::make_pair(1,5));


    //prim - slowest
    // O(V+E)
    prim_algorithm(adjency_list);

}

/*
int main() {
    std::cout << "Hello, World!" << std::endl;
    minimum_spanning_tree_test();

    return 0;
}*/