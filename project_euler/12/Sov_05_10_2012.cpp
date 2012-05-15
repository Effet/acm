#include <iostream>
using namespace std;

int div(long long n) {
    long long ans = 1;
    for (long long i = 2; i <= n; ++ i)
    {
        int cnt = 0;
        if (n % i == 0)
        {
            while (n % i == 0 && n >= i)
            {
                ++ cnt;
                n /= i;
            }
        }
        ans *= (cnt + 1);
    }
    return ans - 1;
            
}

int main() {
    int limit = 500;
    // long long num = 28;
    // long long add = 8;
    long long num = 0;
    long long add = 1;

    for (;;++add)
    {
        num += add;
        long long dd = div(num);
        cout << num << " " << dd << endl;

        if (dd >= limit)
            break;
    }
    cout << num << endl;
    return 0;
}
