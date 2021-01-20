#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <set>
#include <stack>
#include <math.h>
#include <time.h>
#include <queue>


int main() {
    std::string ac_code;

    std::getline(std::cin, ac_code);

    std::cout << "Input: "<<ac_code << "\n";

    //vektor indexu a typu protected/unprotected, hrany
    std::vector<std::pair<std::pair<int, std::string>, std::vector<int>>> nodes;
    std::vector<int> roots;

    std::stack<int> parent_stck;
    int n = 0;
    int p = n;
    for (int x = 0; x < ac_code.length(); x++){
        if (ac_code[x]=='a'){
            std::vector<int> edges;
            auto node = std::make_pair(n, ac_code[x+1]);
            nodes.emplace_back(std::make_pair(node, edges));

            if(parent_stck.empty()){
                roots.emplace_back(n);
            }else{
                nodes[parent_stck.top()].second.emplace_back(n);
            }
            parent_stck.push(n);
            n++;
            x++;
        }else if (ac_code[x]=='c'){
            auto current = nodes[parent_stck.top()];
            parent_stck.pop();

            std::vector<std::string> sort_strings;
            for (int s1 : nodes[parent_stck.top()].second){
                sort_strings.emplace_back(nodes[s1].first.first);
            }

        }
    }
    return 0;
}