// Kosaraju's algorithm to find strongly connected components in C++

#include <iostream>
#include <list>
#include <stack>
#include <vector>

class Graph {
    int V;
    std::vector<std::vector<int>> adj;
    void fillOrder(int s, bool visitedV[], std::stack<int> &Stack);
    void DFS(int s, bool visitedV[]);

public:
    Graph(int V);
    void addEdge(int s, int d);
    void printSCC();
    Graph transpose();
};

Graph::Graph(int V) {
    this->V = V;
    adj = std::vector<std::vector<int>>(V);
}

// DFS
void Graph::DFS(int s, bool visitedV[]) {
    visitedV[s] = true;
    std::cout << s << " ";

    std::vector<int>::iterator i;
    for (i = adj[s].begin(); i != adj[s].end(); ++i)
        if (!visitedV[*i])
            DFS(*i, visitedV);
}

// Transpose
Graph Graph::transpose() {
    Graph g(V);
    for (int s = 0; s < V; s++) {
        std::vector<int>::iterator i;
        for (i = adj[s].begin(); i != adj[s].end(); ++i) {
            g.adj[*i].push_back(s);
        }
    }
    return g;
}

// Add edge into the graph
void Graph::addEdge(int s, int d) {
    adj[s].push_back(d);
}

void Graph::fillOrder(int s, bool visitedV[], std::stack<int> &Stack) {
    visitedV[s] = true;

    std::vector<int>::iterator i;
    for (i = adj[s].begin(); i != adj[s].end(); ++i)
        if (!visitedV[*i])
            fillOrder(*i, visitedV, Stack);

    Stack.push(s);
}

// Print strongly connected component
void Graph::printSCC() {
    std::stack<int> Stack;

    bool *visitedV = new bool[V];
    for (int i = 0; i < V; i++)
        visitedV[i] = false;

    for (int i = 0; i < V; i++)
        if (visitedV[i] == false)
            fillOrder(i, visitedV, Stack);

    Graph gr = transpose();

    for (int i = 0; i < V; i++)
        visitedV[i] = false;

    while (Stack.empty() == false) {
        int s = Stack.top();
        Stack.pop();

        if (visitedV[s] == false) {
            gr.DFS(s, visitedV);
            std::cout << std::endl;
        }
    }
}

int main() {
    Graph g(12);
    g.addEdge(7, 4);
    g.addEdge(7, 2);
    g.addEdge(2, 7);
    g.addEdge(4, 2);
    g.addEdge(2, 10);
    g.addEdge(4, 10);
    g.addEdge(10, 8);
    g.addEdge(8, 10);
    g.addEdge(1, 10);
    g.addEdge(10, 1);
    g.addEdge(8, 9);
    g.addEdge(9, 3);
    g.addEdge(3, 9);
    g.addEdge(1, 3);
    g.addEdge(1, 5);
    g.addEdge(2, 11);
    g.addEdge(11, 5);
    g.addEdge(5, 6);
    g.addEdge(6, 11);

    std::cout << "Strongly Connected Components:\n";
    g.printSCC();
}
