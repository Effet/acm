#include <iostream>
#include <string>
using namespace std;

int main()
{
	int t;
	cin >> t;
	while (t--)
	{
		string str;
		cin >> str;
		if (str.find("D") == -1)
			cout << "Possible" << endl;
		else
			cout << "You shall not pass!" << endl;
	}
	return 0;
}
