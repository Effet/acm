#include <iostream>
using namespace std;

int main() {
    long long ans = 0;
    long long a1 = 0, a2 = 0;
    for (int i = 1; i <= 100; ++ i)
    {
        a1 += i*i;
        a2 += i;
    }
    a2 *= a2;
    cout << a2 - a1 << endl;
    return 0;
}
