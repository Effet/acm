#include <iostream>
using namespace std;

bool is_prime(int n) {
    for (int i = 2; i * i <= n; ++ i)
        if (n % i == 0)
            return false;
    return true;
}

int main() {
    int limit = 10001;
    int n = 2, cnt = 1;
    while (cnt < limit) {
        ++ n;
        if (is_prime(n) )
            ++ cnt;
    }
    cout << n << endl;
    return 0;
}
