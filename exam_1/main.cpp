#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <set>
#include <math.h>
#include <time.h>
#include <queue>

void print_lev(std::vector<std::vector<unsigned int>> &d){
    for (auto i : d){
        for (auto j : i){
            std::cout << j << " ";
        }
        std::cout<<"\n";
    }
}

void showpq(std::priority_queue<std::string> gq)
{
    std::priority_queue<std::string> g = gq;
    std::string final;
    while (!g.empty()) {
        final = g.top();
        //std::cout << final << "\n";
        g.pop();
    }
    std::cout << final;
}

std::vector<unsigned int> lev_dist(std::string &s1, std::string &s2) {
    const std::size_t len1 = s1.size(), len2 = s2.size();
    std::vector<std::vector<unsigned int>> d(len1 + 1, std::vector<unsigned int>(len2 + 1));

    for (unsigned int i = 0; i <= len1; ++i) d[i][0] = i;
    for (unsigned int i = 1; i <= len2; ++i) d[0][i] = 0;

    for (unsigned int i = 1; i <= len1; ++i) {
        for (unsigned int j = 1; j <= len2; ++j) {
            if(i<len1) {
                d[i][j] = std::min({d[i - 1][j] + 1,
                                    d[i][j - 1] + 1,
                                    d[i - 1][j - 1] + (s1[i-1] == s2[j-1] ? 0 : 1)});
            }else{
                d[i][j] = std::min({d[i - 1][j] + 1,
                                    d[i - 1][j - 1] + (s1[i-1] == s2[j-1] ? 0 : 1)});
            }
        }
    }

    //print_lev(d);
    return d[len1];
}
/*
int main() {
    std::string alphabet;
    int D;
    std::string W1;
    std::string W2;

    std::priority_queue<std::string> W_candidates;

    //LOADING DATA
    std::getline(std::cin, alphabet);
    //std::cout << "Alphabet: "<<alphabet << "\n";

    scanf("%d", &D);
    //std::cout << "D: " << D << "\n";
    std::getline(std::cin, W1);
    std::getline(std::cin, W1);
    std::getline(std::cin, W2);
    std::cout << "W1: "<<W1 << "\n";
    std::cout << "W2: "<<W2 << "\n";

    int W_len = W1.size() - D;
    //std::cout << "W_len: " << W_len << "\n";


    //make all possible substrings of W2
    for (int i = 0; i < W2.size()-W_len+1; i++){
        std::string W2_substr = W2.substr(i, W_len);
        //std::cout << "W2 substr: " << W2_substr << "\n";

        std::vector<unsigned int> distance_W1_W2 = lev_dist(W2_substr, W1);

        //projit vsechny hodnoty a ty co jsou v thresholdu tak ulozit
        int W1_index = 0;
        for (unsigned int lev_dist_curr : distance_W1_W2){
            if (lev_dist_curr <= W_len && W1_index >= W_len){

                std::string W_candidate = W1.substr(W1_index-W_len, W_len);

                //tam kde se rovna W2_substr tak zkusim vsech
                int mist_counter = 0;
                //v poslednim loopu zmenim pismenka co se rovnaji
                for (int last_i = 0; last_i < W_len; last_i++){
                    if(W_candidate[last_i]==W2_substr[last_i] &&W_candidate[last_i] != alphabet[0]){
                        W_candidate[last_i] = alphabet[0];
                        mist_counter++;

                    }if (W_candidate[last_i]!=W2_substr[last_i] ){
                        mist_counter++;
                    }
                }
                if (mist_counter > lev_dist_curr){
                    //std::cout << "Rejected: " << W_candidate << "\n";
                    continue;
                }
                //std::cout << "Added W_candidate: " << W_candidate << " lev: " << lev_dist_curr << "\n";
                W_candidates.push(W_candidate);
            }
            W1_index++;
        }
        //std::cout<< "Lev dist W1, W2: " << lev_dist(W1, W2);
    }

    showpq(W_candidates);
    return 0;
}*/

int main(){
    std::string alphabet;
    int D;
    std::string W1;
    std::string W2;

    std::priority_queue<std::string> W_candidates;

    //LOADING DATA
    std::getline(std::cin, alphabet);
    //std::cout << "Alphabet: "<<alphabet << "\n";

    scanf("%d", &D);
    //std::cout << "D: " << D << "\n";
    std::getline(std::cin, W1);
    std::getline(std::cin, W1);
    std::getline(std::cin, W2);
    std::cout << "W1: "<<W1 << "\n";
    std::cout << "W2: "<<W2 << "\n";

    int W_len = W1.size() - D;
    //std::cout << "W_len: " << W_len << "\n";

    for (int i = 0; i < W1.size(); i++){
        for (int j = 0 ; j < alphabet.size(); j++){

        }
    }
}