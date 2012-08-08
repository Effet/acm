#include <iostream>
#include <cmath>
using namespace std;

typedef long long ll;

const int MAX_N = 100 + 10;

ll ex_gcd(ll a, ll b, ll& x, ll& y)
{
   ll d;
   if (b == 0) {
       x = 1; y = 0;
       return a;
   }
   d  = ex_gcd(b, a%b, y, x);
   y -= a/b * x;
   return d;
}

ll Chinese_Remainder(ll* a, ll* n, ll k) {
    ll N = 1, r = 0;
    for (int i = 0; i < k; ++ i)
        N *= n[i];
    for (int i = 0; i < k; ++ i)
    {
        ll m = N / n[i], x, y;
        ex_gcd(m, n[i], x, y);
        x = (x % n[i] + n[i]) % n[i];
        r = (r + a[i]*m*x) % N;
    }
    return r;
}

int k;
ll a[MAX_N], n[MAX_N];

int main() {
    while (cin >> k)
    {
        for (int i = 0; i < k; ++ i)
            cin >> n[i] >> a[i];
        cout << Chinese_Remainder(a, n, k) << endl;
    }
    return 0;
}
