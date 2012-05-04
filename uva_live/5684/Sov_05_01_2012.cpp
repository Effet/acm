#include <iostream>
#include <cstdio>
#include <string>
#include <cstring>
#include <sstream>
#include <vector>
using namespace std;

int main()
{
	string st;
	getline(cin, st);
	stringstream sst(st);
	int tt;
	sst >> tt;
	int cls = 0;
	while (tt--)
	{
		cls ++ ;

		string s;
		getline(cin, s);
		stringstream ss(s);
		int t;
		ss >> t;
		int present = 0;
		int at_home = 0;
		int Need_remedial = 0;
		int abset = 0;
		for (int i = 0; i < t; ++ i)
		{
			string str;
			getline(cin, str);
			stringstream sin(str);

			vector<string> vv;
			string tmp;
			while ( sin >> tmp ) {
				vv.push_back(tmp);
			}

			if (vv.size() == 1)
			{
				++ abset;
			}
			else {
				if (vv[1] == "y" || vv[1] == "yes")
					++ present;
				else {
					int j = 1;
					for (; j < vv.size(); ++ j)
					{
						if (tmp == "y" || tmp == "yes")
							break;
					}
					if (j == vv.size())
						++ Need_remedial;
					else
						++ at_home;
				}
			}
		}
		printf("Roll-call: %d\n", cls);
		printf("Present: %d out of %d\n", present, t);
		printf("Needs to study at home: %d out of %d\n", at_home, t);
		printf("Needs remedial work after school: %d out of %d\n", Need_remedial, t);
		printf("Absent: %d out of 5\n", abset, t);

	}
	return 0;
}
