#include <iostream>
#include <cmath>
using namespace std;

int main()
{
	long long n;
	while (cin >> n && n != 0)
	{
		long long q = sqrt(n);
		if (q*q != n)
			cout << "no" << endl;
		else
			cout << "yes" << endl;
	}
}
