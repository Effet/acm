#include<stdio.h>
#include<iostream>
#include<algorithm>
using namespace std;

const int MAX_VETX = 100;
const int MAX_EDGE = 100;

//有向图链式前向星即是数组模拟链表，需先初始化head和next
typedef struct forward_table{int to, next;}FwdT;
int n, m, head[MAX_VETX];
FwdT F[MAX_EDGE];
//第i条从u到v的边
void insertDirectEdge(int i, int u, int v){
   F[i].to = v, F[i].next = head[u], head[u] = i;
}

//无向图链式前向星
//typedef struct forward_table{int to, next;}FwdT;
//int n, m, head[MAX_VETX];
//int weight[MAX_EDGE];//两边共用权值
//FwdT F[MAX_EDGE*2];
//void insertUndirectEdge(int i, int u, int v, int w){
//   F[i<<1].to = v, F[i<<1].next = head[u], head[u] = i<<1;
//   F[i<<1|1].to = u, F[i<<1|1].next = head[v], head[v] = i<<1|1;
//   weight[i] = w;
//}

//普通前向星，不用初始化
//typedef struct edge{ int //u, v; }Edge;
//typedef struct forward_table{ int beg, end; }FwdT;
//bool cmp(const Edge& a, const Edge& b){ return a.u < b.u; }
//Edge E[MAX_EDGE];
//FwdT head[MAX_VETX];
//int n, m;
//void ComputeGraph() {
//   sort(E, E + m, cmp);

//   for (int i = 1; i <= n; i++)
//      head[i].beg = -1;
//   int pre = -1, now;
//   for (int i = 0; i < m; i++) {
//      now = E[i].u;
//      if (now != pre) {
//         if (i != 0)
//            head[pre].end = i - 1;
//         head[now].beg = i, pre = now;
//      }
//   }
//   head[pre].end = m - 1;
//}
