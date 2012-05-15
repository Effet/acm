#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

int matrix[20][20];

int n = 20;
bool ok(int x, int y) {
    return (x>=0&&x<n && y>=0&&y<n);
}

int main() {
    for (int i = 0; i < n; ++ i)
        for (int j = 0; j < n; ++ j)
            cin >> matrix[i][j];
    
    int ans = -1;
    for (int i = 0; i < n; ++ i)
        for (int j = 0; j < n; ++ j)
        {
            if (ok(i+3,j))
            {
                int cur = 1;
                for (int k = 0; k < 4; ++ k)
                    cur *= matrix[i+k][j];
                ans = max(ans, cur);
            }
            if (ok(i,j+3))
            {
                int cur = 1;
                for (int k = 0; k < 4; ++ k)
                    cur *= matrix[i][j+k];
                ans = max(ans, cur);
            }
            if (ok(i+3,j+3))
            {
                int cur = 1;
                for (int k = 0; k < 4; ++ k)
                    cur *= matrix[i+k][j+k];
                ans = max(ans, cur);
            }
            if (ok(i-3,j+3))
            {
                int cur = 1;
                for (int k = 0; k < 4; ++ k)
                    cur *= matrix[i-k][j+k];
                ans = max(ans, cur);
            }
        }
    
    cout << ans << endl;
            
    return 0;
}
