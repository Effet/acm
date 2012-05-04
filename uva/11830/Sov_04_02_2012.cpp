#include <iostream>
#include <string>
using namespace std;

int main()
{
	int d;
	string s;
	while (cin >> d >> s)
	{
		if (d == 0 && s.size() == 1 && s[0] == '0')
			break;
		int found = s.find(d+'0');
		while (found != -1)
		{
			s.erase(s.begin()+found);
			found = s.find(d+'0');
		}
		while (s[0] == '0')
			s.erase(s.begin());
		if (s.size() == 0)
			s = "0";
		cout << s << endl;
	}
}
