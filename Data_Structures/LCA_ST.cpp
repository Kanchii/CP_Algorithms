#include <bits/stdc++.h>

using namespace std;

vector<int> tour, height;
int vis[20];
int entrada[20];

void preTour(vector<vector<int> > &adj, int u, int nivel){
    vis[u] = 1;
    tour.push_back(u);
    entrada[u] = tour.size() - 1;
    height.push_back(nivel);
    for(int v : adj[u]){
        if(!vis[v]){
            preTour(adj, v, nivel + 1);
            tour.push_back(u);
            height.push_back(nivel);
        }
    }
}

int st[20][10];

void preST(vector<vector<int> > &adj){
    for(int i = 0; i < tour.size(); i++){
        st[i][0] = entrada[tour[i]];
    }
    for(int j = 1; j <= 8; j++){
        for(int i = 0; i + (1 << j) <= tour.size(); i++){
            int u = height[st[i][j - 1]];
            int v = height[st[i + (1 << (j - 1))][j - 1]];
            if(u < v){
                st[i][j] = st[i][j - 1];
            } else {
                st[i][j] = st[i + (1 << (j - 1))][j - 1];
            }
        }
    }
}

int query(int l, int r){
    if(l > r){
        swap(l, r);
    }
    int diff = r - l + 1;
    int first = 0;
    int res;
    for(int j = 8; j >= 0; j--){
        if(diff & (1 << j)){
            if(!first){
                first = 1;
                res = st[l][j];
                l += (1 << j);
            } else {
                int u = st[l][j];
                if(height[u] < height[res]){
                    res = u;
                }
                l += (1 << j);
            }
        }
    }
    return tour[res];
}

int main(int argc, char const *argv[]) {

    vector<vector<int> > adj(8);
    adj[1].push_back(2);
    adj[2].push_back(1);
    adj[1].push_back(3);
    adj[3].push_back(1);
    adj[1].push_back(4);
    adj[4].push_back(1);
    adj[2].push_back(5);
    adj[5].push_back(2);
    adj[2].push_back(6);
    adj[6].push_back(2);
    adj[4].push_back(7);
    adj[7].push_back(4);
    preTour(adj, 1, 1);
    preST(adj);

    cout << query(entrada[5], entrada[6]) << endl; // Saida = 2
    cout << query(entrada[2], entrada[3]) << endl; // Saida = 1
    cout << query(entrada[3], entrada[3]) << endl; // Saida = 3
    cout << query(entrada[4], entrada[7]) << endl; // Saida = 4
    cout << query(entrada[7], entrada[1]) << endl; // Saida = 1

    return 0;
}
