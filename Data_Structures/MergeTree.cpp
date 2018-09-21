#include <bits/stdc++.h>

using namespace std;

vector<int> mergeTree[1234];

void createMergeTree(vector<int> &vet, int l, int r, int pos){
    if(l == r){
        // cout << l << " " << r << ": " << vet[l] << endl;
        mergeTree[pos] = vector<int>(1, vet[l]);
    } else {
        int mid = (l + r) / 2;
        createMergeTree(vet, l, mid, 2 * pos + 1);
        createMergeTree(vet, mid + 1, r, 2 * pos + 2);
        merge(mergeTree[2 * pos + 1].begin(), mergeTree[2 * pos + 1].end(),
              mergeTree[2 * pos + 2].begin(), mergeTree[2 * pos + 2].end(),
              back_inserter(mergeTree[pos]));
        // cout << l << " " << r << ": ";
        // for(int v : mergeTree[pos]) cout << v << " ";
        // cout << endl;
    }
}

int query(int l, int r, int ql, int qr, int pos, int kth){
    if(l > qr or r < ql) return 1e9;
    if(l == r) return mergeTree[pos][0];
    int mid = (l + r) / 2;
    if(mid < ql){
        return query(mid + 1, r, ql, qr, 2 * pos + 2, kth);
    }
    int left = mid - ql + 1;
    if(left >= kth){
        return query(l, mid, ql, qr, 2 * pos + 1, kth);
    } else {
        return query(mid + 1, r, mid + 1, qr, 2 * pos + 2, kth - left);
    }
}

int main(int argc, char const *argv[]) {

    int n = 10;
    int arr[] = {0, 2, 10, -5, 3, 1, 5, 0, 8, -3};
    vector<int> vet(arr, arr + n);
    createMergeTree(vet, 0, n - 1, 0);

    int kth = 3;
    int q = query(0, n - 1, 1, 6, 0, kth);
    cout << q << endl; // Saida: 2


    return 0;
}
