#include <bits/stdc++.h>

using namespace std;

int FenwickTree2D[1234][1234];

int sum(int idx_x, int idx_y){
    int res = 0;
    for(int i = idx_x; i >= 0; i = (i & (i + 1)) - 1){
        for(int j = idx_y; j >= 0; j = (j & (j  + 1)) - 1){
            res += FenwickTree2D[i][j];
        }
    }
    return res;
}

void add(int idx_x, int idx_y, int value, int n, int m){
    for(int i = idx_x; i < n; i = i | (i + 1)){
        for(int j = idx_y; j < m; j = j | (j + 1)){
            FenwickTree2D[i][j] += value;
        }
    }
}

int sumRange(int idx_x_1, int idx_y_1, int idx_x_2, int idx_y_2){
    if(idx_x_1 > idx_x_2){
        swap(idx_x_1, idx_x_2);
    }
    if(idx_y_1 > idx_y_2){
        swap(idx_y_1, idx_y_2);
    }
    int bottom_right = sum(idx_x_2, idx_y_2);
    int bottom_left = sum(idx_x_1 - 1, idx_y_2);
    int up_right = sum(idx_x_2, idx_y_1 - 1);
    int up_left = sum(idx_x_1 - 1, idx_y_1 - 1);
    return (bottom_right - bottom_left - up_right + up_left);
}

int main(int argc, char const *argv[]) {
    int n = 5, m = 4;
    int vet[][4] = {{1, 5, -2, 0},
                    {5, 8, -1, 2},
                    {1, 3, 0, -2},
                    {10, 1, 5, 7},
                    {0, -5, 6, 6}};

    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            add(i, j, vet[i][j], n, m);
        }
    }

    cout << sumRange(0, 0, 2, 1) << endl; // Saida = 23
    cout << sumRange(1, 1, 3, 1) << endl; // Saida = 12
    cout << sumRange(3, 2, 1, 0) << endl; // Saida = 32
    cout << sumRange(3, 3, 3, 3) << endl; // Saida = 7
    cout << sumRange(1, 2, 2, 3) << endl; // Saida = -1]
    cout << sumRange(0, 0, n - 1, m - 1) << endl; // Saida = 50

    return 0;
}
