#include <iostream>
#include <cstring>
using namespace std;

int main(int argc, char *argv[])
{
    char str[300];
    cin >> str;
    int len = strlen(str);
    bool flag = false;
    for (int i = 0; i < len; ++ i)
    {
        if (i + 2 < len)
        {
            if (str[i] == 'W' && str[i+1] == 'U' && str[i+2] == 'B')
            {
                i += 2;
                if (flag)
                    cout << " ";
                flag = false;
            }
            else
            {
                flag = true;
                cout << str[i];
            }
        }
        else
        {
            flag = true;
            cout << str[i];
        }
    }
    cout << endl;
    return 0;
}
