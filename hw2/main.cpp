#include <iostream>
#include <vector>
#include <stack>
#include <stdio.h>
#include <list>
#include <time.h>
#include <cstring>
#include <climits>
#include <algorithm>

void printGraphDAG(std::vector<std::vector <std::pair<int, int>>> &adj) {
    for (int d = 0; d < adj.size(); ++d) {
        std::cout << "From vertex: " << d;
        for (auto x : adj[d])
            std::cout << " to: "<<x.first << " weight: " << x.second << "\n";
        printf("\n");
    }
}

void printGraph(std::vector<std::vector <int>> &adj) {
    for (int d = 0; d < adj.size(); ++d) {
        std::cout << "From vertex: " << d << "\n";
        for (auto x : adj[d])
            std::cout << "To: "<<x << "\n";
        printf("\n");
    }
}

bool contains(const std::list<int> &list, int x){
    return std::find(list.begin(), list.end(), x) != list.end();
}

void topologicalSort(int v, bool visited[],
         std::stack<int>& Stack, std::vector<std::vector<std::pair<int, int>>> &DAG)
{
    // Mark the current node as visited
    visited[v] = true;

    // Recur for all the vertices adjacent to this vertex
    for (std::pair<int, int> x : DAG[v]) {
        if (!visited[x.first])
            topologicalSort(x.first, visited, Stack, DAG);
    }
    // sort
    Stack.push(v);
}


int longestPath(int NODE, std::vector<std::vector<std::pair<int, int>>> &DAG, int components[], int endedNodes[])
{
    // if it is in stack
    bool *visited = new bool[NODE];
    memset(visited, false, sizeof(bool)*NODE);

    std::stack<int> Stack;
    int *dist = new int[NODE];
    memset(dist, INT_MIN, sizeof(int)*NODE);

    // Sort starting from all vertices one by one
    for (int i = 0; i < NODE; i++)
        if (visited[i] == false)
            topologicalSort(i, visited, Stack, DAG);

    int u = Stack.top();
    dist[u] = 0;

    // Process vertices in topological order
    while (Stack.empty() == false) {
        // Get the next vertex from topological order
        int u = Stack.top();
        Stack.pop();
        //std::cout << "Top order: " << u << "\n";

        if (dist[u] != INT_MIN) {
            for (std::pair<int, int> x : DAG[u]) {
                if (dist[x.first] < dist[u] + x.second) {
                    dist[x.first] = dist[u] + x.second;
                }
            }
            if (DAG[u].empty()) {
                if (endedNodes[u] > 0){
                    dist[u] = dist[u] + endedNodes[u];

                }
            }

        }
    }

    //delete [] visited;
    return *std::max_element(dist, dist + NODE);
}


void check_safe_status(std::vector<std::pair<int, int>> &edges, int &safeCounter,int &w, std::vector<std::vector<int>> &adj, std::vector<std::vector<int>> &undirected, bool safeCities[], bool componentArray[]){
    //CUT PHASE
    bool safeStatus = true;
    //for node in strong component
    for (int neighbor : undirected[w]){
        //printf("cp size %d \n", component.size());
        //if in stkItem is neghbour which is not in component -> say it is unsafe
        if (!componentArray[neighbor]){
            //printf("%d has neigh with %d", w, neighbor);
            safeStatus = false;
        }
    }
    //if it is not safe
    if(!safeStatus) {
        for (int x : adj[w]) {
            if (!componentArray[x]){
                edges.push_back(std::make_pair(x, 0));
            }
        }
    }else{
        //printf("TU");
        safeCounter++;
        safeCities[w] = safeStatus;
    }
}

void createDAG(std::vector<std::vector<std::pair<int, int>>> &DAG, int components[]){
    for (int i = 0; i < DAG.size(); i++) {
        std::vector<std::pair<int, int>> edges;
        for (auto x : DAG[i]){
            edges.push_back(std::make_pair(components[x.first], x.second));
        }
        DAG[i]=edges;

    }
}

