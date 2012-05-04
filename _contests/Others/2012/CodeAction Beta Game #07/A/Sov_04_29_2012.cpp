#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;

int main()
{
	int n;
	scanf("%d", &n);

	double Score = 0;
	double Jam = 0;
	while (n--)
	{
		char Cmd[15];
		scanf("%s", Cmd);
		if (strcmp(Cmd,"Cool") == 0) {
			Score += 200 + 10*(int)Jam;
			Jam += 1.0/25;
		} else if (strcmp(Cmd,"Good") == 0) {
			Score += 100 + 5*(int)Jam;
			Jam += 1.0/50;
		} else if (strcmp(Cmd,"Bad") == 0) {
			Jam = 0;
		} else if (strcmp(Cmd,"Miss") == 0) {
			Score = max(0.0, Score-10);
			Jam = 0;
		}
	}
	printf("%d\n", (int)Score);
	return 0;
}
