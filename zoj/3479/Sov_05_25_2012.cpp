#include <iostream>
#include <string>
using namespace std;

string zodiacs[12] = {
    "Rat",
    "Ox",
    "Tiger",
    "Rabbit",
    "Dragon",
    "Snake",
    "Horse",
    "Ram",
    "Monkey",
    "Rooster",
    "Dog",
    "Pig"
};

int main() {
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        for (int i = 0; i < 12; ++ i) {
            if ( zodiacs[(n+i)%12] == zodiacs[4] )
            {
                cout << zodiacs[i] << endl;
                break;
            }
        }
    }
    return 0;
}
