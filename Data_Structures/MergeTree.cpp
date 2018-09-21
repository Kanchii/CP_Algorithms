#include <bits/stdc++.h>

using namespace std;

vector<int> mergeTree[1234];

void createMergeTree(vector<int> &vet, int l, int r, int pos){
    if(l == r){
        cout << l << " " << r << ": " << vet[l] << endl;
        mergeTree[pos] = vector<int>(1, vet[l]);
    } else {
        int mid = (l + r) / 2;
        createMergeTree(vet, l, mid, 2 * pos + 1);
        createMergeTree(vet, mid + 1, r, 2 * pos + 2);
        merge(mergeTree[2 * pos + 1].begin(), mergeTree[2 * pos + 1].end(),
              mergeTree[2 * pos + 2].begin(), mergeTree[2 * pos + 2].end(),
              back_inserter(mergeTree[pos]));
        cout << l << " " << r << ": ";
        for(int v : mergeTree[pos]) cout << v << " ";
        cout << endl;
    }
}

int main(int argc, char const *argv[]) {

    int n = 10;
    int arr[] = {0, 2, 10, -5, 3, 1, 5, 6, 8, -3};

    // -5 1 2 3 5 10
    vector<int> vet(arr, arr + n);
    createMergeTree(vet, 0, n - 1, 0);
    


    return 0;
}
