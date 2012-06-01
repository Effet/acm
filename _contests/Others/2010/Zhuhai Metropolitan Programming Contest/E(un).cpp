#include <stdio.h>
#include <string.h>
#include <string>
#include <iostream>
#include <algorithm>
#define TEXT 200
#define MAXN 20002
using namespace std;

char a[TEXT];
char b[TEXT];
int k;

void encry(int l, int r) {
	int t;
	if (r - l < 0)
		return;
	if (r - l == 0) {
		b[r] = a[k++];
		return;
	}
	if (r - l == 1) {
		b[l] = a[k++];
		b[r] = a[k++];
		return;
	}
	t = (r + l) / 2;
	if (b[t] == -1)
		b[t] = a[k++];
	encry(l, t - 1);
	encry(t + 1, r);
}

int main() {
	int t, len, i;
	char c;
	while (scanf("%d", &t) != EOF) {
		getchar();
		len = 0;
		while (t--) {
			gets(a);
			len = strlen(a);
			k = 0;
			memset(b, -1, sizeof(b));
			encry(0, len - 1);
			for( i=0; i<len; i++ )
				printf( "%c", b[i] );
			printf("\n");
		}
	}
	return 0;
}