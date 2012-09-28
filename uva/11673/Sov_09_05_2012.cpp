#include <iostream>
#include <cstdio>
using namespace std;

typedef long long LL;

const int MAX_N = 1000000 + 1;
const int MAX_P = 60;

int p[MAX_N], q[MAX_N];
int PP[MAX_P];

int main(int argc, char *argv[])
{
    int t;
    scanf("%d", &t);
    for (int cas = 1; cas <= t; ++ cas)
    {
        int P;
        scanf("%d", &P);
        for (int i = 0; i < P; ++ i)
            scanf("%d", &PP[i]);
        int n, A, B, C, D, E, F, M;
        scanf("%d", &n);
        scanf("%d%d", &p[0], &q[0]);
        scanf("%d%d%d", &A, &B, &C);
        scanf("%d%d%d", &D, &E, &F);
        scanf("%d", &M);

        for (int i = 1; i <= n; ++ i)
        {
            p[i] = (A * (LL)p[i-1] + B * (LL)q[i-1] + C) % M;
            q[i] = (D * (LL)p[i-1] + E * (LL)q[i-1] + F) % M;
            if (p[i] > q[i])
                swap(p[i], q[i]);
        }
        int ans = 0;
        for (int j = 1; j <= n - P + 1; ++ j)
        {
            int k;
            for (k = 0; k < P; ++ k)
                if (p[j+k] > PP[k] || q[j+k] < PP[k])
                    break;
            if (k == P)
                ++ ans;
        }
        printf("Case %d: %d\n", cas, ans);
    }
    return 0;
}
