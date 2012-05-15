#include <iostream>
#include <cstdio>
using namespace std;

#define MAX_N 2000000

int n;
int a[MAX_N];
int b[MAX_N];

int ma[MAX_N];
int ra[MAX_N];

int main() {
    while (scanf("%d", &n) != EOF) {
        for (int i = 0; i < n; ++ i)
        {
            scanf("%d", &a[i]);
            ma[a[i]] = i;
        }
        for (int i = 0; i < n; ++ i)
        {
            scanf("%d", &b[i]);
            ra[ ma[b[i]] ] = i;
        }

        // for (int i = 0; i < n; ++ i)
        //     cout << ra[i] << " ";
        // cout << endl;
        int j;
        int big = -1;
        for (j = 0; j < n; ++ j)
        {
            if (ra[j] < big)
                break;
            else
            {
                big = ra[j];
            }
        }
        cout << n - j << endl;
                
    }
    return 0;
}
