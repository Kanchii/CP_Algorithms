#include <bits/stdc++.h>

using namespace std;

struct Node {
    Node *l, *r;
    int rev, prior;
    int size, val;
    int pares;
};

Node *createNode(int val){
    Node *node = new Node;
    node -> rev = false;
    node -> size = 1;
    node -> val = val;
    node -> l = node -> r = NULL;
    node -> pares = 0;
    node -> prior = rand();
    return node;
}

int getSize(Node *t){
    return (t ? t -> size : 0);
}

void updatePares(Node * &t){
    if(!t) return;
    t -> pares = (t -> val % 2 == 0 ? 1 : 0) + (t -> l ? t -> l -> pares : 0) + (t -> r ? t -> r -> pares : 0);
}

void updateSize(Node * &t){
    if(t){
        t -> size = 1 + (t -> l ? t -> l -> size : 0) + (t -> r ? t -> r -> size : 0);
    }
}

void rev(Node * &t){
    if(!t or !(t -> rev)) return;
    swap(t -> l, t -> r);
    if(t -> l) t -> l -> rev ^= true;
    if(t -> r) t -> r -> rev ^= true;
    t -> rev = false;
}

void split(Node *t, Node * &l, Node * &r, int pos, int acc){
    if(!t) l = r = NULL;
    else {
        rev(t);
        int tmp = acc + getSize(t -> l);
        if(tmp <= pos){
            split(t -> r, t -> r, r, pos, tmp + 1), l = t;
        } else {
            split(t -> l, l, t -> l, pos, acc), r = t;
        }

        updateSize(t);
        updatePares(t);
    }
}

void merge(Node * &t, Node *l, Node *r){
    rev(l), rev(r);
    if(!l or !r) t = l ? l : r;
    else {
        if(l -> prior > r -> prior){
            merge(l -> r, l -> r, r), t = l;
        } else {
            merge(r -> l, l, r -> l), t = r;
        }
    }
    updateSize(t);
    updatePares(t);
}

void update(Node * &t, int pos, int val){
    Node *l = NULL, *m = NULL, *r = NULL;
    split(t, l, m, pos - 1, 0);
    split(m, t, r, pos, pos);
    t -> val = val;
    merge(m, l, t);
    merge(t, m, r);
}

int consultaPar(Node *t, int ll, int rr){
    Node *l = NULL, *m = NULL, *r = NULL;
    // printf("FELIEPRA1\n");
    // printf("%d\n", ll - 1);
    split(t, l, m, ll - 1, 0);
    // printf("FELIEPRA2\n");
    // printf("sizeL = %d | sizeR = %d\n", getSize(l), getSize(m));
    split(m, t, r, rr, ll);
    // printf("FELIEPRA3\n");
    int res = t -> pares;
    // printf("FELIEPRA4\n");
    merge(m, l, t);
    // printf("FELIEPRA5\n");
    merge(t, m, r);
    // printf("FELIEPRA6\n");
    return res;
}

void insert(Node * &t, Node *it, int pos){
    Node *l = NULL, *m = NULL, *r = NULL;
    split(t, l, r, pos-1, 0);
    // printf("sizeL = %d | sizeR = %d\n", getSize(l), getSize(r));
    merge(t, l, it);
    merge(t, t, r);

}

int consultaImp(Node *t, int l, int r){
    int res = consultaPar(t, l, r);
    return ((r - l + 1) - res);
}

void reverse(Node *t, int ll, int rr){
    Node *l = NULL, *m = NULL, *r = NULL;
    split(t, l, m, ll - 1, 0);
    split(m, t, r, rr, ll);
    t -> rev ^= true;
    merge(m, l, t);
    merge(t, m, r);
}

void printIn(Node *t){
    if(!t) return;
    cout << t -> val << " -> " << (t -> l ? t -> l -> val : -1) << endl;
    cout << t -> val << " -> " << (t -> r ? t -> r -> val : -1) << endl;
    printIn(t -> l);
    printIn(t -> r);
}

int main(int argc, char const *argv[]) {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    srand(time(NULL));
    int p, q;
    while(scanf("%d %d", &p, &q) != EOF){
        Node *root = NULL;
        for(int i = 0; i < p; i++){
            int x;
            scanf("%d", &x);
            Node *tmp = createNode(x);
            insert(root, tmp, i);
        }
        // printIn(root);
        // cout << endl;
        // cout << getSize(root) << endl;
        for(int i = 0; i < q; i++){
            char c;
            getchar();
            scanf("%c", &c);
            int a, b;
            scanf("%d %d", &a, &b);
            // cout << a << " " << b << " " << c << endl;
            if(c == 'O'){
                printf("%d\n", consultaImp(root, a - 1, b - 1));
            } else if(c == 'E'){
                printf("%d\n", consultaPar(root, a - 1, b - 1));
            } else if(c == 'S'){
                update(root, a - 1, b);
            } else {
                reverse(root, a - 1, b - 1);
            }
        }
        free(root);
    }
    return 0;
}
