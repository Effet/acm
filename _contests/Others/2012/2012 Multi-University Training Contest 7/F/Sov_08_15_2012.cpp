#include <iostream>
#include <cstdio>
#include <set>
using namespace std;

const int MOD = 100000007;

typedef long long ll;
typedef pair<int, int> p_pair;

int fastpow(ll a, int b, int c)
{
    ll r = 1 % c;
    while(b)
    {
        if (b & 1)
            r = r * a % c;
        b >>= 1;
        a = a * a % c;
    }
    return (int)r;
}

int main(int argc, char *argv[])
{
    int n, m, k;
    while (cin >> n >> m >> k)
    {
        
        int L;
        if (n & 1)
            L = (n + 1) / 2;
        else
            L = n / 2;

        set<p_pair> s;
        while (m--)
        {
            p_pair p;
            cin >> p.first >> p.second;
            // for (int i = 0; i < 4; ++ i)
            // {
            //     p = make_pair(p.second, n-1-p.first);
            //     if (p.first < L && p.second < L && p.first <= p.second)
            //         s.insert(p);
            // }
            // p.second = n-1-p.second;
            // for (int i = 0; i < 4; ++ i)
            // {
            //     p = make_pair(p.second, n-1-p.first);
            //     if (p.first < L && p.second < L && p.first <= p.second)
            //         s.insert(p);
            // }
            p.first = min(p.first, n-1-p.first);
            p.second = min(p.second, n-1-p.second);
            if (p.first > p.second)
                swap(p.first, p.second);
            s.insert(p);
        }

        int cnt = L * (L + 1) / 2 - s.size();
        cout << fastpow((ll)k, cnt, MOD) << endl;
    }
    return 0;
}
