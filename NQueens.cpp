#include<iostream>
#define MAX 20
using namespace std;

bool col[MAX] = {0};
bool forwardDiagonal[2*MAX - 1] = {0};
bool backwardDiagonal[2*MAX - 1] = {0};

bool board[MAX][MAX] = {0};

int cnt = 0;

void printBoard(int  n){
    cout << "Cach " << ++cnt << ": \n";
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            cout << board[i][j] << " ";
        }
        cout << "\n";
    }
    cout << "\n";
}

void setQueenPos(int n, int r){
    if (r == n){
        printBoard(n);
        return;
    }
    for (int c = 0; c < n; c++){
        if (!col[c] && !forwardDiagonal[c + r] && !backwardDiagonal[r + (n - 1) - c]){

            board[r][c] = 1;
            col[c] = true;
			forwardDiagonal[r + c] = true;
			backwardDiagonal[r + (n - 1) - c] = true;
			
            setQueenPos(n, r + 1);
			
            backwardDiagonal[r + (n - 1) - c] = false;
			forwardDiagonal[r + c] = false;
			col[c] = false;    
            board[r][c] = 0;
        }
    }
}

int main(){
    int n;
    cout << "Enter size of board: ";
    cin >> n;
    setQueenPos(n, 0);
    return 0;
}
