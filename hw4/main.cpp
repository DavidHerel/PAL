#include <iostream>
#include <vector>
#include <stack>
#include <string>
#include <stdio.h>
#include <list>
#include <time.h>
#include <cstring>
#include <climits>
#include <algorithm>
#include <ctype.h>
#include <unordered_set>
#include <set>
/*
void print(std::unordered_set<int> const &s)
{
    std::copy(s.begin(),
              s.end(),
              std::ostream_iterator<int>(std::cout, " "));
}*/

void find_longest_and_shortest(int &global_min, int &global_max, int local_minmax, std::vector<std::set<int>> &adjacency_list_states_backwards,
        int starting_node, std::unordered_set<int> &prefix_states, int score_min[], int score_max[]){
    //jsem v prefix nodu a mrknu se jestli muzu jit jeste do dalsiho prefix uzlu
    if(prefix_states.find(starting_node) != prefix_states.end()) {
        for (auto i : adjacency_list_states_backwards[starting_node]) {
            //pokud ano, tak jdu
            if (prefix_states.find(i) != prefix_states.end()){
                /*std::cout << "jsem v PREFIX NODU" << "\n";
                std::cout << "From " << starting_node << " to " << i<< " with len " << local_minmax + 1 << "\n";*/
                bool go= false;
                if(score_min[i]>local_minmax){
                    score_min[i] = local_minmax;
                    go = true;
                }
                if(score_max[i]<local_minmax){
                    score_max[i] = local_minmax;
                    go = true;
                }
                if(go) {
                    find_longest_and_shortest(global_min, global_max, local_minmax + 1, adjacency_list_states_backwards,
                                              i, prefix_states, score_min, score_max);
                }
            }else{
                //std::cout << "FINAL CHAPTER" << "\n";
                //std::cout << "From " << starting_node << " to " << i << " with len " << local_minmax << "\n";
                //pokud ne - pocitam
                if (local_minmax > global_max){
                    global_max = local_minmax;
                }
                if (local_minmax < global_min){
                    global_min = local_minmax;
                }
            }

        }
    //nejsem v prefix nodu
    }else{
        for (auto i : adjacency_list_states_backwards[starting_node]) {
            bool go= false;
            //std::cout << score_min[i] << " " << local_minmax << "\n";
            if(score_min[i]>local_minmax){
                score_min[i] = local_minmax;
                go = true;
            }
            //std::cout << score_max[i] << " " << local_minmax << "\n";
            if(score_max[i]<local_minmax){
                score_max[i] = local_minmax;
                go = true;
            }
            if(go) {
                /*std::cout << "From " << starting_node << " to " << i<< " with len " << local_minmax + 1
                          << "\n";*/
                find_longest_and_shortest(global_min, global_max, local_minmax + 1, adjacency_list_states_backwards,
                                          i, prefix_states, score_min, score_max);
            }
        }
    }
}

void find_longest_and_shortest_iterative(int &global_min, int &global_max, int local_minmax, std::vector<std::set<int>> &adjacency_list_states_backwards,
                               int starting_node, std::unordered_set<int> &finite_states, int score_min[], int score_max[]){
    //jsem v finite nodu a mrknu se jestli muzu jit jeste dal
    //printf("Nova iterace ");
    //std::cout << local_minmax << "\n";
    if(finite_states.find(starting_node) != finite_states.end()) {
        if (local_minmax > global_max){
            global_max = local_minmax;
        }
        if (local_minmax < global_min){
            global_min = local_minmax;
        }
        for (auto i : adjacency_list_states_backwards[starting_node]) {

            bool go = false;
            //std::cout << score_min[i] << " " << local_minmax << "\n";
            if (score_min[i] > local_minmax) {
                score_min[i] = local_minmax;
                go = true;
            }
            //std::cout << score_max[i] << " " << local_minmax << "\n";
            if (score_max[i] < local_minmax) {
                score_max[i] = local_minmax;
                go = true;
            }
            if (go) {
                /*std::cout << "From " << starting_node << " to " << i<< " with len " << local_minmax + 1
                          << "\n";*/
                find_longest_and_shortest_iterative(global_min, global_max, local_minmax + 1, adjacency_list_states_backwards,
                                          i, finite_states, score_min, score_max);
            }

        }

    }else {
        for (auto i : adjacency_list_states_backwards[starting_node]) {
            bool go = false;
            //std::cout << score_min[i] << " " << local_minmax << "\n";
            if (score_min[i] > local_minmax) {
                score_min[i] = local_minmax;
                go = true;
            }
            //std::cout << score_max[i] << " " << local_minmax << "\n";
            if (score_max[i] < local_minmax) {
                score_max[i] = local_minmax;
                go = true;
            }
            if (go) {
                /*std::cout << "NFrom " << starting_node << " to " << i<< " with len " << local_minmax + 1
                          << "\n";*/
                find_longest_and_shortest_iterative(global_min, global_max, local_minmax + 1, adjacency_list_states_backwards,
                                          i, finite_states, score_min, score_max);
            }
        }
    }

}

