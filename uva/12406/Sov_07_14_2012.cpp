#include <iostream>
#include <cstdio>
using namespace std;

typedef long long ll;

ll bi[19];
void init() {
    bi[0] = 1;
    for (int i = 1; i < 19; ++ i)
        bi[i] = bi[i-1] * 2;
}

int main(int argc, char *argv[])
{
    init();
    int t;
    cin >> t;
    for (int cas = 1; cas <= t; ++ cas)
    {
        int p, q;
        cin >> p >> q;
        ll minn = -1, maxx = - 1;
        for (int x = 0; x < (1<<p); ++ x) {
            ll d = 0;
            for (int i = 0; i < p; ++ i) {
                int b = (x&(1<<i))?1:0;
                d = d*10 + (b + 1);
            }
            // cout << d << endl;
            if (d % bi[q] == 0)
            {
                maxx = d;
                if (minn == -1) {
                    minn = d;
                }
            }
        }
        cout << "Case " << cas << ": ";
        if (minn == -1)
            cout << "impossible" << endl;
        else if (minn == maxx)
            cout << minn << endl;
        else
            cout << minn << " " << maxx << endl;
    }
    return 0;
}
