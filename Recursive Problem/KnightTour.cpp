#include<iostream>

using namespace std;

int stepX[] = {2, 2, 1, -1, -2, -2, -1, 1};
int stepY[] = {1, -1, -2, -2, -1, 1, 2, 2};

int cnt = 0;
int orderOfMove[8][8];

void printOrderOfMove(){
    printf("How the knight traverses the board: \n");
    for (int i = 0; i < 8; i++){
        for (int j = 0; j < 8; j++){
            printf("%3d", orderOfMove[i][j]);
        }
        cout << "\n";
    }
}

bool findTour(int x, int y){
    if (cnt == 64) {
        printOrderOfMove();
        return true;
    }

    int minExit = 7;
    int exit[8] = { 0 };
    for (int i = 0; i < 8; i++) {
        int newX = x + stepX[i];
        int newY = y + stepY[i];
        if ((0 <= newX && newX < 8) && (0 <= newY && newY < 8) && orderOfMove[newX][newY] == 0) {
            for (int j = 0; j < 8; j++) {
                int nextNewX = newX + stepX[j];
                int nextNewY = newY + stepY[j];
                if ((0 <= nextNewX && nextNewX < 8) && (0 <= nextNewY && nextNewY < 8) && orderOfMove[nextNewX][nextNewY] == 0) {
                    exit[i]++;
                }
            }
            if (exit[i] < minExit) minExit = exit[i];
        }
        else exit[i] = -1;
    }

    for (int i = 0; i < 8; i++){
        int newX = x + stepX[i];
        int newY = y + stepY[i];
        if (exit[i] == minExit) {
            orderOfMove[newX][newY] = ++cnt;
            if (findTour(newX, newY)) return true;
            cnt--;
            orderOfMove[newX][newY] = 0;
        }
    }
    return false;
}

int main(){
    for (int i = 0; i < 8; ++i){
        for (int j = 0; j < 8; ++j){
            orderOfMove[i][j] = 0;
        }
    }
    int x, y;
    cout << "Enter the start position of the Knight (x,y): ";
    cin >> x >> y;
    cnt = 1;
    orderOfMove[x][y] = cnt;
    findTour(x,y);
    return 0;
}