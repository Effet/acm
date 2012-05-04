#include <iostream>
#include <string>
#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;

#define MAX_N 11111

struct array {
	char name[100];
} a[MAX_N];

bool cmp(array const & aa, array const & bb) {
	return strcmp(aa.name, bb.name) < 0;
}

int main()
{
	int t;
	scanf("%d", &t);
	while (t --)
	{
		int n;
		scanf("%d", &n);
		for (int i = 0; i < n; ++ i)
			scanf("%s", a[i].name);
		sort(a, a+n, cmp);
		for (int i = 0; i < n; ++ i)
			printf("%s", a[i].name);
		printf("\n");
	}
	return 0;
}
