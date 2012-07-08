#include <iostream>
#include <string>
#include <vector>
using namespace std;

#define pow2(x) ((x)*(x))

int x[4], y[4];

bool is_parl() {
    if ((y[1]-y[0])*(x[3]-x[2]) == (y[3]-y[2])*(x[1]-x[0]) &&
        (y[3]-y[0])*(x[2]-x[1]) == (y[2]-y[1])*(x[3]-x[0])
        )
        return true;
    return false;
}

bool is_rect() {
    if (is_parl() &&
        (y[1]-y[0])*(y[2]-y[1]) + (x[1]-x[0])*(x[2]-x[1]) == 0)
        return true;
    return false;
}

bool is_diam() {
    if (is_parl() &&
        pow2(y[1]-y[0])+pow2(x[1]-x[0]) == pow2(y[2]-y[1])+pow2(x[2]-x[1]))
        return true;
    return false;
}

bool is_sqre() {
    if (is_rect() && is_diam())
        return true;
    return false;
}

int main() {
    int t;
    cin >> t;
    for (int cas = 1; cas <= t; ++ cas) {
        cout << "Case #" << cas << ": ";
        for (int i = 0; i < 4; ++ i)
            cin >> x[i] >> y[i];
        if (is_sqre())
            cout << "Square" << endl;
        else if (is_diam())
            cout << "Diamond" << endl;
        else if (is_rect())
            cout << "Rectangle" << endl;
        else if (is_parl())
            cout << "Parallelogram" << endl;
        else
            cout << "Others" << endl;
    }
    return 0;
}
