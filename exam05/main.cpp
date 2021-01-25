#include <iostream>
#include <set>
#include <vector>
#include <algorithm>
#include <queue>
/*
#include <istream>
#include <iostream>
#include <bits/stdc++.h>
#include <vector>


int N, M, P, C;
bool **adj_matrix;
//zde budou vsechnu mozne packy
std::vector<std::vector<int>> all_packs;
std::vector<std::vector<int>> solutions;

bool testCombination(std::vector<int> comb) {


    int c = 0;

    for (int i = 0; i < P; ++i) {
        int from = comb[i];
        for (int j = i + 1; j < P; ++j) {
            int to = comb[j];
            if (adj_matrix[from][to]) {
//                std::cout << "from to: " << from << " " << to << "\n";
                ++c;
            }
        }
//        if (c > C) return false;
    }
    if (c != C) return false;

    // is reachable?
    std::queue<int> queue;
    queue.push(comb[0]);
    bool visited[N];
    for (int i = 0; i < N; ++i) {
        visited[i] = false;
    }
    int visitCount = 0;
    while (!queue.empty()) {
        int next = queue.front();
//        std::cout << "next: " << next << " \n";
        queue.pop();
        if (!visited[next]) {
            visited[next] = true;
            ++visitCount;
            for (int i = 0; i < P; ++i) {
                int possChild = comb[i];
//                std::cout << "possChild: " << possChild << " \n";
                if (adj_matrix[next][possChild]) {
                    queue.push(possChild);
                }
            }
        }
    }
    return visitCount == P;
}

void k_subsets(int *a, int reqLen, int s, int currLen, bool *check, int l)
//print the all possible combination of given array set
{
    if (currLen > reqLen)
        return;
    else if (currLen == reqLen) {
        int prev_node;
        std::vector<int> possible_pack;
        for (int i = 0; i < l; i++) {
            if (check[i]) {
//                std::cout << a[i] << " ";
                possible_pack.push_back(a[i]);
                //check if there is connection between 2
                if (possible_pack.size() > 1) {
                    //there is not connection
                    /*
                    if (!adj_matrix[a[i]][prev_node]) {
                        std::cout<< "Not a pack\n";
                        //this is not pack
                        return;
                    }*/
/*
                }
                prev_node = a[i];
            }
        }
        if (testCombination(possible_pack)) {
            std::sort(possible_pack.begin(), possible_pack.end());
            all_packs.push_back(possible_pack);
        }
        return;
    }
    if (s == l) {
        return;
    }
    check[s] = true;
    k_subsets(a, reqLen, s + 1, currLen + 1, check, l);
    //recursively call k_subsets() with incremented value of ‘currLen’ and ‘s’.
    check[s] = false;
    k_subsets(a, reqLen, s + 1, currLen, check, l);
    //recursively call k_subsets() with only incremented value of ‘s’.
}

int degree(int from, std::vector<int> &pack) {
    int c = 0;
    for (int i = 0; i < P; ++i) {
        int to = pack[i];
        if (adj_matrix[from][to]) ++c;
    }
    return c;
}

bool test2Packs(std::vector<int> &pack1, std::vector<int> &pack2) {
    for (const auto &v: pack1) {
        for (const auto &w: pack2) {
            if (v == w) return false;
        }
    }

    std::vector<int> degreesPack1(P);
    std::vector<int> degreesPack2(P);
    for (int i = 0; i < P; ++i) {
        degreesPack1[i] = degree(pack1[i], pack1);
        degreesPack2[i] = degree(pack2[i], pack2);
    }
    std::sort(degreesPack1.begin(), degreesPack1.end());
    std::sort(degreesPack2.begin(), degreesPack2.end());
    for (int i = 0; i < P; ++i) {
        if (degreesPack1[i] != degreesPack2[i]) return false;
    }

    return true;
}

void testPacks() {
    int SIZE = all_packs.size();
    for (int i = 0; i < SIZE; ++i) {
        for (int j = i; j < SIZE; ++j) {
            if (test2Packs(all_packs[i], all_packs[j])) {
                std::vector<int> solution;
                for (const auto &v: all_packs[i]) {
                    solution.push_back(v);
                }
                for (const auto &v: all_packs[j]) {
                    solution.push_back(v);
                }
                solutions.push_back(solution);
            }
        }
    }
}

int main(int argc, char ** argv) {
    //LOADING INPUT
    scanf("%d %d %d %d", &N, &M, &P, &C);

    int *set = new int[N];
    //init matrix
    adj_matrix = new bool *[N];
    for (int i = 0; i < N; ++i) {
        set[i] = i;
        adj_matrix[i] = new bool[N];
        for (int j = 0; j < N; ++j) {
            adj_matrix[i][j] = false;
        }
    }

    int a, b;
    //fill the matrix
    for (int k = 0; k < M; ++k) {
        scanf("%d %d", &a, &b);
        adj_matrix[a][b] = true;
        adj_matrix[b][a] = true;
    }

    //ACTUAL CODE
    //Chci vyextrahovat všechny packy z grafu
    //a porovnavat kazdy s kazdyms


    //udelat vsechny P kombinace z N, ktere splnuji ze je tam C hran a kazde dva jsou mezi sebou propojeni
    bool *check = new bool[N];
    k_subsets(set, P, 0, 0, check, N);

    testPacks();

    for (const auto &sol: solutions) {
        std::cout << sol[0];
        for (int i = 1; i < sol.size(); ++i) {
            std::cout << " " << sol[i];
        }
        std::cout << "\n";
    }
    return 0;
}
*/

