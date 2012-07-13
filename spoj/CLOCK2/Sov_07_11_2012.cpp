#include <iostream>
#include <string>
#include <map>
using namespace std;

map<string,int> m;

void init() {
    m["I"] = 1;
    m["II"] = 2;
    m["III"] = 3;
    m["IV"] = 4;
    m["V"] = 5;
    m["VI"] = 6;
    m["VII"] = 7;
    m["VIII"] = 8;
    m["IX"] = 9;
    m["X"] = 10;
    m["XI"] = 11;
    m["XII"] = 12;
}

int main(int argc, char *argv[])
{
    init();
    int cas = 1;
    string a;
    while (cin >> a) {
        cout << "Case " << cas ++ << ": "<< m[a] << endl;
    }
    return 0;
}
