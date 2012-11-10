// Timothy Chan    "ch3d.cc"    12/02    3-d lower hull (in C++)

// a simple implementation of the O(n log n) divide-and-conquer algorithm

//   input: coordinates of points
//     n x_0 y_0 z_0 ... x_{n-1} y_{n-1} z_{n-1}

//   output: indices of facets
//     i_1 j_1 k_1 i_2 j_2 k_2 ...

//   warning: ignores degeneracies and robustness
//   space: uses 6n pointers


// #include <stream.h>
#include <iostream>
#include <algorithm>
#include <vector>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
using namespace std;

struct Point {
  double x, y, z;
  double rx, ry, rz;
  Point *prev, *next;
  void act() {  
    if (prev->next != this) prev->next = next->prev = this;  // insert
    else { prev->next = next; next->prev = prev; }  // delete
  }
};

const double INF = 1e99;
static Point nil = {INF, INF, INF, 0, 0};
Point *NIL = &nil;

inline double turn(Point *p, Point *q, Point *r) {  // <0 iff cw
  if (p == NIL || q == NIL || r == NIL) return 1.0;
  return (q->x-p->x)*(r->y-p->y) - (r->x-p->x)*(q->y-p->y);
}

inline double time(Point *p, Point *q, Point *r) {  
  if (p == NIL || q == NIL || r == NIL) return INF;
  return ((q->x-p->x)*(r->z-p->z) - (r->x-p->x)*(q->z-p->z)) / turn(p,q,r);
}

Point *sort(Point P[], int n) {  // mergesort

  Point *a, *b, *c, head;

  if (n == 1) { P[0].next = NIL; return P; }
  a = sort(P, n/2);
  b = sort(P+n/2, n-n/2);
  c = &head;
  do
    if (a->x < b->x) { c = c->next = a; a = a->next; }
    else { c = c->next = b; b = b->next; }
  while (c != NIL);
  return head.next;
}

void hull(Point *list, int n, Point **A, Point **B) {  // main algorithm

  Point *u, *v, *mid;  
  double t[6], oldt, newt;  
  int i, j, k, l, minl;

  if (n == 1) { A[0] = list->prev = list->next = NIL; return; }

  for (u = list, i = 0; i < n/2-1; u = u->next, i++) ;
  mid = v = u->next;
  hull(list, n/2, B, A);  // recurse on left and right sides
  hull(mid, n-n/2, B+n/2*2, A+n/2*2);

  for ( ; ; )  // find initial bridge
    if (turn(u, v, v->next) < 0) v = v->next;
    else if (turn(u->prev, u, v) < 0) u = u->prev;  
    else break;

  // merge by tracking bridge uv over time
  for (i = k = 0, j = n/2*2, oldt = -INF; ; oldt = newt) {  
    t[0] = time(B[i]->prev, B[i], B[i]->next);  
    t[1] = time(B[j]->prev, B[j], B[j]->next);    
    t[2] = time(u, u->next, v);  
    t[3] = time(u->prev, u, v);
    t[4] = time(u, v->prev, v); 
    t[5] = time(u, v, v->next);
    for (newt = INF, l = 0; l < 6; l++) 
      if (t[l] > oldt && t[l] < newt) { minl = l; newt = t[l]; }
    if (newt == INF) break;
    switch (minl) {
    case 0:  if (B[i]->x < u->x) A[k++] = B[i];  B[i++]->act();  break;
    case 1:  if (B[j]->x > v->x) A[k++] = B[j];  B[j++]->act();  break;
    case 2:  A[k++] = u = u->next;  break;
    case 3:  A[k++] = u;  u = u->prev;  break;
    case 4:  A[k++] = v = v->prev;  break;
    case 5:  A[k++] = v;  v = v->next;  break;
    }
  }
  A[k] = NIL;

  u->next = v;  v->prev = u;  // now go back in time to update pointers
  for (k--; k >= 0; k--) 
    if (A[k]->x <= u->x || A[k]->x >= v->x) {
      A[k]->act();
      if (A[k] == u) u = u->prev; else if (A[k] == v) v = v->next;
    }
    else { 
      u->next = A[k]; A[k]->prev = u; v->prev = A[k]; A[k]->next = v;
      if (A[k]->x < mid->x) u = A[k]; else v = A[k];
    }
}

const double EPS = 1e-9;

double rand01() { return (double)rand() / (double)RAND_MAX; }
double randeps() {return (rand01() - 0.5) * EPS; }

