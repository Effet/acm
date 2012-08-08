#include <iostream>
#include <cmath>
using namespace std;

typedef long long ll;

int main(int argc, char *argv[])
{
    ll a, b;
    while (cin >> a >> b)
    {
        if (a == 0 && b == 0)
            break;

        ll x = abs(b - a), n = x;
        ll ans = 1;
        for (int i = 2; i * i <= n; ++ i)
        {
            if (x % i == 0)
            {
                ll cnt = 0;
                while (x % i == 0)
                {
                    x /= i;
                    ++ cnt;
                }
                ans *= (cnt + 1);
            }
        }
        if (x != 1)
            ans *= 2;
        cout << ans << endl;
    }
    return 0;
}
