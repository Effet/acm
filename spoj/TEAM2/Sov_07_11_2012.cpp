#include <iostream>
#include <algorithm>
using namespace std;

int main(int argc, char *argv[])
{
    int a[4];
    int cas = 1;
    while (cin >> a[0] >> a[1] >> a[2] >> a[3]) {
        cout << "Case " << cas ++ << ": ";
        sort(a, a+4);
        cout << a[3] + a[2] << endl;;
    }
    return 0;
}
