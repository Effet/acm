#include <iostream>
#include <string>
using namespace std;

void clean(string &s)
{
	for (int i = 0; i < s.size(); i ++)
	{
		if (s.find(s[i]) != i)
		{
			s.erase(s.begin()+i);
			i --;
		}
	}
}

int main()
{
	int n;
	while (cin>>n && n!=-1)
	{
		string hang,cho;
		cin >> hang >> cho;
		clean(hang);
		clean(cho);
		int cnt = 0;
		for (int i = 0; i < cho.size(); i ++)
		{
			if (hang.size() == 0 || cnt == 7)
				break;
			int found = hang.find(cho[i]);
			if (found != -1)
				hang.erase(hang.begin()+found);
			else
				cnt ++;
		}
		cout << "Round " << n << endl;
		//cout << hang.size() << " " << cnt << endl;
		if (hang.size() == 0)
			cout << "You win." << endl;
		else if (cnt < 7)
			cout << "You chickened out." << endl;
		else
			cout << "You lose." << endl;
	}
}
