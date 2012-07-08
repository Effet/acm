#include <iostream>
#include <cstdio>
using namespace std;

int main() {
    int x, t, a, b, da, db;
    cin >> x >> t >> a >> b >> da >> db;
    bool flag = false;
    for (int i = a, t1 = 0; i >= 0; i -= da, ++ t1) {
        for (int j = b, t2 = 0; j >= 0; j -= db, ++ t2) {
            int i1, j1;
            if (t1 >= t) i1 = 0; else i1 = i;
            if (t2 >= t) j1 = 0; else j1 = j;
            if (i1 + j1 == x)
                flag = true;
        }
    }
    if (flag || x == 0)
        cout << "YES" << endl;
    else
        cout << "NO" << endl;
    return 0;
}
