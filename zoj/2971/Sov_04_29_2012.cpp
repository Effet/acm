#include <iostream>
#include <sstream>
#include <string>
#include <algorithm>
#include <cstdio>
#include <vector>
#include <map>
using namespace std;

vector<string> vs;

map<string, int> mp;
void init()
{
	mp["zero"] = 0;
	mp["one"] = 1;
	mp["two"] = 2;
	mp["three"] = 3;
	mp["four"] = 4;
	mp["five"] = 5;
	mp["six"] = 6;
	mp["seven"] = 7;
	mp["eight"] = 8;
	mp["nine"] = 9;
	mp["ten"] = 10;
	mp["eleven"] = 11;
	mp["twelve"] = 12;
	mp["thirteen"] = 13;
	mp["fourteen"] = 14;
	mp["fifteen"] = 15;
	mp["sixteen"] = 16;
	mp["seventeen"] = 17;
	mp["eighteen"] = 18;
	mp["nineteen"] = 19;

	mp["twenty"] = 20;
	mp["thirty"] = 30;
	mp["forty"] = 40;
	mp["fifty"] = 50;
	mp["sixty"] = 60;
	mp["seventy"] = 70;
	mp["eighty"] = 80;
	mp["ninety"] = 90;
}

int do_ten(int l, int r)
{
	if (l > r)
		return 0;

	if (l == r)
		return mp[vs[l]];
	else
	{
		int a, b;
		return mp[vs[l]] + mp[vs[r]];
	}
}

int do_hundred(int l, int r)
{
	if (l > r)
		return 0;

	int ret = 0;

	int i;
	for (i = l; i <= r; ++ i)
		if (vs[i] == "hundred")
			break;
	if (i <= r)
	{
		ret += 100*do_ten(l,i-1);
		l = i + 1;
	}

	if (l < r && vs[l] == "and")
		++ l;

	ret += do_ten(l,r);

	return ret;
}

int main()
{
	init();
	string s;
	getline(cin, s);
	stringstream ss(s);
	int t;
	ss >> t;
	while (t --)
	{
		string str;
		getline(cin, str);
		stringstream sin(str);

		string tmp;
		vs.clear();
		while ( sin >> tmp)
			vs.push_back(tmp);

		int ans = 0;

		int l = 0, r;
		for (r = l; r < vs.size(); ++ r) if (vs[r] == "million") break;
		if (r != vs.size()) {
			ans += 1000000*do_hundred(l,r-1);
			l = r + 1;
		}

		for (r = l; r < vs.size(); ++ r) if (vs[r] == "thousand") break;
		if (r != vs.size()) {
			ans += 1000*do_hundred(l,r-1);
			l = r + 1;
		}

		//cout << l << " " << vs.size()-1 << endl;
		ans += do_hundred(l,vs.size()-1);

		cout << ans << endl;
	}
}
