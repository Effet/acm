#include <iostream>
#include <cstdio>
using namespace std;

int main(int argc, char *argv[])
{
    int t;
    cin >> t;
    for (int cas = 1; cas <= t; ++ cas)
    {
        int n;
        char str[500];
        int ans = 0;
        cin >> n >> str;
        for (int i = 1; i <= n; ++ i)
        {
            if (str[i-1] == '.')
            {
                ++ ans;
                str[i-1] = '#';
                str[i] = '#';
                str[i+1] = '#';
            }
        }
        cout << "Case " << cas << ": ";
        cout << ans << endl;
    }
    return 0;
}
