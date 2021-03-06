#include <bits/stdc++.h>

using namespace std;

struct Node {
    Node *l, *r;
    int key, prior;
    int num_child;
    int lazy;
    int sum;
};

int cnt(Node *t){
    return (t ? t -> num_child : 0);
}

void update_Child(Node * &t){
    if(t) t -> num_child = 1 + cnt(t -> l) + cnt(t -> r);
}

void lazy(Node * &t){
    if(!t or t -> lazy == 0) return;
    t -> key += t -> lazy;
    t -> sum += (t -> lazy * t -> num_child);
    if(t -> l) t -> l -> lazy += t -> lazy;
    if(t -> r) t -> r -> lazy += t -> lazy;
    t -> lazy = 0;

}

void update_Sum(Node * &t){
    if(t){
        lazy(t -> l);
        lazy(t -> r);
        if(!(t -> l) and !(t -> r)){
            t -> sum = t -> key;
        } else {
            int sumL = t -> l ? (t -> l -> sum) : 0;
            int sumR = t -> r ? (t -> r -> sum) : 0;
            t -> sum = t -> key + sumL + sumR;
        }
    }
}

void split(Node *t, int key, Node * &l, Node * &r, int acc){
    if(!t){
        r = l = NULL;
    } else {
        lazy(t);
        int aux = acc + cnt(t -> l);
        if(aux <= key){
            split(t -> r, key, t -> r, r, aux + 1), l = t;
        } else {
            split(t -> l, key, l, t -> l, acc), r = t;
        }
        update_Child(t);
        update_Sum(t);
    }
}

void merge(Node * &t, Node *l, Node *r){
    lazy(l);
    lazy(r);
    if(!l or !r){
        t = (l ? l : r);
    } else {
        if(l -> prior > r -> prior){
            merge(l -> r, l -> r, r), t = l;
        } else {
            merge(r -> l, l, r -> l), t = r;
        }
    }
    update_Child(t);
    update_Sum(t);
}

void print_Tree(Node *t){
    if(!t) return;
    cout << "(" << t -> key << ", " << t -> prior << ") -> " << t -> num_child << endl;
    print_Tree(t -> l);
    print_Tree(t -> r);
}

void insert(Node * &t, Node *it, int idx){
    Node *left, *right;
    split(t, idx - 1, left, right, 0);
    Node *res;
    merge(res, left, it);
    merge(res, res, right);
    t = res;
    update_Child(t);
    update_Sum(t);
}

void erase(Node * &t, int idx){
    Node *left, *mid, *right;
    split(t, idx - 1, left, mid, 0);
    split(mid, idx, t, right, idx);
    merge(t, left, right);

    update_Child(t);
    update_Sum(t);
}

int range_Query(Node *root, int l, int r){
    Node *left, *mid, *right;
    split(root, l - 1, left, mid, 0);
    // cout << left -> sum << " " << mid -> sum << endl;
    split(mid, r, root, right, l);
    cout << "Soma no intervalo [" << l << ", " << r << "] = " << root -> sum << endl;
    merge(mid, left, root);
    merge(root, mid, right);

    return root -> sum;
}

void range_Update(Node * &root, int l, int r, int val){
    Node *left, *mid, *right;
    split(root, l - 1, left, mid, 0);
    split(mid, r, root, right, l);
    root -> lazy += val;
    merge(mid, left, root);
    merge(root, mid, right);
}

Node *create_Node(int x){
    Node *aux = new Node;
    aux -> prior = rand();
    aux -> key = x;
    aux -> l = aux -> r = NULL;
    aux -> num_child = 0;
    aux -> sum = x;
    aux -> lazy = 0;
    return aux;
}


int main(int argc, char const *argv[]) {
    srand(time(NULL));
    int vet[] = {-1, 2, 0, 3, 5, 2};
    int n = 6;

    Node *root = NULL;

    for(int i = 0 ; i < n; i++){
        Node *aux = create_Node(vet[i]);
        insert(root, aux, i);
        // cout << i << " " << root -> sum << endl;
    }

    print_Tree(root);
    cout << endl;

    for(int i = 0; i < n; i++){
        for(int j = i; j < n; j++){
            range_Query(root, i, j);
        }
    }

    range_Update(root, 1, 3, 3);
    cout << endl;

    // Vet = [-1, 5, 3, 6, 5, 2]

    for(int i = 0; i < n; i++){
        for(int j = i; j < n; j++){
            range_Query(root, i, j);
        }
    }
    //
    // Node *aux = create_Node(6);
    // insert(root, aux, 3);
    // Vetor = [-1, 2, 0, 6, 3, 5, 2]
    // n++;
    // cout << endl;
    // for(int i = 0; i < n; i++){
    //     for(int j = i; j < n; j++){
    //         range_Query(root, i, j);
    //     }
    // }
    // cout << endl;

    print_Tree(root);
    cout << endl;

    erase(root, 3);
    n--;

    print_Tree(root);
    cout << endl;

    free(root);

    return 0;
}
