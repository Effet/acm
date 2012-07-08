#include <iostream>
using namespace std;

typedef long long ll;

ll gcd(ll a, ll b) {
    if (b == 0)
        return a;
    else
        return gcd(b,a%b);
}

int main() {
    int t;
    ll a, b;
    cin >> t;
    while (t--) {
        ll n;
        cin >> n;
        cout << 4*n/gcd(4*n,n+1) + 1 << endl;
    }
    return 0;
}
