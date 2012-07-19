#include <iostream>
#include <cstdio>
#include <cmath>
using namespace std;

#define eps 0.00000000001

int K;
double L, R, P, E, T;
double PP;

void dfs(double l, double r, int deep, double p)
{
    if (r - eps < T - E || l + eps > T + E)
        return ;

    double t = (l + r)/2;
    
    if (abs(l - r) - eps <= 0 ||
        (l + eps >= T - E && r - eps <= T + E)
        || deep == K) {
        // cout << "T,t,p " << T << " " << t << " " << p << endl;
        if (abs(t-T) - eps <= E)
        {
            // cout << p << endl;
            PP += p;
        }

        return ;
    }

    if (t + eps >= T)
    {
        dfs(l, t, deep+1, p * (1-P));
        dfs(t, r, deep+1, p * P);
    }
    else
    {
        dfs(l, t, deep+1, p * P);
        dfs(t, r, deep+1, p * (1-P));
    }
}

int main(int argc, char *argv[])
{
    while (cin >> K >> L >> R >> P >> E >> T)
    {
        // cout << "E,T " << E << " " << T << endl;
        PP = 0;
        dfs(L, R, 0, 1);
        printf("%.20lf\n", PP);
    }
    return 0;
}
