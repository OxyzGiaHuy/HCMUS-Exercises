#include <iostream>
#define MAX 1000

using namespace std;


int LISTopDown(int* A, int* T, int* prev, int i, int& lastPos, int& maxLength){
    if (T[i] != -1) return T[i];
    T[i] = 1;
    prev[i] = -1;
    for (int j = 0; j < i; j++){
        int Tj = LISTopDown(A, T, prev, j, lastPos, maxLength);
        if (A[j] < A[i]){
            T[i] = max(T[i], Tj + 1);
            prev[i] = j;
            if (maxLength < T[i]){
                maxLength = T[i];
                lastPos = i;
            }
        }
    }
    return T[i];
}

void LISBottomUp(int A[], int T[], int n, int& maxLength, int prev[], int& lastPos){
    maxLength = 0;
    for (int i = 0; i < n; i++){
        T[i] = 1;
        prev[i] = -1;
        for (int j = 0; j < i; j++){
            if (A[j] < A[i]) {
                T[i] = max(T[i], T[j] + 1);
                prev[i] = j;
                if (maxLength < T[i]){
                    maxLength = T[i];
                    lastPos = i;
                }
            }
        }
        
    }
}

void findSubset(int* arr, int* prev, int maxLength, int lastPos, int* res){
    for (int i = 0; i < maxLength; i++){
        res[maxLength - 1 - i] = arr[lastPos];
        lastPos = prev[lastPos]; 
    }
}


int main() {
    int arr[] = {1, 5, 9, 2, 4, 7, 8};
    int n = sizeof(arr) / sizeof(arr[0]);
    int T[n];
    int prev[MAX];
    int res[MAX];
    for (int i = 0; i < n; i++)
        T[i] = -1; 

    int maxLength = 0, lastPos = 0;
    cout << "Top Down: \n";
    LISTopDown(arr, T, prev, n-1, lastPos, maxLength);
    findSubset(arr, prev, maxLength, lastPos, res);
    for (int i = 0; i < maxLength; i++){
        cout << res[i] << " ";
    }
    
    cout << "\nBottom Up:\n";
    LISBottomUp(arr, T, n, maxLength, prev, lastPos);
    findSubset(arr, prev, maxLength, lastPos, res);
    for (int i = 0; i < maxLength; i++){
        cout << res[i] << " ";
    }
    return 0;
}