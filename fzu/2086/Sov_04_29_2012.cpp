#include <iostream>
#include <cstdio>
#include <vector>
#include <map>
using namespace std;

int cnt[5];
int x[5][10];

int main()
{
	int t;
	scanf("%d", &t);
	while (t--)
	{
		for (int i = 0; i < 5; ++ i)
			scanf("%d", &cnt[i]);
		for (int i = 0; i < 5; ++ i)
			for (int j = 0; j < cnt[i]; ++ j)
				scanf("%d", &x[i][j]);

		int sml, big;
		scanf("%d%d", &sml, &big);

		int ans = 0;
		for (int i = 0; i < cnt[3]; ++ i)
			for (int j = i; j < cnt[3]; ++ j)
				for (int ii = 0; ii < cnt[4]; ++ ii)
					for (int jj = ii; jj < cnt[4]; ++ jj)
					{
						int fee = x[3][i]+(i==j?0:x[3][j]) + x[4][ii]+(ii==jj?0:x[4][jj]);

						for (int iii = 0; iii < cnt[0]; ++ iii)
							for (int jjj = 0; jjj < cnt[1]; ++ jjj)
							{
								int fee2 = fee + x[0][iii]+x[1][jjj];
								if (fee2 >= sml && fee2 <= big)
									++ ans;
							}

						for (int iii = 0; iii < cnt[2]; ++ iii)
						{
							int fee2 = fee + x[2][iii];
							if (fee2 >= sml && fee2 <= big)
								++ ans;
						}
					}

		printf("%d\n", ans);
	}
	return 0;
}
