#include <iostream>
#include <vector>
#include <valarray>
#include <stdio.h>
#include <math.h>
#include <string.h>
using namespace std;

typedef double DB;
typedef valarray<DB> PT;

const DB EPS = 1e-8;
int sig(DB x) {return x<-EPS? -1: x>EPS? 1: 0;}
DB len(PT p) {return sqrt((p*p).sum());}
DB dot(PT a, PT b) {return (a*b).sum();}
PT crs(PT a, PT b) {return (a.cshift(+1)*b.cshift(-1)
                            - a.cshift(-1)*b.cshift(+1));}
DB box(PT o, PT a, PT b, PT c) {return dot(crs(a-o, b-o), c-o);}


// O(n^2)
class ConvexHull3D {
private:
#define add push_back
  struct FT : vector<int> {
    FT(int a, int b, int c) {
      add(a); add(b); add(c);
    }
  };
  vector<PT> ps;
  vector<FT> crt;

#define ahead(x) {swap(ps[x],ps[i]); break;}
  bool getFirst() {
    int i,n=ps.size();
    for (i=1;i<n;i++) if (len(ps[0]-ps[i]) != 0) ahead(1);
    for (i++;i<n;i++) if (len(crs(ps[1]-ps[0],ps[i]-ps[0])) != 0) ahead(2);
    for (i++;i<n;i++) if (box(ps[0],ps[1],ps[2],ps[i]) != 0) ahead(3);
    return i < n;
  }
public:
  ConvexHull3D(vector<PT> ps): ps(ps) {}
  ConvexHull3D(PT *p = NULL, int n = 0) {
    ps.clear();
    for (int i=0; i<n; i++) ps.add(p[i]);
  }

  void get(PT p) {ps.add(p);}

  void hull() {
    crt.clear();
    if (!getFirst()) return ;
        
    crt.add(FT(0,1,2));
    crt.add(FT(2,1,0));

    int n = ps.size();
    vector<vector<int> > vs(n, vector<int>(n, 0));
    for (int i = 3; i < n; i++)
    {
      vector<FT> next;
      for (int j = 0; j < crt.size(); j++) {
        FT &f = crt[j];
        int v = box(ps[f[0]],ps[f[1]],ps[f[2]],ps[i])<0?-1:1;
        if (v < 0) next.add(f);

        for (int k = 0; k < 3; k++) {
          int a = f[k], b = f[(k+1)%3];
          if (vs[b][a] == 0) vs[a][b] = v;
          else {
            if (vs[b][a] != v)
              next.add(FT(v>0?a:b, v>0?b:a, i));
            vs[b][a] = 0;
          }
        }
      }
      crt = next;
    }
  }

  inline bool eq(FT f, FT g) {
    for (int i = 0; i < 3; i++)
      if (sig(box(ps[f[0]],ps[f[1]],ps[f[2]],ps[g[i]])))
        return false;
    return true;
  }

  int face_num() {
    int i,j,r,f;
    for(r=i=0;i<crt.size();i++) {
      for(f=1,j=0;j<i;j++)
        if(eq(crt[i],crt[j])) {f=0; break;}
      r+=f;
    }
    return r;
  }
};

int main(int argc, char *argv[])
{
  int n, i;
  while (scanf("%d", &n) != EOF) {
    vector<PT> p(n);
    for (i = 0; i < n; i++) {
      DB v[3];
      scanf("%lf%lf%lf", &v[0], &v[1], &v[2]);
      p[i] = PT(v, 3);
      // scanf("%lf%lf%lf", &p[i].x, &p[i].y, &p[i].z);
    }
    ConvexHull3D P(p);
    P.hull();
    printf("%d\n", P.face_num());
  }
  return 0;
}
