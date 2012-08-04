#include <iostream>
#include <cstdio>
using namespace std;

typedef long long ll;

const int MAX_N = 100000 + 100;

int n;
ll a[MAX_N];
ll sum1[MAX_N];
ll sum2[MAX_N];

int main(int argc, char *argv[])
{
    int t;
    scanf("%d", &t);
    while (t--)
    {
        int n;
        scanf("%d", &n);
        ll sum = 0;
        for (int i = 0; i < n; ++ i)
        {
            scanf("%lld", &a[i]);
            sum += a[i];
        }

        sum1[0] = a[0];
        for (int i = 1; i < n; ++ i)
            sum1[i] = sum1[i-1] + a[i];
        sum2[n-1] = a[n-1];
        for (int i = n - 2; i >= 0; -- i)
            sum2[i] = sum2[i+1] + a[i];

        ll max_l = max(a[0], a[n-1]);
        for (int i = 1; i <= n - 2; ++ i)
        {
            max_l = max(max_l,
                        max(a[i] - sum1[i-1], a[i] - sum2[i+1]));
        }
        printf("%lld\n", sum - max_l);
    }
    return 0;
}
