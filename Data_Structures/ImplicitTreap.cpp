#include <bits/stdc++.h>

using namespace std;

struct Node {
    Node *l, *r;
    int key, prior;
    int num_child;
    int sum;
};

int cnt(Node *t){
    return (t ? t -> num_child : 0);
}

void update_Child(Node * &t){
    if(t){
        t -> num_child = 1 + cnt(t -> l) + cnt(t -> r);
    }
}

void update_Sum(Node *t){
    if(!t) return;
    int sumL = t -> l ? (t -> l -> sum) : 0;
    int sumR = t -> r ? (t -> r -> sum) : 0;
    t -> sum = t -> key + sumL + sumR;
}

void split(Node *t, int key, Node * &l, Node * &r, int acc){
    if(!t){
        r = l = NULL;
        return;
    }
    int aux = acc + cnt(t -> l);
    if(aux > key){
        split(t -> l, key, l, t -> l, acc), r = t;
    } else {
        split(t -> r, key, t -> r, r, aux + 1), l = t;
    }
    update_Child(t);
    update_Sum(t);
}

void merge(Node * &t, Node *l, Node *r){
    if(!l or !r){
        t = (l ? l : r);
        update_Child(t);
        return;
    }
    if(l -> prior > r -> prior){
        merge(l -> r, l -> r, r), t = l;
    } else {
        merge(r -> l, l, r -> l), t = r;
    }
    update_Child(t);
    update_Sum(t);
}

void insert(Node * &t, Node *it, int idx){
    if(!t){
        t = it;
        update_Child(t);
        return;
    }
    Node *left, *right;
    split(t, idx, left, right, 0);
    merge(t, left, it);
    merge(t, t, right);
    update_Child(t);
    update_Sum(t);
}

int range_Query(Node *root, int l, int r){
    Node *left, *right, *range;
    split(root, l, left, right, 0);
    split(right, r + 1, range, left, l);
    cout << "Soma no intervalo [" << l << ", " << r << "] = " << range -> sum << endl;
}

// void erase(Node * &t, Node *it){
//     if(t -> key == it -> key){
//         merge(t, t -> l, t -> r);
//     } else if(t -> key > it -> key){
//         erase(t -> l, it);
//     } else {
//         Node *aux = new Node;
//         erase(t -> r, it);
//     }
//     update_Child(t);
//     update_Sum(t);
// }

Node *create_Node(int x){
    Node *aux = new Node;
    aux -> prior = rand();
    aux -> key = x;
    aux -> l = aux -> r = NULL;
    aux -> num_child = 0;
    return aux;
}

void print_Tree(Node *t){
    if(!t) return;
    cout << "(" << t -> key << ", " << t -> prior << ") -> " << t -> num_child << endl;
    print_Tree(t -> l);
    print_Tree(t -> r);
}

int main(int argc, char const *argv[]) {
    srand(time(NULL));
    int vet[] = {-1, 2, 0, 3, 5, 2};
    int n = 6;

    Node *root = NULL;

    for(int i = 0 ; i < n; i++){
        Node *aux = create_Node(vet[i]);
        insert(root, aux, i);
    }

    print_Tree(root);
    cout << endl;
    range_Query(root, 1, 1);

    cout << endl;
    Node *aux = create_Node(6);
    insert(root, aux, 3);
    // erase(root, aux);

    print_Tree(root);
    cout << endl;


    free(root);

    return 0;
}
