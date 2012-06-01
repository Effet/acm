#include <stdio.h>
#include <string.h>
#include <string>
#include <iostream>
#include <algorithm>
#include <math.h>

char map[10][10];

int _is(char *temp) {
	int i, n, flag;
	for (flag = 0, n = i = 1; i < 4; i++) {
		if (temp[i] == temp[0])
			n++;
		else if (temp[i] == '*' && !flag) {
			flag = 1;
			n++;
		}
	}
	if (n == 4) {
		printf( " 1\n" );
		return 1;
	}
	for (flag = 0, n = 1, i = 2; i < 5; i++) {
		if (temp[i] == temp[1] || temp[i] == '*')
			n++;
		else if (temp[i] == '*' && !flag) {
			flag = 1;
			n++;
		}
	}
	if (n == 4) {
		printf( " 1\n" );
		return 1;
	}
	printf( " 0\n");
	return 0;
}

int sov(int a, int b) {
	int i;
	char temp[6];
	for (i = 0; i < 5; i++)
		temp[i] = map[i][b];
//	for ( i=0; i<5; i++ )
//		printf( "%c", temp[i]);
//	printf(" 1");

	if (_is(temp))
		return 0;
	for (i = 0; i < 5; i++)
		temp[i] = map[a][i+1];
//	for ( i=0; i<5; i++ )
//		printf( "%c", temp[i]);
//	printf(" 2");

	if (_is(temp))
		return 0;

	if (a - b <= 1 && b - a <= 1) {
		memset(temp, 0, sizeof(temp));
		for (i = 0; i < 5; i++)
			temp[i] = map[i][i + b - a];

//		for ( i=0; i<5; i++ )
//			printf( "%c", temp[i]);
//		printf(" 3");
		if (_is(temp))
			return 0;
	}
	if (a + b <= 5 && a + b >= 3) {
		memset(temp, 0, sizeof(temp));
		for (i = 0; i < 5; i++)
			temp[i] = map[i][a + b - i];
		for ( i=0; i<5; i++ )
			printf( "%c", temp[i]);
		printf(" 4");

		if (_is(temp))
			return 0;
	}
	return 1;
}

int main() {
	int i, j, n;
	char temp[10];
	while (gets(temp)) {
		if (temp[0] == 'F')
			break;
		if (temp[0] != 'X' && temp[0] != 'O' && temp[0] != '*')
			gets(temp);
		memset(map, 0, sizeof(map));
		for (j = 0; j < 5; j++)
			map[0][j+1] = temp[j + j];
		for (i = 1; i < 5; i++) {
			for (j = 0; j < 5; j++) {
				scanf("%c", &map[i][j+1]);
				getchar();
			}
		}
		for (n = i = 0; i < 5; i++) {
			for (j = 0; j < 5; j++) {
				if (map[i][j+1] == '*')
					if (sov(i, j+1)) {
						printf("%d\n", 5 * i + j + 1);
						n = 1;
						break;
					}
			}
			if (n)
				break;
		}
	}
	return 0;
}
