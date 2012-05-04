#include <iostream>
using namespace std;

int main()
{
	int t;
	cin >> t;
	while (t --)
	{
		int n;
		int a[111], b[111];
		cin >> n;
		for (int i = 0; i < n; i ++)
			cin >> a[i];
		for (int i = 0; i < n; i ++)
			cin >> b[i];

		bool flag1 = true, flag2 = true;
		for (int i = 0; i < n; i ++)
		{
			if (a[i] != b[i])
				flag1 = false;
			if (a[i] != b[n-1-i])
				flag2 = false;
		}
		if (flag1 && flag2)
			cout << "both" << endl;
		else if (flag1)
			cout << "queue" << endl;
		else if (flag2)
			cout << "stack" << endl;
		else
			cout << "neither" << endl;

	}
}
