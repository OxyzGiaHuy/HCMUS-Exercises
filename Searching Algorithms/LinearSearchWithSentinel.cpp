#include<iostream>
#include<vector>

using namespace std;

int linearSearchWithSentinel(vector<int> arr, int x){
    arr.push_back(x);
    for (int i = 0;; i++){
        if (arr[i] == x) return i;
    }
    return -1;
}