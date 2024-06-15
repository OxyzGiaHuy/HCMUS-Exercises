#include<iostream>
#define MAX 1000
using namespace std;

// bottom up
void coinChangeBottomUp(int* coin, int N, int M, int& minCoins, int* listCoin){
    int T[M + 1];
    T[0] = 0;
    int usedCoin[M + 1];
    usedCoin[0] = -1;
    for (int i = 1; i <= M; i++){
        T[i] = INT_MAX;
        for (int j = 0; j < N; j++){
            if (coin[j] <= i){
                int minCoin = T[i - coin[j]];
                if (minCoin + 1 < T[i]){
                    T[i] = minCoin + 1;
                    usedCoin[i] = coin[j]; 
                }
            }  
        }
    }    
    minCoins = T[M];
    int k = 0;
    int tmp = M;
    while (tmp > 0){
        listCoin[k++] = usedCoin[tmp];
        tmp -= usedCoin[tmp];
    }
}

int coinChangeTopDown(int* coin, int N, int M, int* T){
    if (T[M] != -1) return T[M];
    T[0] = 0;
    int res = INT_MAX;
    for (int j = 0; j < N; j++){
        if (coin[j] <= M){
            res = min(res, 1 + coinChangeTopDown(coin, N, M - coin[j], T));
        }
    }
    T[M] = res;
    return T[M];
}


int main(){
    int coins[] = {5, 10, 25, 40, 75, 90};
    int N = sizeof(coins)/sizeof(coins[0]);
    int M = 600;
    
    // bottom up
    int listCoin[100];
    int minCoins = 0;
    coinChangeBottomUp(coins, N, M, minCoins, listCoin);
    cout << "(Bottom up) Minimum coins required is "
         << minCoins << "\n"
         << M << " = " << listCoin[0];
    for (int i = 1; i < minCoins; i++){
        cout << " + " << listCoin[i];
    }

    // top down
    int T[MAX];
    for (int i = 0; i < MAX; i++)
        T[i] = -1;
    cout << "\n(Top down) Minimum coins required is "
         << coinChangeTopDown(coins, N, M, T) << "\n";
    return 0;
}