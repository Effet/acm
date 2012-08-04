/*
 * Problem name: Popular Cows
 *  Solved when: 2011-8-5
 *       Author: nesua
 *  Description: 如果牛A认为牛B受欢迎，牛B认为牛C受欢迎，那么牛A就认为牛C受欢迎。
 *  求受所有牛欢迎的牛有几只？
 *      解题思路: 强连通，将图缩点后枚举求解。 
 *      难易程度: ★★★★☆
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <vector>
#include <queue>
#include <map>
#include <algorithm>
#include <iostream>
using namespace std;
#define GRPH_N 0
#define GRPH_T 1
#define WHITE 0
#define BLACK 1
const int MAX_VETX = 10000 + 10;
const int MAX_EDGE = 50000 + 10;

typedef struct edge {
	int u, v; //指u到v的一条边
} Edge;
typedef struct adjacent_table { //正向表前向星
	int beg, end;
} AdjT;
bool cmp1(const Edge& a, const Edge& b) { //正图
	return a.u < b.u;
}
bool cmp2(const Edge& a, const Edge& b) { //反图
	return a.v < b.v;
}

Edge E[MAX_EDGE]; //边集
AdjT Head[MAX_VETX]; //正向表
int n, m;
bool readin() {
	if (scanf("%d%d", &n, &m) == EOF
	)
		return false;
	for (int i = 0; i < m; i++)
		scanf("%d%d", &E[i].u, &E[i].v);
	return true;
}

void ComputeGraph() {
	sort(E, E + m, cmp1);

	for (int i = 1; i <= n; i++)
		Head[i].beg = -1;
	int pre = -1, now;
	for (int i = 0; i < m; i++) {
		now = E[i].u;
		if (now != pre) {
			if (i != 0)
				Head[pre].end = i - 1;
			Head[now].beg = i, pre = now;
		}
	}
	Head[pre].end = m - 1;
}

void ComputeGraphT() {
	sort(E, E + m, cmp2);

	for (int i = 1; i <= n; i++)
		Head[i].beg = -1;
	int pre = -1, now;
	for (int i = 0; i < m; i++) {
		now = E[i].v;
		if (now != pre) {
			if (i != 0)
				Head[pre].end = i - 1;
			Head[now].beg = i, pre = now;
		}
	}
	Head[pre].end = m - 1;
}

int time;
bool cover[MAX_VETX];
int f[MAX_VETX];
void DFSVisit(int u) {
	cover[u] = BLACK;
	if (Head[u].beg != -1)
		for (int i = Head[u].beg; i <= Head[u].end; i++) {
			int v = E[i].v;
			if (cover[v] == WHITE
			)
				DFSVisit(v);
		}
	f[++time] = u;
}
void DFS() {
	for (int i = 1; i <= n; i++)
		cover[i] = WHITE;
	time = 0;
	for (int i = 1; i <= n; i++)
		if (cover[i] == WHITE
		)
			DFSVisit(i);
}

int sig;
int belg[MAX_VETX];
void DFSVisit_2(int u) {
	cover[u] = BLACK;
	if (Head[u].beg != -1)
		for (int i = Head[u].beg; i <= Head[u].end; i++) {
			int v = E[i].u;
			if (cover[v] == WHITE
			)
				DFSVisit_2(v);
		}
	belg[u] = sig;
}
void DFS2() {
	for (int i = 1; i <= n; i++)
		cover[i] = WHITE;
	sig = 0;
	for (int i = time; i >= 1; i--)
		if (cover[f[i]] == WHITE) {
			++sig;
			DFSVisit_2(f[i]);
		}
}

void Kosaraju() {
	ComputeGraph();
	DFS();
	ComputeGraphT();
	DFS2();
}

int out[MAX_VETX];
void print() {

	memset(out, 0, sizeof(out));
	for (int i = 0; i < m; i++) {
		if (belg[E[i].u] != belg[E[i].v])
			out[belg[E[i].u]] = 1;
	}
	int flag = 0, place;
	for (int i = 1; i <= sig; i++) {
		if (!out[i]) {
			flag++;
			place = i;
		}
	}
	if (flag == 1) {
		int ans = 0;
		for (int i = 1; i <= n; i++)
			if (belg[i] == place)
				ans++;
		printf("%d\n", ans);
	} else {
		printf("0\n");
	}
}

int main() {
	freopen("POJ.in", "r", stdin);
	while (readin()) {
		Kosaraju();
		print();
	}
	return 0;
}


//使用了链式前向星（数组模拟链表），速度微微提升
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <vector>
#include <queue>
#include <map>
#include <algorithm>
#include <iostream>
using namespace std;
#define GRPH_N 0
#define GRPH_T 1
#define WHITE 0
#define BLACK 1
const int MAX_VETX = 10000 + 10;
const int MAX_EDGE = 50000 + 10;
 typedef struct edge { int u, v; } Edge; //指u到v的一条边
typedef struct forward_table{int to, next;}FwdT; //链式前向星

Edge E[MAX_EDGE]; //边集
FwdT F[MAX_EDGE];
int head[MAX_VETX];
int n, m;
bool readin() {
   if (scanf("%d%d", &n, &m) == EOF) { return false; }
   for (int i = 0; i < m; i++)
      scanf("%d%d", &E[i].u, &E[i].v);
   return true;
}

void insertDirectEdge(int i, int u, int v){
   F[i].to = v; F[i].next = head[u]; head[u] = i;
}
void computeGraph(bool type) {
   for(int i=1; i<=n; i++) head[i] = -1;
   for(int i=0; i<m; i++) F[i].next = -1;
   for(int i=0;i<m;i++){
      if(type == GRPH_N){ insertDirectEdge(i+1, E[i].u, E[i].v); }
      else{ insertDirectEdge(i+1, E[i].v, E[i].u); }
   }
}

int f[MAX_VETX], time;
bool cover[MAX_VETX];
void DFS_Visit(int u) {
   cover[u] = BLACK;
   for (int i = head[u]; i!=-1; i=F[i].next)
      if (cover[F[i].to] == WHITE)
         DFS_Visit(F[i].to);
   f[++time] = u;
}
void DFS(){
   for (int i = 1; i <= n; i++)
      cover[i] = WHITE;
   time = 0;
   for (int i = 1; i <= n; i++)
      if (cover[i] == WHITE)
         DFS_Visit(i);
}
int sig;
int belg[MAX_VETX];
void DFS_Visit_2(int u) {
   cover[u] = BLACK;
   for (int i = head[u]; i!=-1; i=F[i].next)
      if (cover[F[i].to] == WHITE)
         DFS_Visit_2(F[i].to);
   belg[u] = sig;
}
void DFS2() {
   for (int i = 1; i <= n; i++)
      cover[i] = WHITE;
   sig = 0;
   for (int i = time; i >= 1; i--)
      if (cover[f[i]] == WHITE){ ++sig; DFS_Visit_2(f[i]); }
}

void Kosaraju() {
   computeGraph(GRPH_N);//建正图
   DFS();
   computeGraph(GRPH_T);//建反图
   DFS2();
}

int out[MAX_VETX];
void print() {
   memset(out, 0, sizeof(out));
   for (int i = 0; i < m; i++)
      if (belg[E[i].u] != belg[E[i].v]) out[belg[E[i].u]] = 1;
   int flag = 0, place;
   for (int i = 1; i <= sig; i++) {
      if (!out[i]) { flag++; place = i; }
   }
   if (flag == 1) {
      int ans = 0;
      for (int i = 1; i <= n; i++)
         if (belg[i] == place) ans++;
      printf("%d\n", ans);
   } else { printf("0\n"); }
}

int main() {
   freopen("POJ.in", "r", stdin);
   while (readin()) {
      Kosaraju();
      print();
   }
   return 0;
}
