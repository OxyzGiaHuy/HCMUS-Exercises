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
        arr[j + 1] = pivot;
    }
}

void diagonalSort(vector<vector<int>>& matrix){
    int m = matrix.size();
    int n = matrix[0].size();
    vector<int> elements;

    for (int i = 0; i < m; i++){
        for (int j = 0; j < n; j++){
            elements.push_back(matrix[i][j]);
        }
    }    

    insertionSort(elements);

    int index = 0;
    for (int sum = 0; sum < m + n - 1; sum++){
        for (int i = 0; i < m; i++){
            int j = sum - i;
            if (j >= 0 && j < n) matrix[i][j] = elements[index++];
        }
    }
}

void zigzagDiagonalSort(vector<vector<int>>& matrix){
    int m = matrix.size();
    int n = matrix[0].size();
    vector<int> elements;

    for (int i = 0; i < m; i++){
        for (int j = 0; j < n; j++){
            elements.push_back(matrix[i][j]);
        }
    }    

    insertionSort(elements);

    int index = 0;
    for (int sum = 0; sum < m + n - 1; sum++){
        if (sum % 2 == 0){
            for (int i = 0; i < m; i++){
                int j = sum - i;
                if (j >= 0 && j < n) matrix[i][j] = elements[index++];
            }
        }
        else {
            for (int i = m - 1; i >= 0; i--){
                int j = sum - i;
                if (j >= 0 && j < n) matrix[i][j] = elements[index++];
            }
        }
        
    }
}

int main(){
    vector<vector<int>> matrix = {
        {2, 3, 7},
        {8, 9, 6},
        {1, 4, 5}
    };

    cout << "Matrix:\n";
    for (const auto& row : matrix) {
        for (int x : row) {
            cout << x << " ";
        }
        cout << "\n";
    }

    zigzagDiagonalSort(matrix);

    cout << "\nAfter sorting:\n";
    for (const auto& row : matrix) {
        for (int x : row) {
            cout << x << " ";
        }
        cout << "\n";
    }

    return 0;
}