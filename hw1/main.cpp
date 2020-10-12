#include "main.h"

int main() {
    //handle input
    int cities, highways, capital;
    scanf("%d %d %d", &cities, &highways, &capital);

    //adjency list - vector of vectors which has pairs <weight, b>
    std::vector<std::vector<std::pair<int, int>>> adjacencyList(cities);

    int a, b, weight;
    for(int i = 0; i < highways; i++){
        scanf("%d %d %d", &a, &b, &weight);

        // Adding Edge
        adjacencyList[a].push_back(std::make_pair(weight, b));
        //adding second edge
        adjacencyList[b].push_back(std::make_pair(weight, a));
    }

    //now everything is in adjacency list
    //printGraph(adjacencyList);
    //now lets make modified prims algorithm
    int value = modified_prim_algorithm(adjacencyList, capital);
    printf("%d", value);
    return value;

}

int modified_prim_algorithm(std::vector<std::vector <std::pair<int, int>>> &adj, int capital){
    //set cityindexes of all to -1
    int *cityIndexes = new int[adj.size()];
    memset(cityIndexes, -1, sizeof(int)*adj.size());
    cityIndexes[capital] = 0;

    // Mark all the vertices as not visited
    bool *spanning_tree = new bool[adj.size()];
    memset(spanning_tree, false, sizeof(bool)*adj.size());
    int spanning_tree_cost = 0;

    std::priority_queue<std::pair<int, std::pair<int, int>>, std::vector<std::pair<int, std::pair<int, int>>>, std::greater<std::pair<int, std::pair<int, int>>>> priority_queue;

    //push there cityIndex, weight, capital -> in this sorting ORDER!!!!
    priority_queue.push(std::make_pair(0, std::make_pair(0, capital)));

    while (!priority_queue.empty()){
        std::pair<int, std::pair<int, int>> vertexPair = priority_queue.top();
        priority_queue.pop();
        int vertex = vertexPair.second.second;
        int weight = vertexPair.second.first;

        //if it is not in spanning tree
        if (!spanning_tree[vertex]){
            //push it there
            spanning_tree[vertex] = true;
            spanning_tree_cost += weight;
            //printf("Added vertex %d with value %d\n", vertex, weight);

            //now look at all weights coming out from our spanning tree
            for (std::pair<int, int> &x : adj[vertex]) {
                int vertex2 = x.second;
                //set its cityIndex
                if (cityIndexes[vertex2] == -1) {
                    cityIndexes[vertex2] = cityIndexes[vertex] + 1;
                }

                //if it is not in spanning tree and city index of this is higher or same than vertex1
                if(!spanning_tree[vertex2] && cityIndexes[vertex2] >= cityIndexes[vertex]){
                    //printf("Vertex %d added to prior queue\n", vertex2);
                    //push it
                    priority_queue.push(std::make_pair(cityIndexes[vertex2], std::make_pair(x.first, vertex2)));
                }

            }
        }
    }

    return spanning_tree_cost;
}
/**
// Print the graph
void printGraph(std::vector<std::vector <std::pair<int, int>>> &adj) {
    for (int d = 0; d < adj.size(); ++d) {
        std::cout << "From vertex: " << d << "\n";
        for (auto x : adj[d])
            std::cout << "To: "<<x.second << " with prize " << x.first << "\n";
        printf("\n");
    }
}
*/

