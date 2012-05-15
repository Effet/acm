#include <iostream>
using namespace std;

int main() {
    long long num = 600851475143;
    long long ans = -1;
    for (long long i = 2; i <= num; ++ i)
    {
        if (num % i == 0)
        {
            if (ans < i)
                ans = i;
            while (num % i == 0)
                num /= i;
        }
    }
    cout << ans << endl;
    return 0;
}
