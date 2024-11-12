#include<iostream>
#include<vector>

using namespace std;

void countingForRadix(vector<int>& arr, int exp){
    int n = arr.size();
    int count_arr[10] = {0};
    vector<int> digit_arr(n);

    for (int i = 0; i < n; i++){
        count_arr[(arr[i] / exp) % 10]++;
    }
    for (int i = 1; i < n; i++){
        count_arr[i] += count_arr[i - 1];
    }
    for (int i = n; i >= 0; i--){
        digit_arr[count_arr[(arr[i] / exp) % 10] - 1] = arr[i];
        count_arr[(arr[i] / exp) % 10]--;
    }
    arr = digit_arr;
}

void radixSort(vector<int>& arr){
    int max = arr[0];
    int n = arr.size();
    
    for (int num: arr){
        if (num > max) max = num;
    }

    for (int exp = 1; max / exp > 0; exp *= exp){
        countingForRadix(arr, exp);
    }
}