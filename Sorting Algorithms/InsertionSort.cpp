#include<iostream>
#include<vector>

using namespace std;

void insertionSort(vector<int>& arr){
    for (int i = 1; i < arr.size(); i++){
        int pivot = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > pivot){
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j] = pivot;
    }
}