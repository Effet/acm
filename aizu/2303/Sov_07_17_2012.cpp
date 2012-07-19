#include <iostream>
#include <cstdio>
#include <cmath>
using namespace std;

typedef long long ll;

const int MAX_N = 100 + 10;
const int MAX_M = 50 + 2;

struct runner {
    int p, t, v;
    double pp[MAX_M];
} R[MAX_N];

double C[MAX_M][MAX_M];
void init()
{
    C[0][0] = 1.0;
    for (int i = 1; i < MAX_M; ++ i)
    {
        C[i][1] = i + 0.0;
        C[i][0] = C[i][i] = 1.0;
    }
    for (int i = 2; i < MAX_M; ++ i)
        for (int j = 1; j < i; ++ j)
            C[i][j] = C[i-1][j-1] + C[i-1][j];
}

int main(int argc, char *argv[])
{
    init();
    int N, M, L;
    while (cin >> N >> M >> L)
    {
        for (int i = 0; i < N; ++ i)
            cin >> R[i].p >> R[i].t >> R[i].v;

        for (int i = 0; i < N; ++ i)
            for (int j = 0; j <= M; ++ j)
                R[i].pp[j] = C[M][j] * pow(R[i].p*1.0/100, j) * pow((100.0 - R[i].p)/100, M-j);

        for (int i = 0; i < N; ++ i)
        {
            double ppp = 0;
            for (int j = 0; j <= M; ++ j)
            {
                double pp = R[i].pp[j];
                for (int ii = 0; ii < N; ++ ii)
                {
                    if (ii == i)
                        continue;

                    double p2 = 0;
                    for (int jj = 0; jj <= M; ++ jj)
                    {
                        int a = L * R[i].v + jj * R[ii].t * R[i].v * R[ii].v;
                        int b = L * R[ii].v + j * R[i].t * R[ii].v * R[i].v;
                        if (a > b)
                            p2 += R[ii].pp[jj];
                    }
                    pp *= p2;
                }
                ppp += pp;
            }
            printf("%.10lf\n", ppp);
        }
    } 

    return 0;
}
