#include <algorithm>
#include <iostream>
#include <string>
using namespace std;

void reverse(string &a) {
    for (int i = 0, j = a.size()-1; i < j; ++ i, -- j)
        swap(a[i],a[j]);
}

string add(string a, string b) {
    reverse(a);
    reverse(b);
        
    string c = "";
    int r = 0;
    for (int i = 0; i < b.size(); ++ i)
    {
        r += a[i]+b[i]-'0'-'0';
        c += r%10 + '0';
        r /= 10;
    }
    for (int i = b.size(); i < a.size(); ++ i)
    {
        r += a[i]-'0';
        c += r%10 + '0';
        r /= 10;
    }
    if (r != 0)
        c += r+'0'; 
    reverse(c);
    
    return c;
}

int main() {
    int n = 100;
    string rst;
    for (int i = 0; i < 50; ++ i)
        rst += "0";
    for (int i = 0; i < n; ++ i)
    {
        string a;
        cin >> a;
        string b = rst;
        rst = add(b, a);
    }

    rst.erase(rst.begin()+10,rst.end());
    cout << rst << endl;

    return 0;
}
