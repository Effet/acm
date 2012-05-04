#include <iostream>
using namespace std;

int main()
{
	string s;
	while (cin >> s)
	{
		if (s.size() == 1 && s[0] == '0')
			break;
		int ans = 0;
		for (int i = s.size()-1, j = 1; i >= 0; i --, j ++)
			ans += (s[i]-'0')*( (1<<j)-1);
		cout << ans << endl;
	}
}
