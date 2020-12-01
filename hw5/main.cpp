#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <set>
#include <time.h>
/*
void print(std::set<int> const &s)
{
    std::copy(s.begin(),
              s.end(),
              std::ostream_iterator<int>(std::cout, " "));
}*/
int find_hamming_distance(std::string &s1, std::string &s2) {
    int count = 0;
    for (int i = 0; s1[i] != 0; i++){
        if (s1[i] != s2[i]) {
            count++;
        }
    }
    return count;
}

void check_k_reduced_pair(std::string &s1, std::string &s2, int K, std::vector<std::pair<std::pair<int, int>, std::pair<int,int>>> &matching_k_reduced_pair,  int start_s1, int end_s1, int start_t1, int end_t1){
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
        int diff = find_hamming_distance(s1, sub_str);
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

void find_s2_substr(int start_s1, int end_s1, int L, int K, std::string &S, std::string &s1, std::set<std::set<int>> &matching_k_pair, std::vector<std::pair<std::pair<int, int>, std::pair<int,int>>> &matching_k_reduced_pair){
    int l_k=L-K;
    for (int i = 0; i < S.length()-l_k+1; i++) {
        if (i + L <= S.length()){
            find_matching_s2_kpair(i, start_s1, end_s1, L, K, S, s1, matching_k_pair);
        }
        if (i+l_k <= S.length() && K !=0){
            //TODO
            //Hledani k reduced je extremně pomale
            find_matching_s2_kreduced(i, start_s1, end_s1, l_k, K, S, s1, matching_k_reduced_pair);
        }
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


    std::set<std::set<int>> matching_k_pair;
    std::vector<std::pair<std::pair<int, int>, std::pair<int,int>>> matching_k_reduced_pair;
    std::string *beg = new std::string();
    std::string *fin = new std::string();
    //loading done
    //finding all S1 subs_strings
    for(int i = 0; i < S.length()-L+1; i++){
        std::string sub_str;
        sub_str = S.substr(i, L);
        //std::cout<<"S1: " << sub_str<<"\n";

        find_s2_substr(i, i+L-1, L, K, S, sub_str, matching_k_pair, matching_k_reduced_pair);

    }

    std::cout << matching_k_pair.size() + matching_k_reduced_pair.size();
    //printf("Time taken: %.2fs\n", (double)(clock() - tStart)/CLOCKS_PER_SEC);
    return 0;
}