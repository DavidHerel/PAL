
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
    int MST_vertices;
    int graph_V;
    int graph_M; //to know when to stop
public:
    Graph(int V, int M);
    void add_edge(int u, int v, int w);
    int find_set(int i);
    void union_set(int u, int v);
    void kruskal();
    void print();
};
Graph::Graph(int V, int M) {
    parent = new int[V];
    rank = new int[V];
    graph_V = V;
    graph_M = M;
    MST_weight=0;
    MST_vertices = 0;
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
    if (i == parent[i]) {
        return i;
    }else {
        // Else if i is not the parent of itself
        // Then i is not the representative of his set,
        // so we recursively call Find on its parent

        return find_set(parent[i]);
    }
}

void Graph::union_set(int u, int v) {
    int xroot = find_set(u);
    int yroot = find_set(v);
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
        //already done
        if (graph_V-graph_M == MST_vertices){
            break;
        }
        std::cout<<"Found " << G[i].second.first << ":"<<G[i].second.second << " weight: "<<G[i].first << "\n";
        uRep = find_set(G[i].second.first);;
        vRep = find_set(G[i].second.second);
        std::cout << "Parents " << uRep<<":"<< vRep << "\n";

        if (uRep != vRep) {
            MST_weight+=G[i].first; //add weight to total MST
            MST_vertices++; //increase number of MST_vertices in MST
            T.push_back(G[i]);  // add to tree
            union_set(uRep, vRep);

            std::cout<<"To MST " << uRep << ":"<<vRep << " weight: "<<G[i].first << "\n";
        }
    }
}
void Graph::print() {
    /*
    std::cout << "Edge :"
              << " Weight" << "\n";
    for (int i = 0; i < T.size(); i++) {
        std::cout << T[i].second.first << " - " << T[i].second.second << " : "
                  << T[i].first << "\n";
    }
    */
    std::cout<< "MST weight: " << MST_weight << "\n";
}

/*
int main() {
    int V,M;
    scanf("%d %d", &V, &M);
    Graph g(V, M);

    int weight;
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            std::cin >> weight;
            //starting node, ending node, weight
            if (weight!=0) {
                g.add_edge(i, j, weight);
                //std::cout << "Added " << i << ":" << j << " weight: " << weight << "\n";
            }
        }
    }
    g.kruskal();
    g.print();
    return 0;
}*/