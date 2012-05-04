//'not greater than 2^32' doesn't mean not less than -2^32
#include <iostream>
using namespace std;

int main()
{
	long long a, b;
	while (cin>>a>>b)
	{
		cout << (a<b?b-a:a-b) << endl;
	}
	return 0;
}
