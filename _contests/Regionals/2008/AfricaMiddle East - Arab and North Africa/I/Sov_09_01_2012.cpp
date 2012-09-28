#include <iostream>
using namespace std;

typedef long long LL;

LL to2[63];

void init()
{
    to2[0] = 1;
    for (int i = 1; i <= 61; ++ i)
        to2[i] = to2[i-1] * 2;
}

int get_val(LL n, LL r, LL c)
{
    if (n == 0)
        return 1;
    if (r >= to2[n-1] && c >= to2[n-1])
        return - get_val(n - 1, r - to2[n-1], c - to2[n-1]);
    else
        return get_val(n - 1,
                       r >= to2[n-1] ? r - to2[n-1] : r,
                       c >= to2[n-1] ? c - to2[n-1] : c);
}

int main(int argc, char *argv[])
{
    init();
    LL n, r, s, e;
    while (cin >> n >> r >> s >> e)
    {
        if (n == -1 && r == -1 && s == -1 && e == -1)
            break;
        int ans = 0;
        for (LL i = s; i <= e; ++ i)
            ans += get_val(n, r, i);
        cout << ans << endl;
    }
    return 0;
}
