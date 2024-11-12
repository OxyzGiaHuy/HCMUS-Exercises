#include<iostream>
#include<vector>

using namespace std;

void merge(vector<int>& arr, int left, int mid, int right){
    int len1 = mid - left + 1;
    int len2 = right - mid;

    vector<int> arr_l(len1), arr_r(len2);
    for (int i = 0; i < len1; i++){
        arr_l[i] = arr[left + i];
    }
    for (int i = 0; i < len2; i++){
        arr_r[i] = arr[mid + 1 + i];
    }

    int i = 0, j = 0, k = left;
    while (i < len1 && j < len2){
        if (arr_l[i] < arr_r[j]) arr[k] = arr_l[i++];
        else arr[k] = arr_r[j++];
        k++;
    }

    while (i < len1){
        arr[k++] = arr_l[i++];
    }
    while (j < len2){
        arr[k++] = arr_r[j++];
    }
}

void mergeSort(vector<int>& arr, int left, int right){
    if (left >= right) return;
    int mid = (left + right) / 2;
    mergeSort(arr, left, mid);
    mergeSort(arr, mid + 1, right);
    merge(arr, left, mid, right);
}