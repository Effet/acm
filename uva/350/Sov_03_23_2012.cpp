#include <map>
#include <iostream>
using namespace std;

int main()
{
	map<int,int> m;
	map<int,int>::iterator it;

	int Z, I, M, L;
	int cas = 0;
	while (cin>>Z>>I>>M>>L&&Z&&I&&M&&L)
	{
		int len = 0, ans;
		m.clear();
		m.insert( pair<int,int>(L,len) );
		while (true)
		{
			len ++;
			L = (Z*L+I)%M;
			
			it = m.find(L);
			if (it != m.end())
			{
				ans = len - it->second;
				break;
			}
			m.insert( pair<int,int>(L,len) );
		}
		cas ++;
		cout << "Case " << cas << ": "
			<< ans << endl;
	}
}
