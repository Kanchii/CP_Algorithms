#include <bits/stdc++.h>

using namespace std;

struct Node {
    Node *l, *r;
    int key, prior;
    int num_child;
};

int cnt(Node *t){
    return (t ? t -> num_child : 0);
}

void update_Child(Node * &t){
    if(t){
        t -> num_child = 1 + cnt(t -> l) + cnt(t -> r);
    }
}

void split(Node *t, int key, Node * &l, Node * &r){
    if(!t){
        r = l = NULL;
        return;
    }
    if(t -> key > key){
        split(t -> l, key, l, t -> l), r = t;
    } else {
        split(t -> r, key, t -> r, r), l = t;
    }
    update_Child(t);
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
}

void insert(Node * &t, Node *it){
    if(!t){
        t = it;
        update_Child(t);
        return;
    }
    if(it -> prior > t -> prior){
        split(t, it -> key, it -> l, it -> r), t = it;
    } else {
        if(t -> key > it -> key){
            insert(t -> l, it);
        } else {
            insert(t -> r, it);
        }
    }
    update_Child(t);
}

void erase(Node * &t, Node *it){
    if(t -> key == it -> key){
        merge(t, t -> l, t -> r);
    } else if(t -> key > it -> key){
        erase(t -> l, it);
    } else {
        Node *aux = new Node;
        erase(t -> r, it);
    }
    update_Child(t);
}

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
    cout << t -> key << ": " << t -> num_child << endl;
    print_Tree(t -> l);
    print_Tree(t -> r);
}

int main(int argc, char const *argv[]) {
    srand(time(NULL));
    int vet[] = {5, -5, 0, 25, 3, 8, 1, 6, 10, 4};
    int n = 10;

    Node *root = NULL;

    for(int i = 0 ; i < n; i++){
        Node *aux = create_Node(vet[i]);
        insert(root, aux);
    }

    print_Tree(root);

    Node *aux = create_Node(6);
    erase(root, aux);

    print_Tree(root);

    free(root);

    return 0;
}
