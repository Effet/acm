#include <iostream>
#include <vector>
#include <cmath>
using namespace std;


typedef long long ll;
typedef pair<ll,ll> mod_p;

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

mod_p Chinese_Remainer_Non_Coprime(vector<mod_p> C)
{
    int k = C.size();
    if (k <= 0)
        return make_pair(-1, -1);
    for (int i = k - 2; i >= 0; -- i)
    {
        ll a1 = C[i].first,   n1 = C[i].second;
        ll a2 = C[i+1].first, n2 = C[i+1].second;

        ll c = a2 - a1, p1, p2;
        ll d = ex_gcd(n1, n2, p1, p2);

        if (c % d != 0)
            return make_pair(-1, -1);

        ll t = n2 / d;
        p1 = (c / d * p1 % t + t) % t;
        ll a0 = a1 + n1 * p1;
        ll n0 = n1/d * n2;
        a0 = (a0 % n0 + n0) % n0;

        C[i] = make_pair(a0, n0);
    }
    return C[0];
}


int main(int argc, char *argv[])
{
    int t;
    cin >> t;
    while (t--)
    {
        ll n;
        int m;
        cin >> n >> m;
        vector<mod_p> C(m);

        for (int i = 0; i < m; ++ i)
            cin >> C[i].second;
        for (int i = 0; i < m; ++ i)
            cin >> C[i].first;

        mod_p r = Chinese_Remainer_Non_Coprime(C);
        
        ll ans = 0;
        if (r.second != -1)
        {
            ll a0 = r.first, n0 = r.second;
            if (n >= a0)
            {
                if (a0 == 0)
                    ans = n / n0; // trick
                else
                    ans = (n - a0) / n0 + 1;
            }
        }
        cout << ans << endl;
    }
    return 0;
}
