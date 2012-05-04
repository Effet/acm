#include <iostream>
using namespace std;

int main()
{
	int t;
	cin >> t;
	for (int cas = 1; cas <= t; cas ++)
	{
		cout << "Case " << cas << ": ";
		int l, w, h;
		cin >> l >> w >> h;
		if (l<=20&&w<=20&&h<=20)
			cout << "good" << endl;
		else
			cout << "bad" << endl;
	}
}
