#include <iostream>
#include <algorithm>
using namespace std;

int main() {
    int t;
    cin >> t;
    for (int cas = 1; cas <= t; ++ cas) {
        int a[3];
        for (int i = 0; i < 3; ++ i)
            cin >> a[i];
        sort(a, a+3);
        cout << "Case #" << cas << ":" << endl;
        do {
            cout << a[0] << " " << a[1] << " " << a[2] << endl;
        } while (next_permutation(a, a+3));
    }
    return 0;
}
