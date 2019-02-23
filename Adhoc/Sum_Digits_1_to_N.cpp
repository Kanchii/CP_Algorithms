#include <bits/stdc++.h>
using namespace std;

#define INF 0x3f3f3f3
#define PI acos(-1)
#define min(a,b) ((a) < (b) ? (a) : (b))
#define max(a,b) ((a) > (b) ? (a) : (b))

typedef long long ll;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef pair<int,int> ii;
typedef pair<ll,ll> pll;

ll sumOfDigits(ll n){
    if(n < 10){
        return (n * (n + 1)) / 2;
    }
    int d = log10(n);
    ll *a = new ll[d + 1];
    a[0] = 0; a[1] = 45;
    for(int i = 2; i <= d; i++){
        a[i] = a[i - 1] * 10 + 45 * (ll)ceil(pow(10, i - 1));
    }
    ll p = (ll)ceil(pow(10, d));
    ll msd = n / p;
    ll first = msd * a[d];
    ll second = (msd * (msd - 1) / 2) * p;
    ll third = msd * (1 + n % p);
    ll fourth = sumOfDigits(n % p);
    return first + second + third + fourth;
}


int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    
    int n = 328;
    cout << sumOfDigits(n) << endl; // saida = 3241
    
    return 0;
}