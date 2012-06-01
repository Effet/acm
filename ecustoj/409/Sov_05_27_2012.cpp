#include <cstdio>
#include <stdio.h>
#include <iostream>
#include <string.h>
#include <cstring>
#include <algorithm>
#include <string>
#include <math.h>
#include <cmath>
using namespace std;

#define MAXN 300
#define inf 1000000000
typedef int elem_t;

void floyd_warshall(int n, elem_t mat[][MAXN], elem_t min[][MAXN],
		int pre[][MAXN]) {
	int i, j, k;
	for (i = 0; i < n; i++)
		for (j = 0; j < n; j++)
			min[i][j] = mat[i][j], pre[i][j] = (i == j) ? -1 : i;
	for (k = 0; k < n; k++)
		for (i = 0; i < n; i++)
			for (j = 0; j < n; j++)
				if (min[i][k] + min[k][j] < min[i][j])
					min[i][j] = min[i][k] + min[k][j], pre[i][j] = pre[k][j];
}

int main() {
	int t, n, i, j, ans;
	int rod[MAXN];
	int mat[MAXN][MAXN], min[MAXN][MAXN], pre[MAXN][MAXN];
	while (scanf("%d", &t) != EOF) {
		while (t--) {
			scanf("%d", &n);
			for (i = 0; i < n; i++)
				scanf("%d", &rod[i]);
			for (i = 0; i < n; i++) {
				for (j = 0; j < n; j++) {
					scanf("%d", &mat[i][j]);
					if ( mat[i][j] == -1 ) mat[i][j] = inf;
				}
			}
			floyd_warshall(n, mat, min, pre);
			/*for (i = 0; i < n; i++) {
				for (j = 0; j < n; j++)
					printf("%d ", min[i][j]);
				printf("\n");
			}*/
			for (ans = i = 0; i < n - 1; i++) {
				if ( min[rod[i]][rod[i+1]] == inf ) break;
				ans += min[rod[i]][rod[i + 1]];
			}
			if ( i < n - 1 ) printf("impossible\n");
			else {
				if ( min[rod[n-1]][rod[0]] == inf ) printf("impossible\n");
				else {
					ans += min[rod[n - 1]][rod[0]];
					printf("%d\n", ans);
				}
			}
		}
	}
	return 0;
}
