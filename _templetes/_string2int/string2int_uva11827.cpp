#include <iostream>
#include <sstream>
#include <string>
#include <algorithm>
using namespace std;

int gcd(int a, int b) {
	return b?gcd(b,a%b):a;
}

int main()
{
	string s;
	getline(cin, s);
	stringstream ss(s);
	int t;
	int a[111];
	ss >> t;
	while (t --)
	{
		string str;
		getline(cin, str);
		stringstream sin(str);
		int n = 0;
		while ( sin >> a[n] ) n ++;

		//for (int i = 0; i < n; i ++)
			//cout << a[i] << " ";
		//cout << endl;

		int ans = 1;
		for (int i = 0; i < n; i ++)
			for (int j = i + 1; j < n; j ++)
				ans = max(ans, gcd(a[i],a[j]));

		cout << ans << endl;
	}
}
