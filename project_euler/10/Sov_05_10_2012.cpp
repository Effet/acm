#include <iostream>
using namespace std;

#define MAX_N 1111111

int primes[MAX_N], top;
int limit = 2000000;


int main() {
    top = 1;
    primes[0] = 2;
    long long sum = 2;
    for (int i = 3; i <= limit; ++ i)
    {
        int j;
        for (j = 0; j < top; ++ j)
            if (i % primes[j] == 0)
                break;
        if (j == top)
        {
            primes[top++] = i;
            sum += i;
        }
    }
    cout << sum << endl;
    return 0;
}
