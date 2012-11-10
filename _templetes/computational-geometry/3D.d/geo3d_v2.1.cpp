#include <iostream>
#include <valarray>
#include <vector>
#include <stdio.h>
#include <math.h>
using namespace std;

typedef double DB;
typedef valarray<DB> PT;

#define EPS (1e-8)
#define sig(x) ((x)<-EPS? -1: (x)>EPS? 1:0)
#define dot(a,b) ((a)*(b)).sum()
#define crs(a,b) (((a).cshift(+1)*(b).cshift(-1))     \
                  - ((a).cshift(-1)*(b).cshift(+1)))
#define box(o,a,b,c) dot(crs((a)-(o),(b)-(o)),(c)-(o))

#define len(p) sqrt(((p)*(p)).sum())
#define arg(a,b) (acos(dot((a),(b)))/len((a))/len((b)))


// distance from p to plane p0-n
DB disPF(PT p,PT o,PT n) {
  return fabs(dot(p-o, n)) / len(n);
}
// projection of p in plane p0-n
PT project(PT p, PT o, PT n) {
  DB t = dot(p-o, n) / len(n);
  return p + n*t;
}
PT crsLF(PT l, PT m, PT o, PT n) {
  DB t = dot(n, o-m) / dot(n, l-m);
  return m + (l-m)*t;
}

bool isPTri(PT p, PT a, PT b, PT c) {
  DB A = len(crs(a-p,b-p)), B = len(crs(b-p,c-p)), C = len(crs(c-p,a-p));
  return !sig(A + B + C - len(crs(b-a,c-a)));
}
bool isSTri(PT l, PT m, PT a, PT b, PT c, PT &p) {
  PT n = crs(b-a, c-a);
  if (!sig(dot(n, l-m))) return false;
  else {
    DB t = dot(n, a-m) / dot(n, l-m);
    if (sig(t) < 0 || sig(t-1) > 0) return false;
    p = m + (l-m)*t;
    return isPTri(p, a, b, c);
  }
}

DB disPL(PT p, PT l, PT m) {
  return len(crs(l-m, p-m)) / len(l-m);
}
DB disPS(PT p, PT s, PT t) {
  if (s == t) return len(p-s);
  PT v1 = s-t, v2 = p-s, v3 = p-t;
  if (sig(dot(v1,v2)) < 0) return len(v2);
  else if (sig(dot(v1,v3)) > 0) return len(v3);
  else return len(crs(v1, v2)) / len(v1);
}


// O(nlogn)
class ConvexHull3D {
private:
#define add push_back
  struct FT : vector<int> {
    FT(int a=-1, int b=-1, int c=-1) {
      add(a); add(b); add(c);
    }
  };
  vector<PT> ps;
  vector<FT> crt;
  vector<vector<int> > blg; // belong

#define ahead(x) {swap(ps[x],ps[i]); break;}
  bool getFirst() {
    int i,n = ps.size();
    for(i=1;i<n;i++) if(len(ps[0]-ps[i])!=0) ahead(1);
    for(i++;i<n;i++) if(len(crs(ps[1]-ps[0],ps[i]-ps[0]))!=0) ahead(2);
    for(i++;i<n;i++) if(box(ps[0],ps[1],ps[2],ps[i])!=0) ahead(3);
    return i < n;
  }
public:
  ConvexHull3D(vector<PT> ps): ps(ps) {}
  ConvexHull3D(PT *p = NULL, int n = 0) {
    ps.clear();
    for (int i=0; i<n; i++)
      ps[i] = p[i];
  }

#define outbox(i,f) (box(ps[f[0]],ps[f[1]],ps[f[2]],ps[i])>0)
#define put(a,b,c) {blg[a][b]=blg[b][c]=blg[c][a] \
      = crt.size(); crt.add(FT(a,b,c));}
  void dfs(int i, FT &g) {
    FT f = g;
    g[0] = -1;
    for (int k=0; k<3; k++) {
      int a=f[k],b=f[(k+1)%3],j=blg[b][a];
      if (~crt[j][0])
        if (outbox(i,crt[j])) dfs(i,crt[j]);
        else put(i,a,b);
    }
  }

  void hull() {
    crt.clear();
    if (!getFirst()) return ;

    int i,j,n=ps.size();
    blg.resize(n,vector<int>(n,-1));
    put(0,1,2);put(2,1,0);
    for (i=3; i<n; i++)
      for (j=0;j<crt.size();j++)
        if (~crt[j][0]&&outbox(i,crt[j])){dfs(i,crt[j]);break;}

    for (i=0; i<crt.size();i++)
      if (!~crt[i][0])
        crt.erase(crt.begin()+i--);
  }

  inline bool eq(FT f, FT g) {
    for (int i = 0; i < 3; i++)
      if (sig(box(ps[f[0]],ps[f[1]],ps[f[2]],ps[g[i]])))
        return false;
    return true;
  }

  // O(h^2)
  int face_num() {
    int i,j,r,f;
    for(r=i=0;i<crt.size();i++) {
      for(f=1,j=0;j<i;j++)
        if(eq(crt[i],crt[j])) {f=0; break;}
      r+=f;
    }
    return r;
  }

  DB face_area() {
    DB r = 0;
    for(int i = 0; i < crt.size(); i++) {
      FT &f = crt[i];
      r += fabs(len(crs(ps[f[1]]-ps[f[0]], ps[f[2]]-ps[f[0]])));
    }
    return r / 2;
  }

  DB min_dis(PT p) {
    DB ans = 1e12;
    for (int i=0; i<crt.size();i++) {
      FT &f = crt[i];
      ans = min(ans, disPF(p, ps[f[0]], crs(ps[f[1]]-ps[f[0]], ps[f[2]]-ps[f[0]])));
    }
    return ans;
  }
};


// O(n^2)
class ConvexHull3D_2 {
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
  ConvexHull3D_2(vector<PT> ps): ps(ps) {}
  ConvexHull3D_2(PT *p = NULL, int n = 0) {
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
  int n;
  while (scanf("%d", &n) != EOF) {
    vector<PT> p(n);
    for (int i = 0; i < n; i++) {
      DB v[3];
      scanf("%lf%lf%lf", &v[0], &v[1], &v[2]);
      p[i] = PT(v, 3);
    }
    ConvexHull3D P(p);
    P.hull();
    printf("%d\n", P.face_num());
  }
  return 0;
}


// ///////////////////////////////////////////////////////////////////////////
// Sphere Section
// ///////////////////////////////////////////////////////////////////////////

DB sphere_dist(DB R, DB lng1, DB lat1, DB lng2, DB lat2) {
  lng1 = lng1 * PI / 180;
  lat1 = lat1 * PI / 180;
  lng2 = lng2 * PI / 180;
  lat2 = lat2 * PI / 180;
  DB dlon = lng2 - lng1;
  DB dlat = lat2 - lat1;
  DB a = pow2(sin(dlat/2)) + cos(lat1) * cost(lat2) * pow2(sin(dlon/2));
  DB c = 2 * atan2(sqrt(a), sqrt(1-a));
  DB d = R * c;
  return d;
}
