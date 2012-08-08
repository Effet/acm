#include <iostream>
#include <algorithm>
#include <cmath>
using namespace std;

int main(int argc, char *argv[])
{
    while (true)
    {
        int a[5];
        for (int i = 0; i < 5; ++ i)
            cin >> a[i];
        
        if (a[0] == 0)
            break;

        int ans = a[3] * a[4];
        for (int i = 0; i < 5; ++ i)
            ans *= a[i];

        cout << ans << endl;
    }
    return 0;
}
