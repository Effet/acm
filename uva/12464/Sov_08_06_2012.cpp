#include <iostream>
#include <vector>
#include <set>
using namespace std;

typedef long long ll;

ll gcd(ll a, ll b) {
    return b ? gcd(b, a % b) : a;
}

int main(int argc, char *argv[])
{
    ll alpha, beta, n;
    while (cin >> alpha >> beta >> n)
    {
        if (alpha == 0 && beta == 0 && n == 0)
            break;

        n %= 5;
        
        if (n == 0)
            cout << alpha << endl;
        else if (n == 1)
            cout << beta << endl;
        else
        {
            ll a1 = alpha, b1 = 1;
            ll a2 = beta,  b2 = 1;
            for (int i = 2; i <= n; ++ i)
            {
                ll a0 = b1 * b2 + a2 * b1;
                ll b0 = a1 * b2;
                ll d = gcd(a0, b0);
                a0 /= d;
                b0 /= d;

                // if (alpha == 7 && beta == 4 && n == 4)
                //     cout << "aaa  : " << a0 << " " << b0 << endl;

                a1 = a2; b1 = b2;
                a2 = a0; b2 = b0;
            }
            cout << a2 / b2 << endl;
        }
    }
    return 0;
}
