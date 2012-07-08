#include <iostream>
using namespace std;

int main() {
    int n, k;
    while (cin >> n >> k) {
        int b = k / n;
        int r = k % n;
        if (b != 2) {
            cout << 0 << endl;
        } else {
            cout << n - r << endl;
        }
    }
    return 0;
}
