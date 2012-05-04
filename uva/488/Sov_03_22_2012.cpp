#include <iostream>
using namespace std;

int main()
{
	int n;
	cin >> n;
	while (n--)
	{
		int a, f;
		cin >> a >> f;
		while (f--)
		{
			for (int i = 1; i < a; i ++)
			{
				for (int j = 1; j <= i; j ++)
					cout << i;
				cout << endl;
			}
			for (int i = a; i >= 1; i --)
			{
				for (int j = i; j >= 1; j --)
					cout << i;
				cout << endl;
			}
			if (n || f)
				cout << endl;
		}
	}
}
