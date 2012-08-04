#include <iostream>
#include <cstring>
using namespace std;

typedef long long ll;

const int MAX_N = 14;

ll t[100];
ll tt[100];
ll ttt[100];

int len(ll x)
{
    int cnt = 0;
    while (x)
    {
        ++ cnt;
        x /= 10;
    }
    return cnt;
}

void init()
{
    t[0] = tt[0] = 1;
    for (int i = 1; i < MAX_N; ++ i)
    {
        t[i] = t[i-1] * 2;
        tt[i] = tt[i-1] * 5;
    }

    memset(ttt, 0, sizeof(ttt));
    for (int i = 0; i < MAX_N; ++ i)
        for (int j = 0; j < MAX_N; ++ j)
        {
            int llen = len(t[i]*tt[j]);
            if (i <= llen && j <= llen)
                ttt[llen] ++;
        }

    for (int i = 1; i < MAX_N; ++ i)
        ttt[i] += ttt[i-1];

    // for (int i = 0; i < MAX_N; ++ i)
    //     cout << i << " " << ttt[i] << endl;
    // cout << endl;
}

ll cal(ll x)
{
    if (x == 0)
        return 0;
    
    int llen = len(x);

    ll cnt = 0;
    for (int i = 0; i <= llen; ++ i)
        for (int j = 0; j <= llen; ++ j)
        {
            // // cout << t[i]*tt[j] << " " << x << endl;
            // cout << "i, j : " << i << " " << j << endl;
            // cout << len(t[i]*tt[j]) << " " << t[i]*tt[j] << endl;
            if (len(t[i]*tt[j]) == llen && t[i] * tt[j] <= x)
                ++ cnt;
        }

    return ttt[llen-1] + cnt;
}

int main()
{
    init();

    ll n, m;
    while (cin >> m >> n) {
        ll x1 = cal(m-1);
        ll x2 = cal(n);
        cout << x2 - x1 << endl;
    }
    return 0;
}
