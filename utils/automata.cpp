//
// Created by Fuji on 24.01.2021.
//
#include <iostream>
#include <unordered_set>
#include <vector>
#include <string>

int main(){
    //nfa

    //vezememe prefix
    std::string line;
    std::getline(std::cin, line);
    std::string prefix = line;

    //automat prezentujeme jako adjacency list, kde cena je prechod
    std::vector<std::vector<std::pair<int, int>>> adjacency_list_states;

    //std::cout<< prefix << "\n";
    //std::cout << "Let's count prefix nodes\n";
    //INPUT DONE - FINALLY
    //now process prefix and find prefix states

    std::vector<int> set_of_states;
    std::unordered_set<int> prefix_states;
    //vlozime pocatecni uzel (v nasem pripade 0)
    set_of_states.push_back(0);
    int i = 0;
    while ((i < prefix.length()) && (!set_of_states.empty())){
        std::vector<int> set_of_states_tmp;

        // pro vsechny stavy v kterych jsme
        for (int state : set_of_states){

            //se koukneme kam vedou
            for (std::pair<char, int> pair : adjacency_list_states[state]){

                //jestli matchujeme s prefixem
                if (pair.first == prefix[i]){
                    //std::cout << "Pushed node: " << pair.second << "\n";
                    //vlozime ho tam
                    set_of_states_tmp.push_back(pair.second);
                    //jestli je zaroven dlouhy jako prefix tak je to prefix state
                    if(i + 1 == prefix.length()){
                        prefix_states.insert(pair.second);
                    }
                }
            }
        }
        set_of_states = set_of_states_tmp;
        i++;
    }


    //if set_of_states.contains final state

    //TODO verze 2

    //pro text search full slova to je:
    set_of_states.push_back(0);
     i = 0;
    while ((i < prefix.length()) && (!set_of_states.empty())){
        for (int state : set_of_states){

            //pokud je state final
            if (state == "FINAL"){
                std::cout << "We are in final state\n";
            }
        }

        std::vector<int> set_of_states_tmp;

        // pro vsechny stavy v kterych jsme
        for (int state : set_of_states){

            //se koukneme kam vedou
            for (std::pair<char, int> pair : adjacency_list_states[state]){

                //jestli matchujeme s prefixem
                if (pair.first == prefix[i]){
                    //std::cout << "Pushed node: " << pair.second << "\n";
                    //vlozime ho tam
                    set_of_states_tmp.push_back(pair.second);
                }
            }
        }
        set_of_states = set_of_states_tmp;
        i++;
    }
}