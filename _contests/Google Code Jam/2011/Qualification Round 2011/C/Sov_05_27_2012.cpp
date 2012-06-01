#include <stdio.h>
#include <string.h>
#define MAXN 1001

int main() {
	freopen("C-large.in", "r", stdin);
	freopen("c.out", "w", stdout);

	int t, cas;
	int n, i;
	int all, c, num;
	int sma;
	while (scanf("%d", &t) != EOF) {
		for (cas = 1; cas <= t; cas++) {

			scanf("%d%d", &n, &c);
			all = sma = c;
			for (i=1; i < n; i++) {
				scanf("%d", &num);
				if ( num < sma ) sma = num;
				all += num;
				c ^= num;
			}
			if ( c )
				printf("Case #%d: NO\n", cas);
			else
				printf("Case #%d: %d\n", cas, all - sma);
		}
	}
	fclose(stdin);
	fclose(stdout);
	return 0;
}