#include <stdio.h>
#include <string.h>
#include <math.h>

int main() {
	double x1, y1;
	double x, y;
	int cas, t, i;
	while (scanf("%d", &t) != EOF) {
		for (cas = 1; cas <= t; cas++) {
			scanf("%lf%lf", &x1, &y1);
			x = x1 + sqrt(y1);
			y = y1 + sqrt(x1);
			i = 100000;
			while (i--) {
				x = x1 + sqrt(y);
				y = y1 + sqrt(x);
			}
			printf("Case %.6lf: %.6lf\n", x, y);
		}
	}
	return 0;
}