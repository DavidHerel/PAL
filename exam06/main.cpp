#include <iostream>
#include <list>
#include <stack>
#include <vector>
#include <algorithm>

class Node {
public:
    std::string value;
    std::vector<Node*> children;

    Node (std::string data);
};

Node::Node(std::string data) {
    value = data;
}

int hammingDist(std::string str1, std::string str2)
{
    int i = 0, count = 0;
    while(str1[i]!='\0')
    {
        if (str1[i] != str2[i]) {
            count++;
        }
        i++;
    }
    return count;
}

int main() {
    std::string certificate1;
    std::cin >> certificate1;

    //std::cout << "Certificate 1: " << certificate1 << "\n";

    std::vector<Node*> centers;
    std::stack<Node*> stack;

    for (int i = 0; i < certificate1.length(); ++i) {
        //go down
        if (certificate1[i]=='a'){
            std::string value = "";

            //invert values
            if (certificate1[i+1] == 'P'){
                value = "aUc";
            }else{
                value = "aPc";
            }
            //std:: cout << "Value " << value << "\n";
            Node *node = new Node(value);

            if(stack.empty()){
                centers.emplace_back(node);
            }else{
                stack.top()->children.push_back(node);
            }
            stack.push(node);
            i++;
        //closing
        }else{

            //std::cout << "closing\n";
            Node *temp_node = stack.top();
            stack.pop();

            std::vector<std::string> sorted_vector;
            //childrens:
            for(Node* x : temp_node->children){
                //std::cout<< "Child value: " << x->value <<"\n";
                sorted_vector.push_back(x->value);
            }
            std::sort(sorted_vector.begin(), sorted_vector.end());

            std::string new_value = "";
            for (std::string x : sorted_vector) {
                new_value += x;
            }
            if (temp_node->value[1] == 'P'){
                new_value.insert(0, "aP");
            }else{
                new_value.insert(0, "aU");
            }
            new_value.append("c");

            temp_node->value = new_value;
            //std::cout << "New value is: " << new_value << "\n";
        }

    }

    std::string certificate2;
    if (centers.size() == 2){
        std::vector<std::string> sorted_vector;
        sorted_vector.push_back(centers[0]->value);
        sorted_vector.push_back(centers[1]->value);
        std::sort(sorted_vector.begin(), sorted_vector.end());

        certificate2 = sorted_vector[0] + sorted_vector[1];
    } else{
        certificate2 = centers[0]->value;
    }

    if (certificate1.length() < 50){
        std::cout<<certificate2 <<"\n";
    }else{
        for (int i = 0; i < certificate1.length(); ++i) {
            if (certificate1[i]!=certificate2[i]){
                std::cout << certificate2.substr(i, 50) << "\n";
                break;
            }
        }
    }

    std::cout<< hammingDist(certificate1, certificate2);
    return 0;
}