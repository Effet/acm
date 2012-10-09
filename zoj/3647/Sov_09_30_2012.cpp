#include <iostream>
#include <cstring>
using namespace std;

typedef long long LL;

const int MAX_N = 1e3 + 10;

LL C[MAX_N * MAX_N];
LL f[MAX_N][MAX_N];

int gcd(int a, int b) {
    return !b ? a : gcd(b, a % b);
}

void init() {

    // cout << gcd(2, 3) << endl;
    // cout << gcd(3, 2) << endl;
    
    memset(C, 0, sizeof(C));
    for (LL i = 3; i < MAX_N * MAX_N; ++ i)
        C[i] = i * (i - 1) * (i - 2) / 6;

    memset(f, 0, sizeof(f));
    for (int i = 2; i < MAX_N; ++ i)
        f[0][i] = f[i][0] = i - 1;
    
    for (int i = 2; i < MAX_N; ++ i) {
        for (int j = 2; j < MAX_N; ++ j) {
            f[i][j] = (LL)(gcd(i, j) - 1) * 2;
        }
    }
    
    // cout << "0:" << endl;
    // for (int i = 0; i <= 3; ++ i) {
    //     for (int j = 0; j <= 3; ++ j)
    //         cout << f[i][j] << " ";
    //     cout << endl;
    // }


    for (int i = 1; i < MAX_N; ++ i)
        f[i][0] = f[0][i] = f[i][0] + f[i-1][0];
    for (int i = 1; i < MAX_N; ++ i) {
        for (int j = 1; j < MAX_N; ++ j) {
            f[i][j] += f[i-1][j] + f[i][j-1] - f[i-1][j-1];
        }
    }

    
    for (int i = 1; i < MAX_N; ++ i)
        f[i][0] = f[0][i] = f[i][0] + f[i-1][0];
    for (int i = 1; i < MAX_N; ++ i) {
        for (int j = 1; j < MAX_N; ++ j) {
            f[i][j] += f[i-1][j] + f[i][j-1] - f[i-1][j-1];
        }
    }
}

int main(int argc, char *argv[])
{
    init();
    int n, m;
    while (cin >> n >> m) {
        cout << C[(n+1) * (m+1)] - f[n][m] << endl;
    }
    return 0;
}
