#include <iostream>
using namespace std;

int main()
{
	int aa, l;
	int cas = 0;
	while (cin>>aa>>l && aa!=-1 && l!=-1)
	{
		long long a = aa;
		int cnt = 1;
		while (a != 1)
		{
			if (a%2 == 0)
				a /= 2;
			else
			{
				a = a*3 + 1;
				if (a > l)
					break;
			}
			cnt ++;
		}
		cas ++;
		cout << "Case " << cas << ": "
			<< "A = " << aa << ", limit = " << l
			<< ", number of terms = " << cnt << endl;
	}
}
