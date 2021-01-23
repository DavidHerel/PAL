//
// Created by Fuji on 22.01.2021.
//

#include <iostream>
#include <list>
#include <stack>
#include <vector>
#include  <algorithm>
#include <cstring>
#include <climits>

static int *components;
static int *endedNodes;
static std::vector<std::vector<std::pair<int, int>>> DAG;

int min(int a, int b) {
    return (a<b)?a:b;
}

void findComponent(int u, int disc[], int low[], std::stack<int>&stk, bool stkItem[], std::vector<std::vector<int>> &adj, int &time, int safe_cnt, std::vector<std::pair<int, std::list<int>>> &almost_DAG) {
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
            findComponent(v, disc, low, stk, stkItem, adj, time, safe_cnt, almost_DAG);

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
        std::vector<std::pair<int, int>> edges;

        std::list<int> component;
        int score_counter = 0;
        //mark safe/unsafe cities
        while (stk.top() != u)
        {
            w = (int) stk.top();
            //std::cout << w << " ";
            stkItem[w] = false;
            component.push_back(w);
            stk.pop();
            components[w] = DAG.size();
            //calculate score of the compomnent
            if (w > 0 && w <= safe_cnt){
                score_counter++;
            }

        }
        w = (int) stk.top();
        stkItem[w]= false;
        components[w] = DAG.size();
        //calculate score of the component
        if (w > 0 && w <= safe_cnt){
            score_counter++;
        }

        //std::cout << w << "\n";
        //std::cout<< "Component score: " << score_counter << "\n";
        component.push_back(w);
        stk.pop();

        //give score to edges
        for (int comp : component){
            for (int x: adj[comp]) {
                bool found = (std::find(component.begin(), component.end(), x) != component.end());
                if (!found){
                    edges.push_back(std::make_pair(x, score_counter));
                }
            }

        }
        endedNodes[DAG.size()] = score_counter;

        almost_DAG.push_back(std::make_pair(score_counter, component));
        DAG.push_back(edges);

    }
}

void strongConComponent(std::vector<std::vector<int>> &adjacencyList, int safe_cnt,  std::vector<std::pair<int, std::list<int>>> &almost_DAG) {
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

    std::stack<int> stk;

    int time = 0;

    for(int i = 0; i<NODE; i++){    //initialize all elements
        if(disc[i] == -1){
            findComponent(i, disc, low, stk, stkItem, adjacencyList, time, safe_cnt, almost_DAG);
        }
    }
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
                dist[u] = dist[u] + endedNodes[u];

            }

        }
    }

    //delete [] visited;
    return *std::max_element(dist, dist + NODE);
}


int dfs(std::vector<std::vector<std::pair<int, int>>> adjacency_list, int start){
    int score = 0;

    // Initially mark all verices as not visited
    std::vector<bool> visited(adjacency_list.size(), false);

    // Create a stack for DFS
    std::stack<int> stack;

    // Push the current source node.
    stack.push(start);

    while (!stack.empty())
    {
        // Pop a vertex from stack and print it
        start = stack.top();
        stack.pop();

        // Stack may contain same vertex twice. So
        // we need to print the popped item only
        // if it is not visited.
        if (!visited[start])
        {
            score += endedNodes[start];
            //std::cout << start << " ";
            visited[start] = true;
        }

        // Get all adjacent vertices of the popped vertex s
        // If a adjacent has not been visited, then push it
        // to the stack.
        for (auto i : adjacency_list[start]){
            if (!visited[i.first]){
                stack.push(i.first);
            }

        }

    }
    return score;
}

//and reverse it
void create_real_DAG(){/*
    for (int i = 0; i < DAG.size(); ++i) {
        std::vector<std::pair<int, int>> edges;
        for (auto x : DAG[i]){
            edges.push_back(std::make_pair(components[x.first], x.second));
        }
        DAG[i]=edges;
    }
*/
    std::vector<std::vector<std::pair<int, int>>> reversed_DAG(DAG.size());
    for (int i = 0; i < DAG.size(); ++i) {
        std::vector<std::pair<int, int>> edges;
        for (auto x : DAG[i]){
            reversed_DAG[components[x.first]].push_back(std::make_pair(i, endedNodes[i]));
        }
    }
    int max = INT_MIN;
    //version 2 dfs from DAG
    for (int j = 0; j < reversed_DAG.size(); ++j) {
        int temp_max = dfs(reversed_DAG, j);
        if (temp_max > max){
            max = temp_max;
        }
    }
    std::cout<<max;
}

int dfs_force(std::vector<std::vector<int>> adjacency_list, int start, int safe_cnt){
    int score = 0;

    // Initially mark all verices as not visited
    std::vector<bool> visited(adjacency_list.size(), false);

    // Create a stack for DFS
    std::stack<int> stack;

    // Push the current source node.
    stack.push(start);

    while (!stack.empty())
    {
        // Pop a vertex from stack and print it
        start = stack.top();
        stack.pop();

        // Stack may contain same vertex twice. So
        // we need to print the popped item only
        // if it is not visited.
        if (!visited[start])
        {
            if (start > 0 && start <= safe_cnt ) {
                score += 1;
            }
            //std::cout << start << " ";
            visited[start] = true;
        }

        // Get all adjacent vertices of the popped vertex s
        // If a adjacent has not been visited, then push it
        // to the stack.
        for (auto i : adjacency_list[start]){
            //std::cout << "\nCO TO: ";
            if (!visited[i]){
                //std::cout << i << " \n";
                stack.push(i);
            }

        }

    }
    return score;
}

int main(){
    int vertices, edges, safe_cnt;
    scanf("%d %d %d", &vertices, &edges, &safe_cnt);
    vertices++;
    std::vector<std::vector<int>> adjacency_list(vertices);

    int start, end;
    for(int i = 0; i < edges; i++){
        scanf("%d %d", &start, &end);

        // Adding Edge
        adjacency_list[start].push_back(end);

    }

    //low_link
    endedNodes = new int[vertices];
    memset(endedNodes, -1, sizeof(int)*vertices);
    //low_link
    components = new int[vertices];
    memset(components, -1, sizeof(int)*vertices);

    std::vector<std::pair<int, std::list<int>>> almost_DAG;
    strongConComponent(adjacency_list, safe_cnt, almost_DAG);

    create_real_DAG();
    //finlani reseseni
    //najit komponenty, udelat z toho kondenzovany graf (DAG), prevratim hrany v tom DAGU a projit DFS - nejdelsi cestu beru
/*
    int ans = longestPath(DAG.size(), DAG, components, endedNodes);
    //std::cout << ans << " DAG SOZE " << DAG.size() << "\n";

    std::vector<std::vector<int>> reversed_adj(adjacency_list.size());
    for (int s = 0; s < adjacency_list.size(); s++) {
        std::vector<int>::iterator i;
        for (i = adjacency_list[s].begin(); i != adjacency_list[s].end(); ++i) {
            reversed_adj[*i].push_back(s);
        }
    }

    int max = INT_MIN;
    //version 2 dfs from DAG
    for (int j = 1; j <= safe_cnt; ++j) {
        int temp_max = dfs_force(reversed_adj, j, safe_cnt);
        if (temp_max > max){
            max = temp_max;
        }
    }
    std::cout<< max;*/

}
