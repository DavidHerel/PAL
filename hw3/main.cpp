#include <iostream>
#include <vector>
#include <string>
#include <unordered_set>
#include <stack>
#include <list>
#include <algorithm>
#include <iterator>

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

std::string find_border_network(std::string &certificate, int ending_index){
    int sum0 =0;
    int sum1 = 1;
    int i = ending_index-1;
    //std::cout << "find border network for certificate: " << certificate << "\n";
    while (true){
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

    //printf("starting index: %d endind index: %d \n", i, ending_index);
    return certificate.substr(i, ending_index-i+1);
}

void count_border_networks(int nmin, int nmax, int hmin, int hmax, std::string &certificate,
                           std::unordered_set<std::string> &border_networks){
    std::stack<int> stack;
    std::vector<std::pair<int, int>> nodesWeightsList;
    std::list<std::pair<int, int>> edgesList;
    int center;
    int node = 0;
    int sum_0 = 0;
    int sum_1 = 0;
    for (int i = 0; i < certificate.size(); i++){
        if (certificate[i] == '0'){
            nodesWeightsList.push_back(std::make_pair(node, sum_0-sum_1));
            if(stack.empty()){
                center = node;
            } else{
                edgesList.push_back(std::make_pair(stack.top(), node));
            }
            stack.push(node);
            node++;
            sum_0++;
        }else{
            int curr_node = stack.top();
            stack.pop();
            if(!stack.empty()){
                //printf("i: %d c: %c\n", i, certificate[i]);
                std::string new_bn = find_border_network(certificate, i);
                int size = new_bn.size()/2;
                int local_max = -1;
                //projdi vsechny nodes vyssi nez curr_node a najdi v nich maximalni weight
                for (int j = 0; j < nodesWeightsList.size(); j++){
                    if (nodesWeightsList[j].first >= curr_node && local_max < nodesWeightsList[j].second){
                        local_max = nodesWeightsList[j].second;
                    }
                }
                if (nmin <= size && size <= nmax && hmin <= local_max-nodesWeightsList[curr_node].second && local_max-nodesWeightsList[curr_node].second<=hmax){
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
    std::vector<std::pair<int, int>> nodesWeightsList;
    std::list<std::pair<int, int>> edgesList;
    int center;
    //std::cout << certificate << "\n";
    int node = 0;
    int sum_0 = 0;
    int sum_1 = 0;
    int counter = 0;
    for (int i = 0; i < certificate.size(); i++){
        if (certificate[i] == '0'){
            //nodesWeightsList.push_back(std::make_pair(node, sum_0-sum_1));
            if(stack.empty()){
                center = node;
            } else{
                //edgesList.push_back(std::make_pair(stack.top(), node));
            }
            stack.push(node);
            node++;
            sum_0++;
        }else{
            int curr_node = stack.top();
            stack.pop();
            if(!stack.empty()){
                //printf("i: %d c: %c\n", i, certificate[i]);
                std::string new_bn = find_border_network(certificate, i);
                std::unordered_set<std::string>::const_iterator got = border_networks.find(new_bn);

                if ( got != border_networks.end() ){
                    counter++;
                }

            }
            sum_1++;
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

    //std::cout << "Trim certificates:\n";
    //test_input_print(nmin, nmax, hmin, hmax, certificate_small_1, certificate_small_2);

    //now we have 2 or 1 certificates for small tree with 1 center
    //count borderNetworks - networks without center
    //root of BN - je ten uzel v BN ktery ma nejmensi vzdalenost do centra cele site, root R, je rootem BN, B(R)
    //size of BN - pocet uzlu v ni
    //height of BN - maximalni vzdalenost rootu od jakehokoliv NODU v BN
    //child of node x in BN - je node y, ktery je soused x, a ma o 1 vyssi vzdalenost od roota nez x
    // equivalence of two border networks B1 and B1 s rootami R1 A R2
    // je definovana rekurzivne
    //

    //std::cout << "Count border networks: \n";
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

