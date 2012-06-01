#include <stdio.h>
#include <string.h>

int main(){
	freopen("D-large.in", "r", stdin);
	freopen("c.out", "w", stdout);
	int t, cas;
	int n, i, a;
	int ans;
	while (scanf("%d", &t) != EOF ) {
		for (cas=1; cas<=t; cas++) {
			scanf("%d", &n);
			for (ans=0,i=1; i<=n; i++){
				scanf("%d", &a);
				if (a != i) ans++;
			}
			printf("Case #%d: %d.000000\n", cas, ans);
		}
	}
	fclose(stdin);
	fclose(stdout);
	return 0;
}