#include <iostream>
using namespace std;

typedef long long ll;

ll C[11][11];
ll S[11][11];
ll f[11];
ll p[11][11];

void init() {
    f[0] = 1;
    for (int i = 1; i <= 10; ++ i)
        f[i] = f[i-1] * i;

    for (int x = 1; x <= 10; ++ x) {
        for (int n = 1; n <= 10; ++ n) {
            if (n == 1)
                p[x][n] = x;
            else
                p[x][n] = p[x][n-1] * x;
        }
    }
    
    for (int n = 1; n <= 10; ++ n) {
        for (int k = 1; k <= 10; ++ k) {
            if (k > n)
                S[n][k] = 0;
            else if (k == 1 || k == n)
                S[n][k] = 1;
            else
                S[n][k] = S[n-1][k-1] + k*S[n-1][k];
        }
    }

    for (int n = 1; n <= 10; ++ n) {
        for (int k = 1; k <= 10; ++ k) {
            if (k > n)
                C[n][k] = 0;
            else if (k == 1)
                C[n][k] = n;
            else
                C[n][k] = C[n-1][k] + C[n-1][k-1];
        }
    }
}

ll gcd(ll a, ll b) {
    return b ? gcd(b, a%b) : a;
}

int main() {
    init();
    int t;
    cin >> t;
    while (t--) {
        ll n, m, k;
        cin >> n >> m >> k;
        ll a = C[n][k]*S[m][k]*f[k];
        if (a == 0)
            cout << 0 << endl;
        else {
            ll b = p[n][m];
            ll g = gcd(a, b);
            a /= g;
            b /= g;
            if (a == 1 && b == 1)
                cout << 1 << endl;
            else
                cout << a << "/" << b << endl;
        }
    }
    return 0;
}
