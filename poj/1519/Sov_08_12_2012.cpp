#include <iostream>
#include <string>
using namespace std;

int main(int argc, char *argv[])
{
    string n;
    while (cin >> n)
    {
        if (n == "0")
            break;
        int x = 0;
        for (int i = 0; i < n.size(); ++ i)
            x += n[i] - '0';
        
        cout << 1 + ((x-1) % 9) << endl;
    }
    return 0;
}
