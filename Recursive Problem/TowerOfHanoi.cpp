#include<iostream>
using namespace std;

int step = 0;

void printMove(char* src, char* des) {
	cout << "Step " << ++step << ": " << src << " to " << des << endl;
}

void towerOfHanoi(int n, char* src, char* des, char* mis){
    if (n == 1) {
        printMove(src, des);
        return;
    } 
    else{
        towerOfHanoi(n - 1, src, mis, des);
        printMove(src, mis);
        towerOfHanoi(n - 1, src, des, mis);
    }   
}

int main(){
    char src[] = "A";
    char mis[] = "B";
    char des[] = "C";
    int n;
    cout << "Enter the number of disks: ";
    cin >> n;
    towerOfHanoi(n, src, des, mis);
}