int min(int a, int b) {
    return (a<b)?a:b;
}
void findComponent(int u, int disc[], int low[], std::stack<int>&stk, bool stkItem[], std::vector<std::vector<int>> &adj, std::vector<std::vector<int>> &undirected, bool safeCities[], int &time, std::vector<std::vector<std::pair<int, int>>> &DAG, int components[], bool componentArray[], int endedNodes[]) {
    disc[u] = low[u] = time++;
    //std::cout << "vertex: " << u << " discovery time: " << disc[u] << " low link: " << low[u] << "\n";
    stk.push(u);
    stkItem[u] = true;

    // Go through all vertices adjacent to this
    std::vector<int>::iterator i;
    for (i = adj[u].begin(); i != adj[u].end(); ++i)
    {
        int v = *i;  // v is current adjacent of 'u'

        // If v is not visited yet, then recur for it
        if (disc[v] == -1)
        {
            findComponent(v, disc, low, stk, stkItem, adj, undirected, safeCities, time, DAG, components, componentArray, endedNodes);

            low[u]  = min(low[u], low[v]);
            //std::cout << "Changing first visit vertex: " << u << " discovery time: " << disc[u] << " low link: " << low[u] << "\n";
        }
        else if (stkItem[v] == true)
            low[u]  = min(low[u], low[v]);
        //std::cout << "Changing vertex: " << u << " discovery time: " << disc[u] << " low link: " << low[u] << "\n";
    }

    int w = 0;  // To store stack extracted vertices
    if (low[u] == disc[u])
    {
        // if it is in stack
        memset(componentArray, false, sizeof(bool)*adj.size());

        std::vector<std::pair<int, int>> edges;

        std::list<int> component;

        int safeCounter = 0;
        //mark safe/unsafe cities
        while (stk.top() != u)
        {
            w = (int) stk.top();
            components[w] = DAG.size();
            //std::cout << w << " ";
            stkItem[w] = false;
            component.push_back(w);
            componentArray[w] = true;
            stk.pop();

        }
        w = (int) stk.top();
        components[w] = DAG.size();
        stkItem[w]= false;
        componentArray[w] = true;
        //std::cout << w << "\n";
        component.push_back(w);
        stk.pop();
        for (int x : component) {
            //std::cout << "component: " << x << "\n";
            check_safe_status(edges, safeCounter, x, adj, undirected, safeCities, componentArray);
        }
        //std::cout << "safeCounter: " << safeCounter << "\n";
        //change weight of edges
        for (int x = 0; x < edges.size(); x++){
            edges[x].second = safeCounter;
        }
        endedNodes[DAG.size()] = safeCounter;

        //push edges
        DAG.push_back(edges);
    }
}
void strongConComponent(std::vector<std::vector<int>> &adjacencyList, std::vector<std::vector<int>> &undirected, bool safeCities[], std::vector<std::vector<std::pair<int, int>>> &DAG, int components[], int endedNodes[]) {
    int NODE = adjacencyList.size();

    //discovery time
    int *disc = new int[NODE];
    memset(disc, -1, sizeof(int)*NODE);

    //low_link
    int *low = new int[NODE];
    memset(low, -1, sizeof(int)*NODE);

    // if it is in stack
    bool *stkItem = new bool[NODE];
    memset(stkItem, false, sizeof(bool)*NODE);

    bool *componentArray = new bool[NODE];
    memset(componentArray, false, sizeof(bool)*NODE);

    std::stack<int> stk;

    int time = 0;

    for(int i = 0; i<NODE; i++){    //initialize all elements
        if(disc[i] == -1){
            findComponent(i, disc, low, stk, stkItem, adjacencyList, undirected, safeCities, time, DAG, components, componentArray, endedNodes);
        }
    }
}

int main() {
    clock_t tStart = clock();
    //handle input
    int vertices, edges;
    scanf("%d %d", &vertices, &edges);

    //adjency list - vector of vectors which has destination
    std::vector<std::vector<int>> adjacencyList(vertices);

    std::vector<std::vector<int>> adjacencyListUndirected(vertices);

    int start, end;
    for(int i = 0; i < edges; i++){
        scanf("%d %d", &start, &end);

        // Adding Edge
        adjacencyList[start].push_back(end);

        //vector for checking safe/unsafe cities
        adjacencyListUndirected[start].push_back(end);
        adjacencyListUndirected[end].push_back(start);
    }
    int NODE = adjacencyList.size();
    // if it is in stack
    bool *safeCities = new bool[NODE];
    memset(safeCities, false, sizeof(bool)*NODE);

    //DAG - b, weight
    std::vector<std::vector<std::pair<int, int>>> DAG;

    //low_link
    int *endedNodes = new int[NODE];
    memset(endedNodes, -1, sizeof(int)*NODE);
    //low_link
    int *components = new int[NODE];
    memset(components, -1, sizeof(int)*NODE);


    //now everything is in adjacency list
    //printGraph(adjacencyListUndirected);
    strongConComponent(adjacencyList, adjacencyListUndirected, safeCities, DAG, components, endedNodes);

    /*printf("----\n");
    for (int i = 0; i < NODE; i++){
        if (safeCities[i])
            printf("%d\n", i);
    }*/
    createDAG(DAG, components);
    //printf("----\n");
    //std::cout<< "SIZE DAG:" << DAG.size() << "\n";
    //printGraphDAG(DAG);
    int ans = longestPath(DAG.size(), DAG, components, endedNodes);
    std::cout << ans;
    //printf("Time taken: %.2fs\n", (double)(clock() - tStart)/CLOCKS_PER_SEC);
    return 0;

}