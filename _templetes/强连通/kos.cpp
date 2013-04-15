#include <stdio.h>
#include <string.h>
#include <vector>
#include <iostream>
using namespace std;
#define MAXN 110000
bool flag[MAXN];
int n, numb[MAXN], belg[MAXN];
vector<int> adj[MAXN], radj[MAXN];

void VisitOne(int cur, int &sig) {
    flag[cur] = true;
    for (int i=0; i<adj[cur].size(); ++i)
        if (flag[adj[cur][i]] == false)
            VisitOne(adj[cur][i],sig);
    numb[++sig] = cur;
}

void VisitTwo(int cur, int sig) {
    flag[cur] = true;
    belg[cur] = sig;
    for (int i=0; i<radj[cur].size(); ++i)
        if (flag[radj[cur][i]] == false)
            VisitTwo(radj[cur][i],sig);
}

int Kosaraju_StronglyConnectedComponent() {
    int i, sig;
    memset(flag+1,0,sizeof(bool)*n);
    for (sig=0,i=1; i<=n; ++i)
        if (flag[i] == false)
            VisitOne(i,sig);

    memset(flag+1,0,sizeof(bool)*n);
    for (sig=0,i=n; i>0; --i)
        if (flag[numb[i]] == false)
            VisitTwo(numb[i],++sig);
   
    return sig;
}
