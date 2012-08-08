#include <iostream>
using namespace std;

typedef long long ll;

const ll MOD = 1000000009;

ll ee[3][3] = {
    {0, 0, 1},
    {1, 0, 1},
    {0, 1, 1}
};

class Matrix
{
public:
    ll x[3][3];

    Matrix operator* (const Matrix& a) const {
        Matrix r;
        for (int i = 0; i < 3; ++ i)
            for (int j = 0; j < 3; ++ j)
            {
                r.x[i][j] = 0;
                for (int k = 0; k < 3; ++ k)
                    r.x[i][j] = (r.x[i][j] + x[i][k]*a.x[k][j]) % MOD;
            }
        return r;
    }

    Matrix operator% (const ll& m) const {
        Matrix r;
        for (int i = 0; i < 3; ++ i)
            for (int j = 0; j < 3; ++ j)
                r.x[i][j] = x[i][j] % m;
        return r;
    }
} e;


Matrix bi(Matrix a, ll b)
{
    Matrix r = e;
    while (b)
    {
        if (b % 2 == 1)
            r = r * a % MOD;
        b /= 2;
        a = a * a % MOD;
    }
    return r;
}

int main(int argc, char *argv[])
{
    for (int i = 0; i < 3; ++ i)
        for (int j = 0; j < 3; ++ j)
            e.x[i][j] = ee[i][j];

    // Matrix xx = e * e;
    // for (int i = 0; i < 3; ++ i)
    // {
    //     for (int j = 0; j < 3; ++ j)
    //         cout << xx.x[i][j] << " " ;
    //     cout << endl;
    // }
    
    ll n;
    while (cin >> n)
    {
        if (n == 0)
            break;

        // cout << n << " : ";

        if (n == 1)
            cout << 0 << endl;
        else if (n == 2)
            cout << 1 << endl;
        else if (n == 3)
            cout << 2 << endl;
        else
        {
            Matrix m = bi(e, n - 4);
            // if (n == 10)
            // {
            //     for (int i = 0; i < 3; ++ i)
            //     {
            //         for (int j = 0; j < 3; ++ j)
            //             cout << m.x[i][j] << " " ;
            //         cout << endl;
            //     }
            // }
            ll ans = (m.x[1][2] + 2 * m.x[2][2]) % MOD;
            cout << ans << endl;
        }
    }
    return 0;
}
