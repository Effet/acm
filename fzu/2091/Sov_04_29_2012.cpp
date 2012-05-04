#include <iostream>
#include <stack>
#include <cstdio>
#include <cstring>
using namespace std;

int main()
{
	int t;
	scanf("%d", &t);
	while (t--)
	{
		int n, m;
		scanf("%d%d", &n, &m);
		stack<int> s;
		s.push(1);
		while (m--)
		{
			char Cmd[11];
			int now;
			scanf("%s", Cmd);
			if (strcmp(Cmd, "PRE") == 0) {
				now = s.top();
				s.pop();
				if (s.empty())
					s.push(now);
				else
					now = s.top();
			} else if (strcmp(Cmd,"NEXT") == 0) {
				if (s.empty()) {
					now = 1;
					s.push(1);
				} else {
					now = s.top();
					if (now < n)
						s.push(++now);
				}
			} else if (strcmp(Cmd,"PLAY") == 0) {
				scanf("%d", &now);
				if (s.empty() || now != s.top())
					s.push(now);
			}
			cout << now << endl;
		}
	}
	return 0;
}
