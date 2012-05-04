#include <cctype>
#include <iostream>
#include <string>
using namespace std;

int main()
{
	string str;
	while (getline(cin,str))
	{
		int c = 0;
		for (unsigned int i = 0; i < str.size(); i ++)
		{
			if (isdigit(str[i]))
				c += str[i] - '0';
			else
			{
				if (str[i] == '!')
				cout << endl;
				else
				{
					for (int j = 0; j < c; j ++)
						cout << (str[i]=='b'?' ':str[i]);
				}
				c = 0;
			}
		}
		cout << endl;
	}
}
