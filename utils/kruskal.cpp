// Kruskal's algorithm in C++

#include <algorithm>
#include <iostream>
#include <vector>

class Graph {
private:
    std::vector<std::pair<int, std::pair<int, int>> > G;  // graph
    std::vector<std::pair<int, std::pair<int, int>> > T;  // mst
    int *parent;
    int *rank;
    int MST_weight;

public:
    Graph(int V);
    void add_edge(int u, int v, int w);
    int find_set(int i);
    void union_set(int u, int v);
    void kruskal();
    void print();
};
Graph::Graph(int V) {
    parent = new int[V];
    rank = new int[V];

    MST_weight=0;
    //i 0 1 2 3 4 5
    //parent[i] 0 1 2 3 4 5
    for (int i = 0; i < V; i++) {
        parent[i] = i;
        rank[i]=0;
    }

    G.clear();
    T.clear();
}
void Graph::add_edge(int u, int v, int w) {
    G.push_back(std::make_pair(w, std::make_pair(u, v)));
}

//same as in PAL lecture
//dont connect sets with same parent
//so we need to find set PARENT
int Graph::find_set(int i) {
    // If i is the parent of itself
    if (i == parent[i])
        return i;
    else
        // Else if i is not the parent of itself
        // Then i is not the representative of his set,
        // so we recursively call Find on its parent
        return find_set(parent[i]);
}

void Graph::union_set(int u, int v) {
    int xroot = parent[u];
    int yroot = parent[v];
    //put smaller rank tree under a high rank tree
    if (rank[xroot]<rank[yroot]){
        parent[xroot] = yroot;
    }else if (rank[xroot]>rank[yroot]){
        parent[yroot] = xroot;
    //if they are same, choose first one
    } else{
        parent[xroot] = yroot;
        rank[yroot]++;
    }

}
void Graph::kruskal() {
    int i, uRep, vRep;
    sort(G.begin(), G.end());  // increasing weight
    for (i = 0; i < G.size(); i++) {
        uRep = find_set(G[i].second.first);
        vRep = find_set(G[i].second.second);
        if (uRep != vRep) {
            MST_weight+=G[i].first;
            T.push_back(G[i]);  // add to tree
            union_set(uRep, vRep);
        }
    }
}
void Graph::print() {
    std::cout << "Edge :"
         << " Weight" << "\n";
    for (int i = 0; i < T.size(); i++) {
        std::cout << T[i].second.first << " - " << T[i].second.second << " : "
             << T[i].first << "\n";
    }
    std::cout<< "MST weight: " << MST_weight << "\n";
}/*
int main() {
    Graph g(6);
    //weight, starting V, ending V
    g.add_edge(0, 1, 4);
    g.add_edge(0, 2, 4);
    g.add_edge(1, 2, 2);
    g.add_edge(1, 0, 4);
    g.add_edge(2, 0, 4);
    g.add_edge(2, 1, 2);
    g.add_edge(2, 3, 3);
    g.add_edge(2, 5, 2);
    g.add_edge(2, 4, 4);
    g.add_edge(3, 2, 3);
    g.add_edge(3, 4, 3);
    g.add_edge(4, 2, 4);
    g.add_edge(4, 3, 3);
    g.add_edge(5, 2, 2);
    g.add_edge(5, 4, 3);

    g.kruskal();
    g.print();
    return 0;
}*/