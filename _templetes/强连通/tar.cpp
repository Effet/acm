#include <stdio.h>
#include <string.h>
#include <iostream>
#include <vector>
#include <set>
using namespace std;

#define MAXN 30001

enum {NOTVIS, VIS, OVER};
int flag[MAXN];

int indx[MAXN], mlik[MAXN];
int stck[MAXN];

int n, belg[MAXN];
vector<int> adj[MAXN];


void Visit(int x, int &sig, int &scc_num) {
    stck[++stck[0]] = x;
    flag[x] = VIS;
    mlik[x] = indx[x] = ++sig;
    for (int i=0; i<adj[x].size(); ++i) {
        int y = adj[x][i];
        if (NOTVIS == flag[y]) {
            Visit(y, sig, scc_num);
            mlik[x] = min(mlik[x], mlik[y]);
        }
        else if (VIS == flag[y])
            mlik[x] = min(mlik[x], indx[y]);
    }
    if (mlik[x] == indx[x]) {
        ++scc_num;
        do {
            belg[stck[stck[0]]] = scc_num;
            flag[stck[stck[0]]] = OVER;
        } while (stck[stck[0]--] != x);
    }
}

int Tarjan_StronglyConnectedComponent() {
    int i, sig, scc_num;
    memset(flag+1,NOTVIS,sizeof(int)*n);
    sig = 0; scc_num = 0; stck[0] = 0;
    for (i=1; i<=n; ++i)
        if (NOTVIS==flag[i])
            Visit(i,sig,scc_num);
    return scc_num;
}
