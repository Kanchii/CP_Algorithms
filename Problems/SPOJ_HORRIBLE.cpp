#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

struct Node {
    Node *l, *r;
    ll key, prior;
    ll num_child;
    ll lazy;
    ll sum;
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
            ll sumL = t -> l ? (t -> l -> sum) : 0;
            ll sumR = t -> r ? (t -> r -> sum) : 0;
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

ll range_Query(Node *root, int l, int r){
    Node *left, *mid, *right;
    split(root, l - 1, left, mid, 0);
    // cout << left -> sum << " " << mid -> sum << endl;
    split(mid, r, root, right, l);
    ll res = root -> sum;
    // cout << "Soma no intervalo [" << l << ", " << r << "] = " << root -> sum << endl;
    merge(mid, left, root);
    merge(root, mid, right);

    return res;
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
    ios_base::sync_with_stdio(false);
    srand(time(NULL));
    int t;
    cin >> t;
    while(t--){
        int n, m;
        cin >> n >> m;

        Node *root = NULL;
        for(int i = 0 ; i < n; i++){
            Node *aux = create_Node(0);
            insert(root, aux, i);
            // cout << i << " " << root -> sum << endl;
        }

        for(int i = 0; i < m; i++){
            int tipo; cin >> tipo;
            if(tipo == 0){
                int a, b, c;
                cin >> a >> b >> c;
                a--; b--;
                range_Update(root, a, b, c);
            } else {
                int a, b;
                cin >> a >> b;
                a--; b--;
                cout << range_Query(root, a, b) << endl;
            }
        }

        free(root);
    }
    return 0;
}
