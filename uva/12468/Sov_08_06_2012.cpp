#include <iostream>
#include <cmath>
using namespace std;

int main(int argc, char *argv[])
{
    int a, b;
    while (cin >> a >> b)
    {
        if (a == -1 && b == -1)
            break;
        int ans = abs(b - a);
        if (100 - ans < ans)
            ans = 100 - ans;
        cout << ans << endl;
    }
    return 0;
}
