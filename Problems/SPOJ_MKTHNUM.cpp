#include <bits/stdc++.h>

using namespace std;

struct Node {
    Node *left, *right;
    int acc;
};

Node *create_Node(){
    Node *node = new Node;
    node -> left = NULL;
    node -> right = NULL;
    node -> acc = 0;
    return node;
}

void init(Node *&node, int l, int r){
    if(l == r){
        Node *temp = create_Node();
        node = temp;
        return;
    }
    int mid = l + (r - l) / 2;
    Node *temp = create_Node();
    init(temp -> left, l, mid);
    init(temp -> right, mid + 1, r);
    node = temp;
}

void update(Node *&anc, Node *&node, int l, int r, int dest){
    if(l == r){
        Node *temp = create_Node();
        temp -> acc = 1;
        node = temp;
        return;
    }
    int mid = l + (r - l) / 2;
    Node *temp = create_Node();
    if(dest > mid){
        update(anc -> right, temp -> right, mid + 1, r, dest);
        temp -> left = anc -> left;
    } else {
        update(anc -> left, temp -> left, l, mid, dest);
        temp -> right = anc -> right;
    }
    temp -> acc = (temp -> left -> acc + temp -> right -> acc);
    node = temp;
}

int query(Node *anc, Node *u, int l, int r, int kth){
    if(l == r){
        return l;
    }
    int mid = l + (r - l) / 2;
    int acc_Left = (u -> left -> acc) - (anc -> left -> acc);
    if(acc_Left >= kth){
        return query(anc -> left, u -> left, l, mid, kth);
    }
    return query(anc -> right, u -> right, mid + 1, r, kth - acc_Left);
}

int main(int argc, char const *argv[]) {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n, m;
    cin >> n >> m;

    vector<Node *> roots;
    Node *temp = create_Node();
    init(temp, 0, n - 1);
    roots.push_back(temp);

    int nums[n + 5];
    for(int i = 0; i < n; i++){
        cin >> nums[i];
    }
    vector<int> vet(nums, nums + n);
    sort(vet.begin(), vet.end());
    map<int, int> mapa;
    for(int i = 0; i < n; i++){
        mapa[vet[i]] = i;
    }

    for(int i = 0; i < n; i++){
        Node *temp = create_Node();
        update(roots[i] , temp, 0, n - 1, mapa[nums[i]]);
        roots.push_back(temp);
    }

    for(int i = 0; i < m; i++){
        int l, r, kth;
        cin >> l >> r >> kth;
        if(r - l + 1 < kth){
            cout << -1 << endl;
            continue;
        }
        cout << vet[query(roots[l - 1], roots[r], 0, n - 1, kth)] << endl;
    }

    return 0;
}
