#include <bits/stdc++.h>

using namespace std;

int FenwickTree[123456];

int sum(int idx){
    int res = 0;
    for(; idx >= 0; idx = (idx & (idx + 1)) - 1){
        res += FenwickTree[idx];
    }
    return res;
}

void add(int idx, int value, int n){
    for(; idx < n; idx = idx | (idx + 1)){
        FenwickTree[idx] += value;
    }
}

int sumRange(int l, int r){
    return (sum(r) - sum(l - 1));
}

int main(int argc, char const *argv[]) {
    int n = 10;
    int vet[] = {1, 0, -2, 0, 1, 5, 10, -3, 2, 5};

    for(int i = 0; i < n; i++){
        add(i, vet[i], n);
    }

    cout << sumRange(0, 9) << endl; // Saida = 19
    cout << sumRange(1, 3) << endl; // Saida = -2
    cout << sumRange(4, 4) << endl; // Saida = 1
    cout << sumRange(9, 9) << endl; // Saida = 5
    cout << sumRange(1, 8) << endl; // Saida = 13

    return 0;
}