bool test_edges(bool **adj_matrix, std::vector<int> &possible_pack, int C, int P){
    int c = 0;

    for (int i = 0; i < P; ++i) {
        int from = possible_pack[i];
        for (int j = i + 1; j < P; ++j) {
            int to = possible_pack[j];
            if (adj_matrix[from][to]) {
//                std::cout << "from to: " << from << " " << to << "\n";
                ++c;
            }
        }
//        if (c > C) return false;
    }
    if (c != C){
        return false;
    } else{
        return true;
    };
}

bool bfs(int start, int n, bool **adj_matrix, std::vector<int> &possible_pack, int actual_nodes){
    bool* visited = new bool[n];
    for (int i = 0; i < n; ++i) {
        visited[i]=false;
    }
    std::vector<int> queue;

    //std::cout << "Entering BFS\n";

    visited[start] = true;
    queue.push_back(start);

    int vis;
    int nodes_cnt = 0;
    while(!queue.empty()){
        vis = queue[0];

        //print current node
        //std::cout<< vis << " ";

        nodes_cnt++;
        queue.erase(queue.begin());

        //for every edge
        for (int i = 0; i < n; ++i) {

            //i has to be in vector
            if(adj_matrix[vis][i] && (!visited[i]) && std::find(possible_pack.begin(), possible_pack.end(), i) != possible_pack.end() ){
                queue.push_back(i);

                visited[i] = true;
            }
        }
    }

    //std::cout<<"\n";
    if(nodes_cnt == actual_nodes){
        return true;
    }

    return false;
}

void k_subsets(int *a, int reqLen, int s, int currLen, bool *check, int l, bool **adj_matrix, std::vector<std::vector<int>> &all_packs, int C)
//print the all possible combination of given array set
{
    if (currLen > reqLen)
        return;
    else if (currLen == reqLen) {
        //std::cout<<"Comb:\n";
        std::vector<int> possible_pack;
        for (int i = 0; i < l; i++) {
            if (check[i] == true) {
                //std::cout << a[i] << " ";

                //add to possible pack
                possible_pack.push_back(a[i]);
            }
        }
        //testuju spojitost
        if(bfs(possible_pack[0], l, adj_matrix, possible_pack, currLen)){
            //testuju pocet hran
            if (test_edges(adj_matrix, possible_pack, C ,currLen)){
                all_packs.push_back(possible_pack);
            }else{
                //std::cout << " Pack rejected\n";
            }

            //std::cout << "\n";
        }else{
            //std::cout << " Pack rejected\n";
        }

        return;
    }
    if (s == l) {
        return;
    }
    check[s] = true;
    k_subsets(a, reqLen, s + 1, currLen + 1, check, l, adj_matrix, all_packs, C);
    //recursively call k_subsets() with incremented value of ‘currLen’ and ‘s’.
    check[s] = false;
    k_subsets(a, reqLen, s + 1, currLen, check, l, adj_matrix, all_packs, C);
    //recursively call k_subsets() with only incremented value of ‘s’.
}

