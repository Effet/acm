#include <ctime>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;

// 前 10^7 个数中有 664,579个素数
const int Limit = 10000000;

bool sieve[Limit + 1];
// int primes[Limit / 2 + 1];
int primes[664590];


void Sieve_of_Eratosthenes()
{
    for (int i = 4; i <= Limit; i += 2) sieve[i] = 1;
	for (int i = 3; i * i <= Limit; i += 2)
        if (!sieve[i])
            for (int j = i * i; j <= Limit; j += i)
                sieve[j] = 1;
    
    primes[0] = 1; primes[1] = 2;
	for(int i = 3; i <= Limit; i += 2)
		if(!sieve[i])
			primes[++ primes[0]] = i;
}


// http://blog.sina.com.cn/s/blog_48f85e1d0100ns71.html
void Sieve_of_Eratosthenes_2(){ //传说中的2倍压缩筛选素数
    int sievelimit = (sqrt(Limit + .0) - 1) / 2; //只需筛到一半
    int maxindex = (Limit - 1) / 2;
    for(int n = 1; n <= sievelimit; ++ n){
        if(sieve[n] == 0){
            int t = 2*n + 1; //每次表示域增加2n+1
            for(int k = 2*n*(n+1); k <= maxindex; k += t) //从2n(n+1)开始
                sieve[k] = 1;
        }
    }
    primes[0] = 1; primes[1] = 2;
    for(int n = 1; n <= maxindex; ++ n){
        if(sieve[n]==0)
            primes[++ primes[0]] = 2*n+1;//p[n]==0表示的是2*n+1是素数
    }
}


// http://en.wikipedia.org/wiki/Sieve_of_Atkin
void Sieve_of_Atkin()
{
    int root = (int)ceil(sqrt(Limit + .0));
    for (int z = 0; z <= Limit; ++ z) sieve[z] = 0;
    for (int x = 1; x <= root; ++ x)
    {
        for (int y = 1; y <= root; ++ y)
        {
            int n = 4*x*x + y*y;
            if (n <= Limit && (n % 12 == 1 || n % 12 == 5)) sieve[n] ^= 1;
            n = 3*x*x + y*y;
            if (n <= Limit && n % 12 == 7) sieve[n] ^= 1;
            n = 3*x*x - y*y;
            if (x > y && n <= Limit && n % 12 == 11) sieve[n] ^= 1;
        }
    }
    for (int r = 5; r <= root; ++ r)
        if (sieve[r])
            for (int i = r*r; i <= Limit; i += r*r)
                sieve[i] = 0;
    
    primes[0] = primes[1] = 2; primes[2] = 3;
    for (int a = 5; a <= Limit; ++ a)
        if (sieve[a])
            primes[++ primes[0]] = a;
}


void test(char *title, void run())
{
    time_t op, ed;
    op = clock();
    
    run();
    
    ed = clock();

    double dif = (ed - op) * 1000.0 / CLOCKS_PER_SEC;
    printf("Testing %s ...\n", title);
    printf("primes: %d, time use: %.3lf ms.\n", primes[0], dif);
}


int main(int argc, char *argv[])
{
    test("Sieve of Eratosthenes",
         Sieve_of_Eratosthenes);
    
    memset(sieve, 0, sizeof(sieve));
    test("Sieve of Eratosthenes 2",
         Sieve_of_Eratosthenes_2);
    
    memset(sieve, 0, sizeof(sieve));
    test("Sieve of Atkin",
         Sieve_of_Atkin);
    return 0;
}
