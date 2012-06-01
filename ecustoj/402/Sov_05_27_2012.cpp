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

int vol(char *str, int n) {
	int i, j, ans;
	ans = 100000;
	for ( i=0; i<n-2; i++)
		if (str[i] == 'l' && str[i+1] == 'o' && str[i+2] == 'l') return 0;
	for (i=0; i<n; i++) {
		if ( str[i] == 'o' ) {
			if ( i > 0 && str[i-1] == 'l') return 1;
			if ( i < n-1 && str[i+1] == 'l') return 1;
			ans = 2;
		}
	}
	for ( i=0; i<n; i++) {
		if ( str[i] == 'l' ) {
			if ( str[i+1] == 'l' || str[i+2] == 'l') return 1;
		}
	}
	if ( ans == 2 ) return 2;
	else for ( i=0; i<n; i++ ) {
		if ( str[i] == 'l' ) {
			if ( str[i+2] == 'l' ) return 2;
		}
	}
	for ( i=0; i<n; i++ ) {
		if (str[i] == 'l') return 2;
	}
	return 3;
}

int main() {
	int t;
	char str[55];
	while ( scanf("%d", &t) != EOF ) {
		while (t--) {
			scanf("%s", str);
			printf("%d\n", vol(str, strlen(str)));
		}
	}
	return 0;
}