int find_degree(bool **adj_matrix, int ver,int N){
    int degree = 0;
    for (int i = 0; i < N; ++i) {
        if(adj_matrix[ver][i]){
            degree++;
        }
    }
    if(adj_matrix[ver][ver]){
        degree++;
    }
    return degree;
}

int degree(int from, std::vector<int> &pack, bool **adj_matrix, int P) {
    int c = 0;
    for (int i = 0; i < P; ++i) {
        int to = pack[i];
        if (adj_matrix[from][to]) ++c;
    }
    return c;
}

bool test2Packs(std::vector<int> &pack1, std::vector<int> &pack2, bool **adj_matrix, int P) {
    for (const auto &v: pack1) {
        for (const auto &w: pack2) {
            if (v == w) return false;
        }
    }

    std::vector<int> degreesPack1(P);
    std::vector<int> degreesPack2(P);
    for (int i = 0; i < P; ++i) {
        degreesPack1[i] = degree(pack1[i], pack1, adj_matrix, P);
        degreesPack2[i] = degree(pack2[i], pack2, adj_matrix, P);
    }
    std::sort(degreesPack1.begin(), degreesPack1.end());
    std::sort(degreesPack2.begin(), degreesPack2.end());
    for (int i = 0; i < P; ++i) {
        if (degreesPack1[i] != degreesPack2[i]) return false;
    }

    return true;
}

bool isBipartite(bool **adj_matrix, int src, int N, std::vector<int> &possible_pack)
{
    // Create a color array to store colors
    // assigned to all veritces. Vertex
    // number is used as index in this array.
    // The value '-1' of colorArr[i]
    // is used to indicate that no color
    // is assigned to vertex 'i'. The value 1
    // is used to indicate first color
    // is assigned and value 0 indicates
    // second color is assigned.
    int *colorArr = new int[N];
    for (int i = 0; i < N; ++i)
        colorArr[i] = -1;

    // Assign first color to source
    colorArr[src] = 1;

    // Create a queue (FIFO) of vertex
    // numbers and enqueue source vertex
    // for BFS traversal
    std::queue <int> q;
    q.push(src);

    // Run while there are vertices
    // in queue (Similar to BFS)
    while (!q.empty())
    {
        // Dequeue a vertex from queue ( Refer http://goo.gl/35oz8 )
        int u = q.front();
        q.pop();

        // Return false if there is a self-loop
        if (adj_matrix[u][u])
            return false;

        // Find all non-colored adjacent vertices
        for (int v = 0; v < N; ++v)
        {
            // An edge from u to v exists and
            // destination v is not colored
            if (adj_matrix[u][v] && colorArr[v] == -1 && std::find(possible_pack.begin(), possible_pack.end(), v) != possible_pack.end())
            {
                // Assign alternate color to this adjacent v of u
                colorArr[v] = 1 - colorArr[u];
                q.push(v);
            }

                // An edge from u to v exists and destination
                // v is colored with same color as u
            else if (adj_matrix[u][v] && colorArr[v] == colorArr[u] && std::find(possible_pack.begin(), possible_pack.end(), v) != possible_pack.end())
                return false;
        }
    }

    // If we reach here, then all adjacent
    // vertices can be colored with alternate color
    return true;
}


