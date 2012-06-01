#include <iostream>
#include <cmath>
using namespace std;

typedef long long ll;

int main() {
    ll n;
    while (cin >> n) {
        ll x = (ll)sqrt(n*2.0);
        bool ok = false;
        for (ll i = 1; i <= x; ++ i) {
            ll y = 2*n - i*(i+1);
            ll z = (ll)sqrt(y);
            if (z > 0 && z*(z+1) == y)
            {
                ok = true;
                break;
            }
        }
        if (ok)
            cout << "YES" << endl;
        else
            cout << "NO" << endl;
    }
    return 0;
}
