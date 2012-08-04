const int MAX_N = 100000 + 100;

int phi[MAX_N];

void euler()
{
    for(int i = 1; i < MAX_N; ++ i) phi[i]=i;
    for(int i = 2; i < MAX_N; i+=2) phi[i]/=2;
    for(int i = 3; i < MAX_N; i+=2)
        if(phi[i] == i)
            for(int j = i ; j < MAX_N; j+=i)
                phi[j] = phi[j]/i * (i-1);
}
