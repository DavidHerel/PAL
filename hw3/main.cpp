#include <iostream>
#include <vector>
#include <string>
#include <unordered_set>
#include <stack>
#include <list>
#include <algorithm>
#include <iterator>
#include <climits>
#include <cstring>
#include <iostream>
#include <unordered_set>
#include <algorithm>
#include <iterator>

void print(std::unordered_set<std::string> const &s)
{
    std::copy(s.begin(),
              s.end(),
              std::ostream_iterator<std::string>(std::cout, " "));
}

std::string find_border_network(std::string &certificate, int ending_index, int nmin, int nmax, int hmin,int hmax){
    int sum0 =0;
    int sum1 = 1;
    int i = ending_index-1;
    //std::cout << "find border network for certificate: " << certificate << "\n";
    while (true){
        if (sum1+sum0>nmax*2){
            return "ERROR";
        }
        //printf("i: %d c: %c\n", i, certificate[i]);
        if (certificate[i] == '1'){
            sum1++;
        }else{
            sum0++;
        }
        if (sum0 == sum1){
            break;
        }
        i--;
    }
    if (nmin >sum0){
        return "ERROR";
    }

    //printf("starting index: %d endind index: %d \n", i, ending_index);
    std::string tree_certif_cut= certificate.substr(i, ending_index-i+1);

    //lets build a FUCKING TREE
    std::stack<int> stack;
    int node = 0;
    int sum_0 = 0;
    int NODE = tree_certif_cut.size()/2;
    int *dist = new int[NODE];
    memset(dist, INT_MIN, sizeof(int)*NODE);
    int sum_1 = 0;
    for (int i = 0; i < tree_certif_cut.size(); i++){
        if (tree_certif_cut[i] == '0'){
            stack.push(node);
            dist[node] = sum_0-sum_1;
            node++;
            sum_0++;
        }else{
            stack.pop();
            sum_1++;
        }
    }
    int max_el = *std::max_element(dist, dist+NODE);
    //std::cout << "Max el: " << max_el << "\n";
    if (hmin <= max_el && max_el <= hmax){
        return tree_certif_cut;
    }else{
        return "ERROR";
    }
}

void count_border_networks(int nmin, int nmax, int hmin, int hmax, std::string &certificate,
                           std::unordered_set<std::string> &border_networks){
    std::stack<int> stack;
    int node = 0;
    int sum_0 = 0;
    int sum_1 = 0;
    for (int i = 0; i < certificate.size(); i++){
        if (certificate[i] == '0'){
            stack.push(node);
            node++;
            sum_0++;
        }else{
            int curr_node = stack.top();
            stack.pop();
            if(!stack.empty()){
                //printf("i: %d c: %c\n", i, certificate[i]);
                std::string new_bn = find_border_network(certificate, i, nmin, nmax, hmin, hmax);
                if (new_bn.compare("ERROR") == 0){
                    continue;
                }
                int size = new_bn.size()/2;
                int local_max = -1;

                if (nmin <= size && size <= nmax){
                    //std::cout << "Size: " << size << " Weight: " << local_max -nodesWeightsList[curr_node].second << "\n";
                    //std::cout <<  "Inserted: "<<new_bn << "\n";
                    border_networks.insert(new_bn);
                }
            }
            sum_1++;
        }
    }

}

int find_border_networks(int nmin, int nmax, int hmin, int hmax, std::string &certificate,
                           std::unordered_set<std::string> &border_networks){
    std::stack<int> stack;
    int node = 0;
    int counter = 0;
    for (int i = 0; i < certificate.size(); i++){
        if (certificate[i] == '0'){
            //nodesWeightsList.push_back(std::make_pair(node, sum_0-sum_1));
            stack.push(node);
            node++;
        }else{
            stack.pop();
            if(!stack.empty()){
                //printf("i: %d c: %c\n", i, certificate[i]);
                std::string new_bn = find_border_network(certificate, i, nmin, nmax, hmin, hmax);
                if (new_bn.compare("ERROR") == 0){
                    continue;
                }
                std::unordered_set<std::string>::const_iterator got = border_networks.find(new_bn);

                if ( got != border_networks.end() ){
                    counter++;
                }

            }
        }
    }
    return counter;
}


void test_input_print(int nmin, int nmax, int hmin, int hmax, std::string &certificate_small, std::string &certificate_big){
    std::cout << nmin << " " << nmax << " " << hmin << " " << hmax << "\n";
    std::cout << certificate_small << "\n";
    std::cout << certificate_big << "\n";
}

int main() {
    int nmin, nmax, hmin, hmax;
    //scan useless data
    scanf("%d %d %d %d", &nmin, &nmax, &hmin, &hmax);
    std::string certificate_small;
    std::string certificate_big;
    std::string line;

    //empty line for no reason wtf
    std::getline(std::cin, line);

    //rest of certificates
    std::getline(std::cin, certificate_small);
    std::getline(std::cin, certificate_big);

    //test_input_print(nmin, nmax, hmin, hmax, certificate_small, certificate_big);

    //trim certificates into 2
    std::string certificate_small_1;
    std::string certificate_small_2;

    //TRIM
    int sum_0 = 0;
    int sum_1 = 0;
    int i = 0;
    while (true){
        if (certificate_small[i] == '0'){
            sum_0++;
        }else{
            sum_1++;
        }
        if (sum_0 == sum_1){
            certificate_small_1 = certificate_small.substr(0, i+1);
            //there is another
            if (i+1 != certificate_small.size()){
                certificate_small_2 = certificate_small.substr(i+1, certificate_small.size()-1);
            }
            break;
        }
        i++;
    }

    std::unordered_set<std::string> border_networks;
    count_border_networks(nmin, nmax, hmin, hmax, certificate_small_1, border_networks);

    if (certificate_small_2.size() > 0) {
        count_border_networks(nmin, nmax, hmin, hmax, certificate_small_2, border_networks);
    }
    //print(border_networks);

    //lets trim big
    //trim certificates into 2
    std::string certificate_big_1;
    std::string certificate_big_2;

    sum_0 = 0;
    sum_1 = 0;
    i = 0;
    while (true){
        if (certificate_big[i] == '0'){
            sum_0++;
        }else{
            sum_1++;
        }
        if (sum_0 == sum_1){
            certificate_big_1 = certificate_big.substr(0, i+1);
            //there is another
            if (i+1 != certificate_big.size()){
                certificate_big_2 = certificate_big.substr(i+1, certificate_big.size()-1);
            }
            break;
        }
        i++;
    }

    //std::cout << "Trim certificates BIG:\n";
    //test_input_print(nmin, nmax, hmin, hmax, certificate_big_1, certificate_big_2);
    //lets do the same algorithm with as small but check if it is in unordered set - if yes raise ++
    //std::cout << "FIND border networks in BIG NETWORKS: \n";
    int counter = find_border_networks(nmin, nmax, hmin, hmax, certificate_big_1, border_networks);

    if (certificate_big_2.size() > 0) {
        counter += find_border_networks(nmin, nmax, hmin, hmax, certificate_big_2, border_networks);
    }
    printf("%d", counter);
    return 0;
}

