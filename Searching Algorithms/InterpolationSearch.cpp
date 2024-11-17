#include<iostream>
#include<vector>

using namespace std;

int interpolationSearch(vector<int> arr, int x){
    int left = 0;
    int right = arr.size() - 1;
    while (left <= right && arr[left] <= x && x <= arr[right]){
        int pos = left + (x - arr[left]) / (arr[right] - arr[left]) * (right - left);
        if (arr[pos] == x) return pos;
        if (arr[pos] < x) left = pos + 1;
        if (arr[pos] > x) right = pos - 1;
    }
    return -1;
}