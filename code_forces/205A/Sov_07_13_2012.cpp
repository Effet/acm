#include <iostream>
#include <cstdio>
using namespace std;

const int MAX_N = 100000 + 100;

int a[MAX_N];

int main(int argc, char *argv[])
{
    int n;
    while (cin >> n)
    {
        for (int i = 1; i <= n; ++ i)
            cin >> a[i];

        
        int min_x = a[1], id = 1;
        for (int i = 2; i <= n; ++ i) {
            if (min_x > a[i]) {
                min_x = a[i];
                id = i;
            }
        }

        // cout << min_x << endl;
        int cnt = 0;
        for (int i = 1; i <= n; ++ i)
            if (a[i] == min_x)
                ++ cnt;
        
        if (cnt == 1)
            cout << id << endl;
        else
            cout << "Still Rozdil" << endl;
    } 

    return 0;
}
