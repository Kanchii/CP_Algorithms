#include <bits/stdc++.h>

using namespace std;

struct Node {
    int parent, rank;
};

Node dsu[123456];

int Find(int v){
    if(dsu[v].parent == v){
        return v;
    }
    return dsu[v].parent = Find(dsu[v].parent);
}

void Union(int a, int b){
    int u = Find(a);
    int v = Find(b);
    if(dsu[v].rank > dsu[u].rank){
        swap(u, v);
    }
    dsu[v].parent = u;
    if(dsu[u].rank == dsu[v].rank){
        dsu[u].rank++;
    }
}

int main(int argc, char const *argv[]) {

    int n = 10;

    for(int i = 0; i < n; i++){
        dsu[i].parent = i;
        dsu[i].rank = 0;
    }

    Union(0, 2);
    Union(1, 3);
    cout << "Parent[" << 0 << "] = " << Find(0) << endl; // Saida = 0
    cout << "Parent[" << 1 << "] = " << Find(1) << endl; // Saida = 1

    Union(0, 1);

    cout << "Parent[" << 0 << "] = " << Find(0) << endl; // Saida = 0
    cout << "Parent[" << 1 << "] = " << Find(1) << endl; // Saida = 0

    cout << "Parent[" << 4 << "] = " << Find(4) << endl; // Saida = 4

    Union(4, 1);

    cout << "Parent[" << 4 << "] = " << Find(4) << endl; // Saida = 0

    return 0;
}
