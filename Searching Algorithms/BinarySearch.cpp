#include<iostream>
#include<vector>

using namespace std;

// array needs to be sorted
int binarySearch(vector<int> arr, int x){
    int left = 0;
    int right = arr.size() - 1;
    while (left <= right){
        int mid = (left + right) / 2;
        if (arr[mid] < x) left = mid + 1;
        if (arr[mid] > x) right = mid - 1;
        if (arr[mid] == x) return mid;
    }
    return-1;
}