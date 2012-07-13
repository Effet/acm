#include <iostream>
#include <cstdio>
using namespace std;

int main(int argc, char *argv[])
{
    int n, p, q;
    int cas = 1;
    while (cin >> n >> p >> q)
    {
        printf("Case %d: %.4lf\n", cas++, double(q+1)/(p+2));
    } 

    return 0;
}