Point operator -(Point p, Point q) {
  p.rx -= q.rx;
  p.ry -= q.ry;
  p.rz -= q.rz;
  return p;
}

double dot(Point a, Point b) {return a.rx*b.rx+a.ry*b.ry+a.rz*b.rz;}
double len(Point a) {return sqrt(a.rx*a.rx+a.ry*a.ry+a.rz*a.rz);}

Point crs(Point a, Point b) {
  Point c;
  c.rx = a.ry*b.rz - a.rz*b.ry;
  c.ry = a.rz*b.rx - a.rx*b.rz;
  c.rz = a.rx*b.ry - a.ry*b.rx;
  return c;
}
// distance from p to plane p0-n
double disPF(Point p, Point o, Point n) {
  return fabs(dot(p-o, n))/len(n);
}


const int N = 1100;
Point P[N], Q[N];

int a[N*10], b[N*10], c[N*10], cnt;

double box(Point o,Point a,Point b,Point c) {
  return dot(crs(a-o, b-o), c-o);
}

int sig(double x) {return x<-EPS? -1: x>EPS? 1 : 0;}

inline bool eq(int i, int j) {
  int f[3], g[3];
  f[0] = a[i]; f[1] = b[i]; f[2] = c[i];
  g[0] = a[j]; g[1] = b[j]; g[2] = c[j];
  for (int i = 0; i < 3; i++)
    if (sig(box(P[f[0]],P[f[1]],P[f[2]],P[g[i]])))
      return false;
  return true;
}

int aa[N*10], bb[N*10], cc[N*10];
void del() {
  int i,j,k=0;
  for (i=0; i<cnt;i++) {
    for (j=0;j<i;j++)
      if (eq(i,j)) break;
    if (j==i) {
      aa[k] = a[i];
      bb[k] = b[i];
      cc[k++] = c[i];
    }
  }
  cnt = k;
  for (i=0; i<cnt; i++) {
    a[i] = aa[i];
    b[i] = bb[i];
    c[i] = cc[i];
  }
}

int main() {

  srand ( time(NULL) );

  int n, i;
  while (scanf("%d", &n) && n) {

    // Point *P = new Point[n];  // input
    // for (i = 0; i < n; i++) { cin >> P[i].x; cin >> P[i].y; cin >> P[i].z; }
    for (i = 0; i < n; i++)
      scanf("%lf%lf%lf", &P[i].rx, &P[i].ry, &P[i].rz);

    for (i = 0; i < n; i++) {
      P[i].x = P[i].rx + randeps();
      P[i].y = P[i].ry + randeps();
      P[i].z = P[i].rz + randeps();
    }
    
    // for (i = 0; i < n; i++)
    //   printf("%.9lf %.9lf %.9lf\n", P[i].x, P[i].y, P[i].z);

    Point *list = sort(P, n);
    Point **A = new Point *[2*n], **B = new Point *[2*n];
    hull(list, n, A, B);

    // Point *Q = new Point[n];
    for (i = 0; i < n; i++) {
      Q[i].x = -P[i].x;
      Q[i].y = -P[i].y;
      Q[i].z = -P[i].z;

      Q[i].rx = P[i].rx;
      Q[i].ry = P[i].ry;
      Q[i].rz = P[i].rz;
    }
    Point *list2 = sort(Q, n);
    Point **AA = new Point *[2*n], **BB = new Point *[2*n];
    hull(list2, n, AA, BB);

    cnt = 0;
    for (i = 0; A[i] != NIL; A[i++]->act()) {
      a[cnt] = A[i]->prev-P;
      b[cnt] = A[i]-P;
      c[cnt++] = A[i]->next-P;
    }
    for (i = 0; AA[i] != NIL; AA[i++]->act()) {
      a[cnt] = AA[i]->prev-Q;
      b[cnt] = AA[i]-Q;
      c[cnt++] = AA[i]->next-Q;
    }

    del();
    
    int m;
    scanf("%d", &m);
    while (m--) {
      Point p;
      scanf("%lf%lf%lf", &p.rx, &p.ry, &p.rz);
      double ans = INF;
      for (i = 0; i < cnt; i++)
        ans = min(ans, disPF(p, P[a[i]], crs(P[b[i]]-P[a[i]], P[c[i]]-P[a[i]])));
      printf("%.4lf\n", ans);
    }
  }
  return 0;
}
