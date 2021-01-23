#include <iostream>
#include <vector>
#include <algorithm>

static bool first = false;

void print_lev(std::vector<std::vector<unsigned int>> &d){
    for (auto i : d){
        for (auto j : i){
            std::cout << j << " ";
        }
        std::cout<<"\n";
    }
}
/*
unsigned int edit_distance(const std::string& s1, const std::string& s2)
{
    const std::size_t len1 = s1.size(), len2 = s2.size();
    std::vector<std::vector<unsigned int>> d(len1 + 1, std::vector<unsigned int>(len2 + 1));

    d[0][0] = 0;
    for(unsigned int i = 1; i <= len1; ++i) d[i][0] = i;
    for(unsigned int i = 1; i <= len2; ++i) d[0][i] = i;

    for(unsigned int i = 1; i <= len1; ++i)
        for(unsigned int j = 1; j <= len2; ++j)
            d[i][j] = std::min({ d[i - 1][j] + 1, d[i][j - 1] + 1, d[i - 1][j - 1] + (s1[i - 1] == s2[j - 1] ? 0 : 1) });
    return d[len1][len2];
}*/

int lev_dist(std::string &s1, std::string &s2) {
    const std::size_t len1 = s1.size(), len2 = s2.size();
    std::vector<std::vector<unsigned int>> d(len1 + 1, std::vector<unsigned int>(len2 + 1));

    d[0][0] = 0;
    for (unsigned int i = 1; i <= len1; ++i) d[i][0] = i;
    for (unsigned int i = 1; i <= len2; ++i) d[0][i] = i;

    for (unsigned int i = 1; i <= len1; ++i) {
        for (unsigned int j = 1; j <= len2; ++j) {
                d[i][j] = std::min({d[i - 1][j] + 1,
                                    d[i][j - 1] + 1,
                                    d[i - 1][j - 1] + (s1[i-1] == s2[j-1] ? 0 : 1)});
        }
    }

    //print_lev(d);
    return d[len1][len2];
}
/*
int levenshtein(std::string &s1, std::string &s2) {
    int n = s2.length();

    int *costs = new int[n + 1];

    for( int k=0; k<=n; k++ ) costs[k] = k;

    int i = 0;
    for (auto const &c1 : s1) {
        costs[0] = i+1;
        int corner = i, j = 0;
        for (auto const &c2 : s2) {
            int upper = costs[j+1];
            if(c1 ==c2) {
                costs[j+1] = corner;
            }
            else {
                int t = std::min(upper, corner);
                costs[j+1] = std::min(costs[j], t) + 1;
            }
            corner = upper;
            j++;
        }
        i++;
    }

    return costs[n];
}*/

//Postupne se rozvetvuju - to same jde udelat i s cislama, akorat by tam byly vector napriklad misto stringu
void repeating_subsets(std::string alphabet, int k, int curr_len, std::string subset, std::string W1, std::string W2, int max_lev_dist){
    if (first){
        return;
    }
    int W1_lev_dist = lev_dist(subset, W1);
    int W2_lev_dist = lev_dist(subset, W2);

    //cut
    if (W1_lev_dist + subset.length() - k - max_lev_dist > 0 ) {
        //std::cout << "cut\n";
        return;
    }
    if (k == curr_len) {

        /*std::cout<< subset<<"\n";
        std::cout << "Dist W1 "<<W1_lev_dist << "\n";
        std::cout << "Dist W2 "<<W2_lev_dist << "\n";*/
        if ( W1_lev_dist<= max_lev_dist &&  W2_lev_dist<= max_lev_dist){
            std::cout<< subset;
            first = true;
            return;
        }

    } else if(k < curr_len){
        return;
    }else {
        for (char i : alphabet) {
            std::string temp_subset = subset + i;
            //std::cout << temp_subset << "\n";
            repeating_subsets(alphabet, k, curr_len+1, temp_subset, W1, W2, max_lev_dist);

        }
    }
}

int main() {
    int max_lev_dist;
    std::string alphabet;
    std::string W1,W2;

    std::cin >> alphabet;
    std::cin >> max_lev_dist;
    std::cin >> W1;
    std::cin >> W2;
/*
    std::cout << "Alphabet: " << alphabet << std::endl;
    std::cout << "Max_lev_dist: " << max_lev_dist << std::endl;
    std::cout << "W1: " << W1 << std::endl;
    std::cout << "W2: " << W2 << std::endl;
*/
    if (W1.length() > W2.length()){
        repeating_subsets(alphabet, W1.length()-max_lev_dist, 0, "", W1, W2, max_lev_dist);
    }else{
        repeating_subsets(alphabet, W2.length()-max_lev_dist, 0, "", W2, W1, max_lev_dist);
    }
    return 0;
}