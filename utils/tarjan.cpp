//
// Created by Fuji on 22.01.2021.
//

#include <iostream>
#include <list>
#include <stack>
#include <vector>
/*
int min(int a, int b) {
    return (a<b)?a:b;
}

void findComponent(int u, int disc[], int low[], std::stack<int>&stk, bool stkItem[], std::vector<std::vector<int>> &adj, int &time) {
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
            findComponent(v, disc, low, stk, stkItem, adj, time);

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

        int safeCounter = 0;
        //mark safe/unsafe cities
        while (stk.top() != u)
        {
            w = (int) stk.top();
            std::cout << w << " ";
            stkItem[w] = false;
            component.push_back(w);
            stk.pop();

        }
        w = (int) stk.top();
        stkItem[w]= false;
        std::cout << w << "\n";
        component.push_back(w);
        stk.pop();
    }
}

void strongConComponent(std::vector<std::vector<int>> &adjacencyList) {
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
            findComponent(i, disc, low, stk, stkItem, adjacencyList, time);
        }
    }
}

int main(){
    int vertices = 12;
    int edges = 19;
    std::vector<std::vector<int>> adjacency_list(vertices);

    adjacency_list[7].push_back(4);
    adjacency_list[7].push_back(2);
    adjacency_list[2].push_back(7);
    adjacency_list[4].push_back(2);
    adjacency_list[2].push_back(10);
    adjacency_list[4].push_back(10);
    adjacency_list[10].push_back(8);
    adjacency_list[8].push_back(10);
    adjacency_list[10].push_back(1);
    adjacency_list[1].push_back(10);
    adjacency_list[8].push_back(9);
    adjacency_list[9].push_back(3);
    adjacency_list[3].push_back(9);
    adjacency_list[1].push_back(3);
    adjacency_list[1].push_back(5);
    adjacency_list[2].push_back(11);
    adjacency_list[11].push_back(5);
    adjacency_list[5].push_back(6);
    adjacency_list[6].push_back(11);

    strongConComponent(adjacency_list);
}
*/