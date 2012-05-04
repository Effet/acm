#include <iostream>
#include <string>
using namespace std;

int main()
{
	int n;
	while (cin >> n)
	{
		long long len = 1, cnt = 1;
		while (n--)
		{
			string s;
			cin >> s;
			if (s == "UR" || s == "DL")
				++ len;
			else if (s == "DR" || s == "UL")
				++ cnt;
			else
				++ len, ++ cnt;
		}
		cout << len * cnt << endl;
	}
	return 0;
}
