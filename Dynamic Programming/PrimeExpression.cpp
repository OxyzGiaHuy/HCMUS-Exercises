#include<iostream>
#define MAX 1000
using namespace std;


// bottom up
void primeExpressionBottomUp(int* prime, int lenPrime, int N, int& minPrime, int* listPrime){
    int T[N + 1];
    T[0] = 0; T[1] = 0; T[2] = 1; T[3] = 1;
    int usedPrime[N + 1];
    usedPrime[0] = -1; usedPrime[1] = -1; usedPrime[2] = 2; usedPrime[3] = 3;

    for (int i = 4; i <= N; i++){
        T[i] = INT_MAX;
        for (int j = 0; j < lenPrime; j++){
            if (prime[j] <= i){
                if (T[i - prime[j]] == 0 && ((i - prime[j]) == 0 || (i -prime[j] == 1))) continue;
                else if (1 + T[i - prime[j]] < T[i])
                    T[i] = 1 + T[i - prime[j]];
                    usedPrime[i] = prime[j];
            }
        }
    }
    minPrime = T[N];

    int tmp = N;
    int cnt = 0;
    while (tmp > 0){
        listPrime[cnt++] = usedPrime[tmp];
        tmp -= usedPrime[tmp];
    }
}

int primeExpressionTopDown(int* prime, int lenPrime, int N, int* T){
    if (T[N] != -1) return T[N];
    T[0] = 0; T[1] = 0; T[2] = 1; T[3] = 1;
    int usedPrime[N + 1];
    usedPrime[0] = -1; usedPrime[1] = -1; usedPrime[2] = 2; usedPrime[3] = 3;

    int res = INT_MAX;
    for (int j = 0; j < lenPrime; j++){
        if (prime[j] <= N){
            if (T[N - prime[j]] == 0 && ((N - prime[j]) == 0 || (N -prime[j] == 1))) continue;
            else{
                int minPrime = 1 + primeExpressionTopDown(prime, lenPrime, N - prime[j], T);
                if (minPrime < res) res = minPrime;
            }
        }
    }
    T[N] = res;

    return T[N];
}

int main(){
    int prime[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29};
    int lenPrime = sizeof(prime)/sizeof(prime[0]);
    int N = 38;
    
    // bottom up
    int minPrimeBottomUp = 0;
    int listPrime[MAX];
    primeExpressionBottomUp(prime, lenPrime, N, minPrimeBottomUp, listPrime);
    cout << "(Bottom Up) Minimum primes required is "
         << minPrimeBottomUp << "\n"
         << N << " = " << listPrime[0];
    for (int i = 1; i < minPrimeBottomUp; i++){
        cout << " + " << listPrime[i];
    }

    // top down
    int T[MAX];
    for (int i = 0; i < MAX; i++){
        T[i] = -1;
    }
    int minPrimeTopDown = primeExpressionTopDown(prime, lenPrime, N, T);
    cout << "\n(Top down) Minimum primes required is " << minPrimeTopDown;
    
    return 0;

}