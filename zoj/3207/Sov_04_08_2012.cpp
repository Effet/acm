#include <iostream>
#include <string>
#include <set>
using namespace std;

int main()
{
	int n;
	string str;
	set<string> s;

	s.clear();
	cin >> n;
	while (n --)
	{
		cin >> str;
		s.insert(str);
	}

	int k;
	cin >> k;
	while (k --)
	{
		cin >> n;
		int cnt = 0;
		while (n --)
		{
			cin >> str;
			if (s.find(str) != s.end())
				cnt ++;
		}

		cout << cnt << endl;
	}
}
