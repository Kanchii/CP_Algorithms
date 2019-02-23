#include <bits/stdc++.h>

using namespace std;

struct Node {
    int val;
    Node *l, *r;
};

struct Temp {
    Node *comeco, *fim;
};

Temp *root;

Node * insert(Node * &root, int val, int obj){
    Node *aux = root;
    while(aux != NULL){
        if(aux -> val == obj){
            Node *tmp = new Node;
            tmp -> val = val;
            tmp -> l = tmp -> r = NULL;
            if(aux -> r == NULL){ 
                tmp -> l = aux;
                aux -> r = tmp;
            } else {
                tmp -> r = aux -> r;
                tmp -> l = aux;
                aux -> r = tmp;
                tmp -> r -> l = tmp;
            }
            return tmp;
        }
        aux = aux -> r;
    }
}

Node * insertFinal(Node * &root, int val){
    Node *aux = root;
    while(aux -> r != NULL){
        aux = aux -> r;
    }
    Node *tmp = new Node;
    tmp -> val = val;
    tmp -> l = tmp -> r = NULL;
    if(aux -> r == NULL){ 
        tmp -> l = aux;
        aux -> r = tmp;
    }
    return tmp;
}

void erase(Node *& root, Node *aux){
    if(aux -> l == NULL and aux -> r == NULL){
        root = NULL;
    } else if(aux -> l == NULL){
        aux = aux -> r;
        aux -> l = NULL;
        free(root);
        root = aux;
    } else if(aux -> r == NULL){
        aux -> l -> r = NULL;
        free(aux);
    } else {
        aux -> l -> r = aux -> r;
        aux -> r -> l = aux -> l;
        free(aux);
    }
}

int getSumL(Node *root, int val){
    int res = 0;
    Node *aux = root;
    while(aux != NULL){
        if(aux -> val == val){
            break;
        }
        res++;
        aux = aux -> r;
    }
    // cout << "ResL: " << res << endl;
    return res;
}

int getSumR(Node *root, Node *tmp){
    Node *aux = tmp -> r;
    int res = 0;
    while(aux != NULL){
        res++;
        aux = aux -> r;
    }
    // cout << "ResR: " << res << endl;
    return res;
}

int getSumRange(Node *root, Node *tmp, int b){
    Node *aux = tmp -> r;
    int res = 0;
    int f = 0;
    // Node *aux = root;
    while(aux != NULL){
        if(aux -> val == b) break;
        res++;
        aux = aux -> r;
    }
    // cout << "Res: " << res << endl;
    return res;
}

void printVet(Node *root){
    Node *aux = root;
    while(aux != NULL){
        cout << aux -> val << " ";
        aux = aux -> r;
    } cout << endl;
}

vector<Node *> adj;
int soma[400];

int main(){
    int n, aux;
    while(scanf("%d", &n) != EOF){
        memset(soma, 0, sizeof soma);
        adj.clear();
        map<int, int> mapa;
        map<int, Node *> aponta;
        int last;
        for(int i = 0; i < n; i++){
            int x; aux = scanf("%d", &x);
            int indice = (int)(i / 150);
;            mapa[x] = indice;
            if(i % 150 == 0){
                Node *tmp = new Node;
                tmp -> val = x;
                tmp -> l = tmp -> r = NULL;
                aponta[x] = tmp;
                adj.push_back(tmp);
            } else {
                aponta[x] = insert(adj[indice], x, last);
            }
            last = x;
            soma[indice]++;
        }
        // for(int i = 0; i < adj.size(); i++){
        //     printVet(adj[i]);
        // }
        // return 0;
        int q;
        scanf("%d", &q);
        while(q--){
            char c;
            getchar();
            aux = scanf("%c", &c);
            if(c == 'Q'){
                int a, b;
                cin >> a >> b;
                if(a == b){
                    printf("0\n");
                    continue;
                }
                int idxA = mapa[a];
                int idxB = mapa[b];
                if(idxA > idxB) swap(idxA, idxB), swap(a, b);
                int r = 0;
                for(int i = idxA; i <= idxB; i++){
                    if(i == idxA and idxA == idxB){
                        r += getSumRange(adj[i], aponta[a], b);
                    } else if(i == idxA){
                        r += getSumR(adj[i], aponta[a]);
                    } else if(i == idxB){
                        r += getSumL(adj[i], b);
                    } else {
                        r += soma[i];
                    }
                }
                printf("%d\n", r);
            } else if(c == 'I'){
                int a, b;
                aux = scanf("%d %d", &a, &b);
                int idx = mapa[b];
                mapa[a] = idx;
                soma[idx]++;
                aponta[a] = insert(adj[idx], a, b);
            } else {
                int x;
                aux = scanf("%d", &x);
                int idx = mapa[x];
                erase(adj[idx], aponta[x]);
                soma[idx]--;
            }
        }
        for(int i = 0; i < adj.size(); i++){
            free(adj[i]);
        }
    }
    return 0;
}