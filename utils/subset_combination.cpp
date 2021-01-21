//
// Created by Fuji on 21.01.2021.
//
#include <iostream>
/*
 * We have {1,2,4,5}
 * and we want to make all possible K subsets
 */

void k_subsets(int *a, int reqLen, int s, int currLen, bool *check, int l)
//print the all possible combination of given array set
{
    if (currLen > reqLen)
        return;
    else if (currLen == reqLen) {
        for (int i = 0; i < l; i++) {
            if (check[i] == true) {
                std::cout << a[i] << " ";
            }
        }
        std::cout << "\n";
        return;
    }
    if (s == l) {
        return;
    }
    check[s] = true;
    k_subsets(a, reqLen, s + 1, currLen + 1, check, l);
    //recursively call k_subsets() with incremented value of ‘currLen’ and ‘s’.
    check[s] = false;
    k_subsets(a, reqLen, s + 1, currLen, check, l);
    //recursively call k_subsets() with only incremented value of ‘s’.
}

/*
 * We have {1,2,3,4,5}
 * and we want to make all possible subsets
 */
void all_subsets(int arr[], int n)
{
    int count = pow(2, n);
    // The outer for loop will run 2^n times to print all subset .
    // Here variable i will act as a binary counter
    for (int i = 0; i < count; i++) {
        // The inner for loop will run n times ,
        // As the maximum number of elements a set can have is n
        // This loop will generate a subset
        for (int j = 0; j < n; j++) {
            // This if condition will check if jth bit in
            // binary representation of  i  is set or not
            // if the value of (i & (1 << j)) is not 0 ,
            // include arr[j] in the current subset
            // otherwise exclude arr[j]
            if ((i & (1 << j)) != 0)
                std::cout << arr[j] << " ";
        }
        std::cout << "\n";
    }
}

//this can be done on chars too
int main() {
    int N = 5;
    int set[] = {5,2,3,4,1};
    bool *check = new bool[N];
    int k = 3;
    //set which we will choose from, k, 0, 0, check, N
    k_subsets(set, k, 0, 0, check, N);

    std::cout<< "All subsets:\n";
    all_subsets(set, N);

    return 0;
}

