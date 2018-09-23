#include <bits/stdc++.h>

using namespace std;

struct Tree {
    Tree *left, *right;
    int soma;
};

vector<Tree *> roots;
int n_roots;

Tree *createNode(){
    Tree *node = new Tree;
    node -> soma = 0;
    node -> left = NULL;
    node -> right = NULL;
    return node;
}

Tree *update(Tree *&orig, Tree *&u, int l, int r, int dest, int value){
    if(l == r){
        Tree *v = createNode();
        v -> soma = value;
        u = v;
        return NULL;
    }
    int mid = (l + r) / 2;
    Tree *v = createNode();
    if(dest > mid){
        update(orig -> right, v -> right, mid + 1, r, dest, value);
        v -> left = orig -> left;
    } else {
        update(orig -> left, v -> left, l, mid, dest, value);
        v -> right = orig -> right;
    }
    v -> soma = (v -> left -> soma + v -> right -> soma);
    u = v;
    return u;
}

int query(Tree *u, int l, int r, int ql, int qr){
    if(u == NULL) return 0;
    if(l > qr or r < ql) return 0;
    if(l >= ql and r <= qr) return u -> soma;
    int mid = (l + r) / 2;
    return query(u -> left, l, mid, ql, qr) + query(u -> right, mid + 1, r, ql ,qr);
}

void createRoot(Tree *&root, int l, int r, int *arr){
    if(l == r){
        Tree *aux = createNode();
        aux -> soma = arr[l];
        root = aux;
        return;
    }
    int mid = (l + r) / 2;
    Tree *v = createNode();
    createRoot(v -> left, l, mid, arr);
    createRoot(v -> right, mid + 1, r, arr);
    v -> soma = v -> left -> soma + v -> right -> soma;
    root = v;
}

int main(int argc, char const *argv[]) {

    int n = 5;
    int arr[] = {0, -2, 1, 5, 8};
    // for(int i = 0; i < n; i++){
    //     cin >> arr[i];
    // }
    Tree *root = createNode();
    createRoot(root, 0, n - 1, arr);
    roots.push_back(root);

    cout << "Saida usando a primeira arvore no intervalo [1, 3]: " <<  query(roots[0], 0, n - 1, 1, 3) << endl; // Saida = 4

    Tree *node_1 = createNode();
    update(roots[roots.size() - 1], node_1, 0, n - 1, 2, 5);
    roots.push_back(node_1);

    cout << "Saida usando a primeira arvore no intervalo [1, 3]: " <<  query(roots[0], 0, n - 1, 1, 3) << endl; // Saida = 4
    cout << "Saida usando a segunda arvore no intervalo [1, 3]: " <<  query(roots[1], 0, n - 1, 1, 3) << endl; // Saida = 8

    Tree *node_2 = createNode();
    update(roots[roots.size() - 1], node_2, 0, n - 1, 4, -8);
    roots.push_back(node_2);

    cout << "Saida usando a primeira arvore no intervalo [1, 4]: " << query(roots[0], 0, n - 1, 1, 4) << endl; // Saida = 12
    cout << "Saida usando a segunda arvore no intervalo [1, 4]: " <<  query(roots[1], 0, n - 1, 1, 4) << endl; // Saida = 16
    cout << "Saida usando a terceira arvore no intervalo [1, 4]: " <<  query(roots[2], 0, n - 1, 1, 4) << endl; // Saida = 0

    return 0;
}
