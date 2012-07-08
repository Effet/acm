#include <iostream>
using namespace std;

int main(int argc, char *argv[])
{
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        for (int i = 0; i < (1<<n); ++ i) {
            int x;
            x = i ^ (i >> 1);
            if (i & 1)
                x = (1<<n) - x - 1;
            cout << x << endl;
        }
    }
    return 0;
}
