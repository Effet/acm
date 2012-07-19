#include <iostream>
using namespace std;

const int MAX_N = 100000 + 100;
int a[MAX_N];

int main(int argc, char *argv[])
{
    int n;
    while (cin >> n)
    {
        for (int i = 0; i < n; ++ i)
            cin >> a[i];
        
        long long ans = 0;
        
        for (int i = 1; i < n; ++ i) {
            if (a[i-1] > a[i]) {
                ans += (long long)(a[i-1]-a[i]);
            }
        }
        cout << ans << endl;
    }
    return 0;
}
