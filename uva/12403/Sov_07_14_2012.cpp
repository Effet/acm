#include <iostream>
#include <cstdio>
using namespace std;


int main(int argc, char *argv[])
{
    int t, sum = 0;
    cin >> t;
    while (t --)
    {
        string str;
        cin >> str;
        if (str == "report")
            cout << sum << endl;
        else
        {
            int x;
            cin >> x;
            sum += x;
        }
    }
    return 0;
}
