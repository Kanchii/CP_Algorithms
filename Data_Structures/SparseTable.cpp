#include <bits/stdc++.h>

using namespace std;

int st[123456][25];

void pre_processamento_soma(int *vet, int n){
    for(int i = 0; i < n; i++){
        st[i][0] = vet[i];
    }
    for(int j = 1; j <= 24; j++){
        for(int i = 0; i + (1 << j) <= n; i++){
            st[i][j] = st[i][j - 1] + st[i + (1 << (j - 1))][j - 1];
        }
    }
}

void pre_processamento_minimo(int *vet, int n){
    for(int i = 0; i < n; i++){
        st[i][0] = vet[i];
    }
    for(int j = 1; j <= 24; j++){
        for(int i = 0; i + (1 << j) <= n; i++){
            st[i][j] = min(st[i][j - 1], st[i + (1 << (j - 1))][j - 1]);
        }
    }
}

int query_soma(int l, int r){
    int res = 0;
    int diff = r - l + 1;
    for(int i = 24; i >= 0; i--){
        if(diff & (1 << i)){
            res += st[l][i];
            l += (1 << i);
        }
    }
    return res;
}

int query_minimo_O1(int l, int r){
    int dist = (r - l + 1);
    int logg = (int)log2(dist);
    return min(st[l][logg], st[r - (1 << logg) + 1][logg]);
}

int query_minimo_Log(int l, int r){
    int res = 1e9;
    int diff = r - l + 1;
    for(int i = 24; i >= 0; i--){
        if(diff & (1 << i)){
            res = min(res, st[l][i]);
            l += (1 << i);
        }
    }
    return res;
}

int main(int argc, char const *argv[]) {

    int vet[] = {1, 2, -5, 0, 1, 10, 5, 6, -3, 2};
    int n = 10;
    pre_processamento_soma(vet, n);
    cout << "Query_soma (1, 6) = " << query_soma(1, 6) << endl; // Saida = 13
    cout << "Query_soma (3, 9) = " << query_soma(3, 9) << endl; // Saida = 21
    cout << "Query_soma (5, 5) = " << query_soma(5, 5) << endl; // Saida = 10
    pre_processamento_minimo(vet, n);
    cout << "Query_minimo_O1 (1, 6) = " << query_minimo_O1(1, 6) << endl; // Saida = -5
    cout << "Query_minimo_O1 (3, 9) = " << query_minimo_O1(3, 9) << endl; // Saida = -3
    cout << "Query_minimo_O1 (5, 5) = " << query_minimo_O1(5, 5) << endl; // Saida = 10

    cout << "Query_minimo_Log (1, 6) = " << query_minimo_Log(1, 6) << endl; // Saida = -5
    cout << "Query_minimo_Log (3, 9) = " << query_minimo_Log(3, 9) << endl; // Saida = -3
    cout << "Query_minimo_Log (5, 5) = " << query_minimo_Log(5, 5) << endl; // Saida = 10

    return 0;
}
