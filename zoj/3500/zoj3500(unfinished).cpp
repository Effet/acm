#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <iostream>
#define PI acos(-1)
#define swap(a,b) a=a^b;b=b^a;a=a^b
using namespace std;

int main() {
	int n;
	int r1, r2, t;
	int x1, x2, y1, y2, z1, z2;
	double d, d1, d2, det, ans;
	double v1, v2, v;
	while (scanf("%d", &n) != EOF) {
		while (n--) {
			scanf("%d%d%d%d", &x1, &y1, &z1, &r1);
			scanf("%d%d%d%d", &x2, &y2, &z2, &r2);

			v = ((r1 * r1 * r1 + r2 * r2 * r2) * 4 + 0.0) / 3;
			if (r1 > r2) {
				t = r1;
				r1 = r2;
				r2 = t;
			}

			t = (x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2) + (z1 - z2) * (z1
					- z2);

			if (t >= (r1 + r2) * (r1 + r2)) {
				v1 = 0.0, v2 = 0.0;
			} else if (t < (r2 - r1) * (r2 - r1)) {
				v1 = (r1 * r1 * r1 * 8 + 0.0) / 3;
				v2 = 0.0;
			} else {
				d = sqrt(t + 0.0);
				det = (r2 * r2 - r1 * r1 + 0.0) / d;
				if (t <= r2 * r2 - r1 * r1) {
					d1 = det - d;
					d2 = det;

					d1 = r1 + r2 - d1;
					d2 = r2 - d2;
					v1 = (r1 * r1 * r1 * 4 + 0.0) / 3 - d1 * d1 * (r1 - d1 / 3);
					v2 = d2 * d2 * (r2 - d2 / 3);
				} else if (t == r2 * r2 - r1 * r1) {
					d2 = d;
					v1 = (r1 * r1 * r1 + 4.0) / 3;
					v2 = d2 * d2 * (r2 - d2 / 3);
				} else {

					d1 = (d - det) / 2;
					d2 = d1 + det;

					d1 = r1 - d1;
					d2 = r2 - d2;

					v1 = d1 * d1 * (r1 - d1 / 3);
					v2 = d2 * d2 * (r2 - d2 / 3);
				}

			}

			ans = (v - v1 - v2) * PI;
			printf("%.2lf\n", ans);
		}
	}
	return 0;
}
