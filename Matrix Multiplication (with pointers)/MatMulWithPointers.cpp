#include<iostream>
#include<fstream>
using namespace std;

bool readMatrix(const char* filename, int** &matrix, int& rows, int& cols);
void printMatrix(const char* filename, int** matrix, int rows, int cols);
bool multiplyMatrices(int** a, int aRows, int aCols, int** b, int bRows, int bCols, int** &res, int &resRows, int &resCols);
void transposeMatrix(int** matrix, int rows, int cols, int** &res, int &resRows, int &resCols);

bool readMatrix(const char* filename, int** &matrix, int& rows, int& cols){
    ifstream file;
    file.open(filename, ios::in);
    if (!file.is_open()) {
        cout << "Can not open file\n";
        return false;  
    }

    rows = 0;
    cols = 0;
    int tmp_cols = 0;
    char c;
    bool first_row = true;

    // 1 loop to find row and col
    while (file.get(c)){
        if (c == ' '){
            if (first_row) tmp_cols++; 
        }
        else if (c == '\n'){
            if (first_row){
                tmp_cols++;
                cols = tmp_cols;
                first_row = false;
            }
            rows++;
        }
    }

    if (rows == 0 || cols == 0) {
        cout << "Invalid matrix format.\n";
        return false;
    }

    if (first_row && tmp_cols > 0) {
        cols = tmp_cols;
        rows = 1;
    } else if (c != '\n') {
        rows++;
    }

    matrix = new int*[rows];
    for (int i = 0; i < rows; ++i) {
        matrix[i] = new int[cols];
    }

    file.clear();
    file.seekg(0, ios::beg);
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            file >> matrix[i][j];
        }
    }

    file.close();
    return true;
}

void printMatrix(const char* filename, int** matrix, int rows, int cols){
    ofstream file;
    file.open(filename, ios::out);
    if (!file.is_open()) {
        cout << "Can not open file\n";
        return;
    }

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            file << matrix[i][j];
            if (j < cols - 1) file << " "; 
        }
        file << "\n"; 
    }

    file.close();
}

bool multiplyMatrices(int** a, int aRows, int aCols, int** b, int bRows, int bCols, int** &res, int &resRows, int &resCols){
    if (aCols != bRows){
        cout << "1.Can not multiply matrices!\n";
        return false;
    }
    resRows = aRows;
    resCols = bCols;

    res = new int*[resRows];
    for (int i = 0; i < resRows; i++){
        res[i] = new int[resCols];
    }

    for (int i = 0; i < resRows; i++){
        for (int j = 0; j < resCols; j++){
            res[i][j] = 0;
            for (int k = 0; k < aCols; k++){
                res[i][j] += a[i][k]*b[k][j];
            }
        }
    }
    return true;
}

void transposeMatrix(int** matrix, int rows, int cols, int** &res, int &resRows, int &resCols){
    resRows = cols;
    resCols = rows;

    res = new int*[resRows];
    for (int i = 0; i < resRows; i++){
        res[i] = new int[resCols];
    }

    for (int i = 0; i < resRows; i++){
        for (int j = 0; j < resCols; j++){
            res[i][j] = matrix[j][i];
        }
    }
}

int main(){
    int **a, **b, **c, **c_t;
    int a_rows, a_cols, b_rows, b_cols, c_rows, c_cols, c_t_rows, c_t_cols; 
    
    if (!readMatrix("matrix_a.txt", a, a_rows, a_cols)) cout << "Can not read matrix a!\n";
    if (!readMatrix("matrix_b.txt", b, b_rows, b_cols)) cout << "Can not read matrix b!\n";

    if (multiplyMatrices(a, a_rows, a_cols, b, b_rows, b_cols, c, c_rows, c_cols)){
        printMatrix("matrix_c.txt", c, c_rows, c_cols);
        transposeMatrix(c, c_rows, c_cols, c_t, c_t_rows, c_t_cols);
        printMatrix("matrix_c_transposed.txt", c_t, c_t_rows, c_t_cols);
    }
    else {
        cout << "Can not multiply matrices!\n";
    }

    return 0;
}