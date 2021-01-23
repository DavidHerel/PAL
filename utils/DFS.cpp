//
// Created by Fuji on 23.01.2021.
//
#include <iostream>
#include <vector>
#include <stack>
void dfs(std::vector<std::vector<std::pair<int, int>>> adjacency_list, int start){
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
            std::cout << start << " ";
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
}

int main(){
    std::vector<std::vector<std::pair<int,int >>> adjadjacency_list(8);
    for (int j = 0; j < adjadjacency_list.size(); ++j) {
        dfs(adjadjacency_list, j);
    }
    return 0;
}
