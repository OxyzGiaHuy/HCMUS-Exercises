#include<iostream>
#include<vector>

using namespace std;

int partition(vector<int>& arr, int low, int high){
    int pivot = arr[high];
    int i = low - 1;
    for (int j = low; j < high - 1; j++){
        if (arr[j] < pivot){
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return i + 1;
}

void quickSort(vector<int>& arr, int low, int high){
    if (low < high){
        int par = partition(arr, low, high);
        quickSort(arr, low, par - 1);
        quickSort(arr, par + 1, high);
    }
}