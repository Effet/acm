#include <vector>
#include <complex>
#include <assert.h>
using namespace std;

typedef double DB;
typedef complex<DB> PT;
struct LI : public vector<PT> {
    LI(PT a, PT b) {push_back(a); push_back(b);}
};
struct CR {
    PT o; DB r;
    CR(PT o, DB r=1.0): o(o), r(r) {}
};

const DB EPS=1e-8,PI=acos(-1.0),TAU=2*PI,INF=1e12;

int sig(DB x) {return x<-EPS? -1 : x>EPS? 1 : 0;}
DB pow2(DB x) {return x * x;}

DB dot(PT a, PT b) {return real(conj(a)*b);}
DB crs(PT a, PT b) {return imag(conj(a)*b);}

PT Rot(PT v, DB co, DB si, DB s=1.0) {return v*PT(co,si)*s;}
PT Rot_a(PT v, DB t, DB s=1.0) {return v*polar(1.0, t)*s;}

PT e(PT v, DB s=1.0) {return v / abs(v) * s;}

int ccw(PT a, PT b, PT c) {
    b -= a; c -= a;
    if (crs(b, c) > 0)     return +1;       // counter clockwise
    if (crs(b, c) < 0)     return -1;       // clockwise
    if (dot(b, c) < 0)     return +2;       // c--a--b on line
    if (norm(b) < norm(c)) return -2;       // a--b--c on line
    return 0;
}
