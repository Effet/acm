#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;

const int MAX_N = 100000 + 30;
const int MAX_M = MAX_N;
const int LIMIT = MAX_N + MAX_M + 100;

int get_next(int x) { return x&(-x); }

int get_sum_one_to_x(int *a, int x) {
    int sum = 0;
    while (x > 0) {
        sum += a[x];
        x -= get_next(x);
    }
    return sum;
}

int get_x(int *a, int x) {
    return get_sum_one_to_x(a,x) - get_sum_one_to_x(a,x-1);
}

void add_to_x(int *a, int x, int val) {
    while (x <= LIMIT) {
        a[x] += val;
        x += get_next(x);
    }
}

void modify_x_to(int *a, int x, int to) {
    add_to_x(a, x, to - get_x(a, x));
}

int a[LIMIT+30];
int id[MAX_N+30];

int main() {
    int t;
    scanf("%d", &t);
    while (t--) {
        int n, m;
        scanf("%d%d", &n, &m);

        int BEgin = MAX_M + 10;
        memset(a, 0, sizeof(a));
        for (int i = 1; i <= n; ++ i) {
            add_to_x(a, i+BEgin, 1);
            id[i] = i + BEgin;
        }
  
        for (int i = 0; i < m; ++ i) {
            int x;
            scanf("%d", &x);
            // printf("id of %d is %d\n", x, id[x]);
            printf("%d", get_sum_one_to_x(a, id[x]-1));
            if (i < m - 1)
                putchar(' ');
            else
                putchar('\n');
            modify_x_to(a, id[x], 0);
            id[x] = BEgin --;
            modify_x_to(a, id[x], 1);
        }
    }
    return 0;
}