int main() {
    //DATA STRUCTURES
    int N, M, P, C;

    //LOADING INPUT
    scanf("%d %d %d %d", &N, &M, &P, &C);

    //test innput
    //std::cout << N << M << P << C << "\n";

    int *set = new int[N];
    //init matrix
    bool **adj_matrix;
    adj_matrix= new bool*[N];
    for (int i = 0; i < N; ++i) {
        set[i]=i;
        adj_matrix[i] = new bool[N];
        for (int j = 0; j < N; ++j) {
            adj_matrix[i][j] = false;
        }
    }

    int a,b;
    //fill the matrix
    for (int k = 0; k < M; ++k) {
        scanf("%d %d", &a, &b);
        adj_matrix[a][b]=true;
        adj_matrix[b][a]=true;
    }

    //check the matrix
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            if(adj_matrix[i][j]){
                //std::cout<< "1 ";
            }else{
                //std::cout<< "0 ";
            }
        }
       // std::cout << "\n";
    }

    //ACTUAL CODE
    //Chci vyextrahovat všechny packy z grafu
    //a porovnavat kazdy s kazdym

    //zde budou vsechnu mozne packy
    std::vector<std::vector<int>> all_packs;

    //udelat vsechny P kombinace z N, ktere splnuji ze je tam C hran a kazde dva jsou mezi sebou propojeni
    bool *check = new bool[N];
    k_subsets(set, P, 0, 0, check, N, adj_matrix, all_packs, C);

    //std::cout<<"All packs\n";
    //now we have all packs in set
    for (std::vector<int> x : all_packs){
        for (int i : x){
            //std::cout << i <<" ";
        }
        //std::cout<<"\n";
    }
    //std::cout << all_packs.size() << "\n";

    std::vector<std::pair<std::vector<int>, std::vector<int>>> pairs;
    //find packs
    for (std::vector<int> curr_pack : all_packs){
        for(std::vector<int> trying_pack : all_packs){
            bool add = true;
            for (int curr_pack_i : trying_pack){
                //std::cout << curr_pack_i <<" ";
                //if it is there - break
                if (std::find(curr_pack.begin(), curr_pack.end(), curr_pack_i) != curr_pack.end()){
                    add = false;
                    break;
                }
            }
            if (add){
                std::pair<std::vector<int>, std::vector<int>> new_pair = std::make_pair(curr_pack, trying_pack);
                std::pair<std::vector<int>, std::vector<int>> sec_pair = std::make_pair(trying_pack, curr_pack);
                if (std::find(pairs.begin(), pairs.end(), sec_pair) != pairs.end()){

                }else{
                    pairs.push_back(new_pair);
                }

            }
        }
        //std::cout<<"\n";
    }

/*
    std::vector<std::pair<std::vector<int>, std::vector<int>>> pairs2;
    //ted vyfiltrovat podle stupne
    for (std::pair<std::vector<int>, std::vector<int>> curr_pack : pairs) {
        std::vector<int> p1_vertices;
        for (int p_1 : curr_pack.first) {
            p1_vertices.push_back(find_degree(adj_matrix, p_1, N));
        }
        std::vector<int> p2_vertices;
        for (int p_2 : curr_pack.second) {
            p2_vertices.push_back(find_degree(adj_matrix, p_2, N));
        }

        std::sort(p1_vertices.begin(), p1_vertices.end());
        std::sort(p2_vertices.begin(), p2_vertices.end());

        bool add = true;
        //if they are not same - not isomorphic
        for (int i = 0; i < p1_vertices.size(); i++){
            if (p1_vertices[i]!=p2_vertices[i]){
                add = false;
            }
        }
        if (add){
            pairs2.push_back(std::make_pair(curr_pack.first, curr_pack.second));
        }
    }
    */
    std::vector<std::pair<std::vector<int>, std::vector<int>>> pairs2;
    //ted vyfiltrovat podle stupne
    for (std::pair<std::vector<int>, std::vector<int>> curr_pack : pairs) {
        if (test2Packs(curr_pack.first, curr_pack.second, adj_matrix, P)){
            pairs2.push_back(std::make_pair(curr_pack.first, curr_pack.second));
        }
    }

    //treti filtr vyfiltrovat podle vzdalenosti
    //bfs s kazdeho uzlu toho podgrafu a

    //ctvry filtr - pocet trojuhelniku

/*
    //paty filtr oba musi byt biparitni
    std::vector<std::pair<std::vector<int>, std::vector<int>>> pairs5;
    for (std::pair<std::vector<int>, std::vector<int>> curr_pack : pairs) {
        if (isBipartite(adj_matrix, curr_pack.first[0], N, curr_pack.first) && isBipartite(adj_matrix, curr_pack.second[0], N, curr_pack.second)){
            pairs5.push_back(std::make_pair(curr_pack.first, curr_pack.second));
        }
    }
    */

    for (std::pair<std::vector<int>, std::vector<int>> curr_pack : pairs2) {
        for (int p_1 : curr_pack.first) {
            std::cout<< p_1 << " ";
        }
        for (int p_2 : curr_pack.second) {
            std::cout<< p_2 << " ";
        }
        std::cout<< "\n";
    }


    return 0;
}
