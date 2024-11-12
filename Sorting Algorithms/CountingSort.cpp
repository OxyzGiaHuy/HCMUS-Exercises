#include<iostream>
#include<vector>

using namespace std;

void countingSort(vector<int>& arr){
    int n = arr.size();
    int max = arr[0];
    int min = arr[0];

    for (int num: arr){
        if (max < num) num = max;
        if (min > num) num = min;
    }
    int count_size = max - min + 1;
    vector<int> count_arr(count_size), sort_arr(n);

    for (int i = 0; i < n; i++){
        count_arr[arr[i] - min]++;
    }
    for (int i = 1; i < n; i++){
        count_arr[i] += count_arr[i - 1];
    }
    for (int i = n - 1; i >= 0; i--){
        sort_arr[count_arr[arr[i] - min] - 1] = arr[i];
        count_arr[arr[i] - min]--;
    }
    arr = sort_arr;
}