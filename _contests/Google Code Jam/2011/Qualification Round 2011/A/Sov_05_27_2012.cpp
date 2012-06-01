#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

#define MAXN 105
#define max(a,b) ((a)>(b)?(a):(b))
#define min(a,b) ((a)<(b)?(a):(b))
using namespace std;

typedef struct robot{
	int r, p, d;
}ROB;

int main() {
	freopen("A-large.in", "r", stdin);
	freopen("c.out", "w", stdout);
	int t, cas;
	int o, b, p;
	int n, i;
	ROB ord[MAXN];
	char r;

	while (scanf("%d", &t)!=EOF) {
		for (cas=1; cas<=t; cas++) {
			scanf("%d%*", &n);

			memset(ord, 0, sizeof(ord));

			o = b = 1;
			for (i=0; i<n; i++) {
				scanf("%c%d%*", &r, &p);
				if ( r == 'O' ) {
					ord[i].r = 0;
					ord[i].p = abs(p - o) + 1;
					o = p;
				} else {
					ord[i].r = 1;
					ord[i].p = abs(p - b) + 1;
					b = p;
				}
			}

			ord[0].d = ord[0].p;
			for (i=1; i<n; i++) {
				if ( ord[i].r != ord[i-1].r ) {
					if (ord[i].p - ord[i-1].d <=0 ) {
						ord[i].d = 1;
						ord[i].p = ord[i-1].p + 1;
					} else {
						ord[i].d = ord[i].p- ord[i-1].d;
						ord[i].p = ord[i-1].p + ord[i].p - ord[i-1].d;
					}
				} else {
					ord[i].d += ord[i].p + ord[i-1].d;
					ord[i].p += ord[i-1].p;
				}
			}

			printf("Case #%d: %d\n", cas, ord[n-1].p);
		}
	}
	fclose(stdin);
	fclose(stdout);
	return 0;
}