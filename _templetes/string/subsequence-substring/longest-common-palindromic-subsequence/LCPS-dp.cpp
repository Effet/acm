#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>
using namespace std;

const int MAX_N = 100;

char x[MAX_N];
char y[MAX_N];
int lcps[MAX_N][MAX_N][MAX_N][MAX_N];

int LCPSLength(char *x, char *y)
{
    int n = strlen(x + 1);
    int m = strlen(y + 1);

    // cout << endl << n <<  " " << m << endl;

    // memset(lcps, 0, sizeof(lcps));
    for (int i = 1; i <= n; ++ i)
        for (int j = i; j <= n; ++ j)
            for (int k = 1; k <= m; ++ k)
                for (int l = k; l <= m; ++ l)
                    if ( (i == j || k == l) &&
                         (x[i] == y[k] || x[i] == y[l] ||
                          x[j] == y[k] || x[j] == y[l])
                        )
                        lcps[i][j][k][l] = 1;
                    else
                        lcps[i][j][k][l] = 0;

    for (int xLength = 2; xLength <= n; ++ xLength)
        for (int yLength = 2; yLength <= m; ++ yLength)
            for (int i = 1; i <= n - xLength + 1; ++ i)
                for (int k = 1; k <= m - yLength + 1; ++ k)
                {
                    int j = i + xLength - 1;
                    int l = k + yLength - 1;
                    if (x[i] == x[j] && x[j] == y[k] && y[k] == y[l])
                        lcps[i][j][k][l] = 2 + lcps[i + 1][j - 1][k + 1][l - 1];
                    else
                        lcps[i][j][k][l] = max(lcps[i + 1][j][k][l],
                                               max(lcps[i][j - 1][k][l],
                                                   max(lcps[i][j][k + 1][l],
                                                       lcps[i][j][k][l - 1])));
                }

    // for (int i = 1; i <= n; ++ i) {
    //     for (int j = 1; j <= n; ++ j) {
    //         for (int k = 1; k <= m; ++ k) {
    //             for (int l = 1; l <= m; ++ l) {
    //                 cout << i << " "<< j << " " << k << " " << l << " " << lcps[i][j][k][l] << endl;
    //             }
    //         }
    //     }
    // }

    return lcps[1][n][1][m];
}

int main(int argc, char *argv[])
{
    int t;
    cin >> t;
    for (int cas = 1; cas <= t; ++ cas)
    {
        cin >> x + 1 >> y + 1;
        cout << "Case " << cas << ": ";
        cout << LCPSLength(x, y) << endl;
    }
    return 0;
}
