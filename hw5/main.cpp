#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <set>
#include <math.h>
#include <time.h>
#define MIN(x,y) ((x) < (y) ? (x) : (y)) //calculate minimum between two values
/*
void print(std::set<int> const &s)
{
    std::copy(s.begin(),
              s.end(),
              std::ostream_iterator<int>(std::cout, " "));
}*/

void print_lev(std::vector<std::vector<unsigned int>> &d){
    for (auto i : d){
        for (auto j : i){
            std::cout << j << " ";
        }
        std::cout<<"\n";
    }
}

std::vector<unsigned int> lev_dist(std::string &s1, std::string &s2) {
    const std::size_t len1 = s1.size(), len2 = s2.size();
    std::vector<std::vector<unsigned int>> d(len1 + 1, std::vector<unsigned int>(len2 + 1));

    for (unsigned int i = 0; i <= len1; ++i) d[i][0] = i;
    for (unsigned int i = 1; i <= len2; ++i) d[0][i] = 0;

    for (unsigned int i = 1; i <= len1; ++i) {
        for (unsigned int j = 1; j <= len2; ++j) {
            // note that std::min({arg1, arg2, arg3}) works only in C++11,
            // for C++98 use std::min(std::min(arg1, arg2), arg3)
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

int find_hamming_distance(std::string &s1, std::string &s2, int K) {
    int count = 0;
    for (int i = 0; s1[i] != 0; i++){
        if (s1[i] != s2[i]) {
            count++;
            if (count > K){
                return count;
            }
        }
    }
    return count;
}

void check_k_reduced_pair(std::string &s1, std::string &s2, int K, std::vector<std::pair<std::pair<int, int>, std::pair<int,int>>> &matching_k_reduced_pair,  int start_s1, int end_s1, int start_t1, int end_t1){
    /*std::vector<unsigned int> lev_d = lev_dist(s1, s2);
    for (unsigned int i = 0; i<lev_d.size(); i++){
        if(lev_d[i] <= K && i >= s2.size()){
            //std::cout<<"Matching\n";
            //std::cout << s1 << " s2 full: "<<s2 << "\n";
            std::string temp_str;
            temp_str = s1.substr(i+1-s2.size(), s2.size());
            //std::cout << temp_str << " s2 full: "<<s2 << "\n";
            if(temp_str==s2){
               // std::cout << "Pridam\n";
                bool add = true;
                for (std::pair<std::pair<int, int>, std::pair<int,int>> vect_pair :matching_k_reduced_pair){
                    if(vect_pair.first.first == start_s1 && vect_pair.first.second==end_s1 && vect_pair.second.first == start_t1 && vect_pair.second.second == end_t1){
                        add = false;
                        break;
                    }
                }
                if (add){
                    matching_k_reduced_pair.push_back(std::make_pair(std::make_pair(start_s1, end_s1), std::make_pair(start_t1, end_t1)));
                }
                break;
            }

        }
    }*/
    for (int i = 0; i < s1.length()-K+1; i++) {
        std::string temp_s1 = s1;
        temp_s1.erase(i, K);
        int diff = s2.compare(temp_s1);

        //std::cout << "diff: "<<diff<<"\n";
        //std::cout << "temp_s1: " << temp_s1 << " s2: "<<s2 << "\n";

        if (diff == 0){
            //std::cout<<"K-reduced pair found\n";
            //std::cout<< "s1: " << s1 << " s2: "<<s2<<"\n";

            bool add = true;
            for (std::pair<std::pair<int, int>, std::pair<int,int>> vect_pair :matching_k_reduced_pair){
                if(vect_pair.first.first == start_s1 && vect_pair.first.second==end_s1 && vect_pair.second.first == start_t1 && vect_pair.second.second == end_t1){
                    add = false;
                    break;
                }
            }
            if (add){
                matching_k_reduced_pair.push_back(std::make_pair(std::make_pair(start_s1, end_s1), std::make_pair(start_t1, end_t1)));
                break;
            }

            //std::cout << matching_k_reduced1.size() << "\n";
            //std::cout << matching_k_reduced2.size() << "\n";
        }
    }

}

void find_matching_s2_kpair(int i, int start_s1, int end_s1, int L, int K, std::string &S, std::string &s1, std::set<std::set<int>> &matching_k_pair){
    if ((i < start_s1 && i+L <= start_s1) || (i>end_s1 && i+L>end_s1)){
        std::string sub_str;
        sub_str = S.substr(i, L);
        //std::cout<<"S2: " << sub_str<< " i: "<< i <<"\n";

        //find k-pair
        //prepsat na hamminga
        int diff = find_hamming_distance(s1, sub_str, K);
        //std::cout<< "diff: " << diff << "\n";
        if (diff == K){
            //std::cout<<"K-pair found\n";
            //std::cout<< "s1: " << s1 << " s2: "<<sub_str<<"\n";
            //check if it differs from rest of pairs (make it as function)
            //musi byt aspon jedna jina pozice mezi (s1,s2) a (t1,t2)
            //if yes - pridame do matchin_pair_k-pair
            std::set<int> new_set;
            new_set.insert(start_s1);
            new_set.insert(end_s1);
            new_set.insert(i);
            new_set.insert(i+L-1);
            matching_k_pair.insert(new_set);
            //std::cout<< matching_k_pair.size() << "\n";
        }
    }
}
void find_matching_s2_kreduced(int i, int start_s1, int end_s1, int L, int K, std::string &S, std::string &s1, std::vector<std::pair<std::pair<int, int>, std::pair<int,int>>> &matching_k_reduced_pair){
    if ((i < start_s1 && i+L <= start_s1) || (i>end_s1 && i+L>end_s1)){
        std::string sub_str;
        sub_str = S.substr(i, L);

        //std::cout<<"K-reduced pair STARTS\n";
        //std::cout<< "s1: " << s1 << " s2: "<<sub_str<<"\n";
        //find k-reduced pair
        check_k_reduced_pair(s1, sub_str, K, matching_k_reduced_pair, start_s1, end_s1, i, i+L-1);
    }
}

void find_s2_substr(int start_s1, int end_s1, int L, int K, std::string &S, std::string &s1, std::set<std::set<int>> &matching_k_pair){
    for (int i = 0; i < S.length()-L+1; i++) {
        find_matching_s2_kpair(i, start_s1, end_s1, L, K, S, s1, matching_k_pair);
    }
}

int main() {
    clock_t tStart = clock();
    int A, L, K;
    //load the shit
    scanf("%d %d %d", &A, &L, &K);
    //printf("%d %d %d\n", A, L, K);
    //load text
    std::string S;
    std::getline(std::cin, S);
    std::getline(std::cin, S);
    //std::cout<<S <<"\n";
    int count_red = 0;
    int l_k = L-K;
    //IMPLEMENTATION OF CHANGED PORADI - posledni sance..
    //combinations of s2:
    //strogin only unique values man
    //take s2
    //TOO SLOW FOR CASE 10
    for (int i = 0; i < S.size() - (l_k)+1; i++){
        //shit case for pub02
        if (K==0){
            break;
        }
        std::string s2_substr = S.substr(i, l_k);
        std::set<unsigned int> temp_j;
        for (int p_s2 = 0; p_s2 < l_k+1; p_s2++){

            std::string ending = s2_substr.substr(l_k-p_s2, p_s2);
            std::string start = s2_substr.substr(0, l_k-p_s2);

            //ted hledam s1 odpovidajici
            for (int j = 0; j < S.size() - L +1; j++){
                //check if it is in range - and compare
                //SUBSTRING TAKES SO LONG!!
                    if(j > i +l_k -1|| j+L-1 < i){
                        bool add = true;
                        for (int jk = 0; jk < start.size(); jk++){
                            if (S[j+jk]!=start[jk]){
                                add = false;
                                break;
                            }
                        }
                        if (add){
                            for (int jk = 0; jk < ending.size(); jk++){
                                if (S[j+L-ending.size()+jk]!=ending[jk]){
                                    add = false;
                                    break;
                                }
                            }
                            if(add){
                                temp_j.insert(j);
                            }
                        }

                    }
            }
        }
        count_red+=temp_j.size();
    }



    std::set<std::set<int>> matching_k_pair;
    //loading done
    //finding all S1 subs_strings
    for(int i = 0; i < S.length()-L+1; i++){
        std::string sub_str;
        sub_str = S.substr(i, L);
        //std::cout<<"S1: " << sub_str<<"\n";

        find_s2_substr(i, i+L-1, L, K, S, sub_str, matching_k_pair);

    }

    std::cout << matching_k_pair.size() + count_red;
    //printf("\nTime taken: %.2fs\n", (double)(clock() - tStart)/CLOCKS_PER_SEC);
    //std::vector<unsigned int> lev_d = lev_dist(s11,s22);

    return 0;
}