int main() {
    clock_t tStart = clock();
    //handle input
    int num_states, size_alphabet;
    scanf("%d %d", &num_states, &size_alphabet);

    //adjency list - vector of vectors which has destination
    std::vector<std::vector<std::pair<char, int>>> adjacency_list_states(num_states);

    std::vector<std::set<int>> adjacency_list_states_backwards(num_states);
    std::vector<std::set<int>> adjacency_list_states_iterative(num_states);
    std::unordered_set<int> finite_states;

    std::string line;
    std::getline(std::cin, line);
    for(int i = 0; i < num_states; i++) {
        std::string line;
        std::getline(std::cin, line);
        //std::cout << line << "\n";

        int j_temp;
        //find finite state
        for (unsigned int j = 0; j < line.length(); j++){
            j_temp = j;
            if (line[j] == 'F'){
                finite_states.insert(i);
                break;
            }else if (line[j] == '-'){
                break;
            }
        }

        std::string number;
        char value = 'a';
        //parse line from 5th index
        for (unsigned int j = j_temp+1; j < line.length(); j++ ){
            //std::cout << "Tady to spadne 1, char: "<< line[j]  << "\n";
            if(isalpha(line[j]) != 0){
                value = line[j];
                //std::cout << "Value: " <<value << "\n";
            }

            //std::cout << "Tady to spadne 2" << "\n";
            //if it is number and not space nor letter
            if(isdigit(line[j]) != 0){
                //std::cout << "Number: " << line[j] << " \n";
                number += line[j];
            }

            //std::cout << "Tady to spadne 3" << "\n";
            if((j+1==line.length() ||line[j] == ' ') && !number.empty()){
                int int_number = std::stoi(number);
                //std::cout << "Z " << i << " do " << int_number << " prechodem: " <<value << "\n";
                adjacency_list_states[i].push_back(std::make_pair(value, int_number));
                adjacency_list_states_backwards[int_number].insert(i);
                adjacency_list_states_iterative[i].insert(int_number);
                number = "";
            }

        }

    }
    std::getline(std::cin, line);
    std::string prefix = line;

    //std::cout<< prefix << "\n";
    //std::cout << "Let's count prefix nodes\n";
    //INPUT DONE - FINALLY
    //now process prefix and find prefix states

    std::vector<int> set_of_states;
    std::unordered_set<int> prefix_states;
    set_of_states.push_back(0);
    int i = 0;
    while ((i < prefix.length()) && (!set_of_states.empty())){
        std::vector<int> set_of_states_tmp;
        for (int state : set_of_states){
            for (std::pair<char, int> pair : adjacency_list_states[state]){
                if (pair.first == prefix[i]){
                    //std::cout << "Pushed node: " << pair.second << "\n";
                    set_of_states_tmp.push_back(pair.second);
                    if(i + 1 == prefix.length()){
                        prefix_states.insert(pair.second);
                    }
                }
            }
        }
        set_of_states = set_of_states_tmp;
        i++;
    }
    //printf("Prefix states:\n");
    //print(prefix_states);

    //NOW I HAVE ALL PREFIX STATES
    //iterate backwards from finite states till you find prefix states
    int global_max = INT_MIN;
    int global_min = INT_MAX;

    //printf("PHASE 3: go backwards \n");
    std::list<int> nodes;
    //discovery time
    int *score_min = new int[num_states];
    int *score_max = new int[num_states];
    for (i = 0; i < num_states; i++){
        score_min[i] = INT_MAX;
        score_max[i] = INT_MIN;
    }

    /*for (int i : finite_states){
        //std::cout << finite_states.size() << " :size\n";
        find_longest_and_shortest(global_min, global_max, 0, adjacency_list_states_backwards, i, prefix_states, score_min, score_max);

    }*/

    for (int i : prefix_states){
        //std::cout << i << " :i\n";
        find_longest_and_shortest_iterative(global_min, global_max, 0, adjacency_list_states_iterative, i, finite_states, score_min, score_max);

    }

    std::cout<< global_min + prefix.length() << " "<<global_max+prefix.length();
    //printf("Time taken: %.2fs\n", (double)(clock() - tStart)/CLOCKS_PER_SEC);
    return 0;
}