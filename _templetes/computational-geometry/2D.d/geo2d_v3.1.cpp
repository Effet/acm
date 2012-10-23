#include <vector>
#include <complex>
#include <iostream>
#include <algorithm>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
using namespace std;

typedef double DB;
typedef complex<DB> PT;
struct LI : public vector<PT> {
    LI(PT a, PT b) {
        push_back(a); push_back(b);
    }
};
struct CR {
    PT o; DB r;
    CR(PT o, DB r=1.0): o(o), r(r) {}
};

const DB EPS=1e-8, PI=acos(-1.0), TAU=2*PI, INF=1e12;

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



// ///////////////////////////////////////////////////////////////////////////
// Point and Line/Segment Section
// ///////////////////////////////////////////////////////////////////////////


bool is_para(LI j, LI k) {return !sig(crs(j[0]-j[1], k[0]-k[1]));}
bool is_perp(LI j, LI k) {return !sig(dot(j[0]-j[1], k[0]-k[1]));}

bool isLP(LI l, PT p) {return !sig(crs(p-l[1], p-l[0]));}
bool isLL(LI l, LI m) {
    return abs(crs(l[1]-l[0], m[1]-m[0])) > EPS || // non-parallel
        abs(crs(l[1]-l[0], m[0]-m[1])) < EPS;      // same line
}
bool isLS(LI l, LI s) {
    return crs(l[1]-l[0], s[0]-l[0]) *
        crs(l[1]-l[0], s[1]-l[0]) < EPS;
}
bool isSP(LI s, PT p) {
    // triangle inequality
    return abs(s[0]-p)+abs(s[1]-p)-abs(s[1]-s[0]) < EPS;
}
bool isSS(LI s, LI t) {
    return ccw(s[0],s[1],t[0])*ccw(s[0],s[1],t[1]) <= 0 &&
        ccw(t[0],t[1],s[0])*ccw(t[0],t[1],s[1]) <= 0;
}


// Nearest point in line
PT project(PT p, LI l) {
    DB t = dot(p-l[0], l[1]-l[0]) / norm(l[1]-l[0]);
    return l[0] + t*(l[1]-l[0]);
}
// Mirorr point of line
PT reflect(PT p, LI l) {
    return p + 2.0 * (project(p, l) - p);
}


DB disLP(LI l, PT p) {
    // dis(high) = area / bottom
    return fabs(crs(l[0]-p,l[1]-p)) / abs(l[0]-l[1]);
}
DB disLL(LI l, LI m) {
    return !is_para(l,m) ? 0 : disLP(m,l[0]);
}
DB disLS(LI l, LI s) {
    return isLS(l,s) ? 0 : min(disLP(l,s[0]), disLP(l,s[1]));
}
DB disSP(LI s, PT p) {
    if (dot(s[1]-s[0],p-s[0]) > 0
        && dot(s[0]-s[1],p-s[1]) > 0) return disLP(s,p);
    else
        return min(abs(p-s[0]), abs(p-s[1]));
}
DB disSS(LI s, LI t) {
    if (isSS(s,t)) return 0;
    return min(min(disSP(s,t[0]),disSP(s,t[1])),
               min(disSP(t,s[0]),disSP(t,s[1])));
}


PT crsLL(LI l, LI m) {
    DB A = crs(l[1]-l[0], m[1]-m[0]);
    DB B = crs(l[1]-l[0], l[1]-m[0]);
    if (abs(A) < EPS && abs(B) < EPS) return m[0]; // same line
    if (abs(A) < EPS) assert(false);
    return m[0] + B / A * (m[1] - m[0]);
}


// ///////////////////////////////////////////////////////////////////////////
// Triangle Section
// ///////////////////////////////////////////////////////////////////////////

DB area_triangle(PT p1, PT p2, PT p3) {
	return fabs(crs(p2-p1,p3-p1)) / 2;
}
DB area_triangle(DB a, DB b, DB c){
	DB s=(a+b+c)/2;
	return sqrt(s*(s-a)*(s-b)*(s-c));
}

// Circumscribed circle(外心)
PT circumcenter(PT a, PT b, PT c) {
    PT ab=(a+b)/2.0, ac=(a+c)/2.0, ba=Rot(b-a,0.0,1.0), ca=Rot(c-a,0.0,1.0);
    return crsLL(LI(ab,ab+ba), LI(ac,ac+ca));
}
// PT circumcenter_1(PT a, PT b, PT c){
//     PT ret;
//     DB a1=b.x-a.x,b1=b.y-a.y,c1=(a1*a1+b1*b1)/2;
//     DB a2=c.x-a.x,b2=c.y-a.y,c2=(a2*a2+b2*b2)/2;
//     DB d=a1*b2-a2*b1;
//     ret.x=a.x+(c1*b2-c2*b1)/d;
//     ret.y=a.y+(a1*c2-a2*c1)/d;
//     return ret;
// }

// Inscribed circle(内心)
PT incenter(PT a, PT b, PT c) {
    DB t1 = (arg(b-c) + arg(a-c))/2;
    DB t2 = (arg(c-a) + arg(b-a))/2;
    return crsLL(LI(c, c+PT(cos(t1), sin(t1))),
                     LI(a, a+PT(cos(t2), sin(t2))));
}

// Altitude (高线/垂心)
PT perpencenter(PT a, PT b, PT c) {
    return crsLL(LI(c, c+Rot(b-a,0,1)),
                     LI(a, a+Rot(c-b,0,1)));
}

// Barycenter(重心)
// 到三角形三顶点距离的平方和最小的点
// 三角形内到三边距离之积最大的点
PT barycenter(PT a, PT b, PT c) {
    return crsLL(LI((a+b)/2.0, c), LI((a+c)/2.0, b));
}

// Equilateral triangle(等边三角形)
LI get_equil(PT a, PT b, PT c) {
    PT v=(b-a)*(sqrt(3.0)/2.0), m=(a+b)/2.0;
    return LI(c, m + (ccw(a, b, c)>0 ? Rot(v,0,-1): Rot(v,0,1)));
}
// 模拟退火算法参看 polygon 部分
PT fermat_point(PT a, PT b, PT c) {
    DB A = abs(b-c), B = abs(a-c), C = abs(a-b);
    // make edge C is largest, A is smallest
    if (B > C) swap(b, c), swap(B, C);
    if (A > C) swap(a, c), swap(A, C);
    // if (A > B) swap(a, b), swap(A, B);

    if (dot(a-c, b-c)/A/B <= -0.5)
        return c;

    return crsLL(get_equil(a, b, c),
                     get_equil(b, c, a));
}
DB fermat_dis(DB a, DB b, DB c) {
    if (a > c) swap(a, c);
    if (b > c) swap(b, c);
    if ((a*a + b*b - c*c) / (2*a*b) <= -0.5)
        return a+b;
    else {
        DB p = (a+b+c)/2, s = sqrt(s*(s-a)*(s-b)*(s-c));
        return sqrt((a*a+b*b+c*c + 4*sqrt(3.0)*s)/2);
    }
}


// ///////////////////////////////////////////////////////////////////////////
// Polygon Section
// ///////////////////////////////////////////////////////////////////////////


// barycenter of polygon (ccw or cw is ok)
PT barycenter(PT *p, int n) {
    PT c(0, 0); DB r = 0, t; // t is sum of area * 2
    p[n] = p[0];
    for (int i = 0; i < n; ++ i) {
        c = c + (p[i] + p[i+1]) * (t = crs(p[i],p[i+1]));
        r += t;
    }
    return c / (3 * r);
}

// Fermat point(费马点)
// total distance to every point is minimal.
DB all_dis(PT *p, int n, PT f) {
    DB r = 0;
    for (int i = 0; i < n; i++)
        r += abs(f-p[i]);
    return r;
}
PT fermat_point(PT *p, int n) {
    PT f(0,0), t;
    DB step = 0;
    for (int i = 0; i < n; i++)
        step+=fabs(real(p[i]))+fabs(imag(p[i])), f=f+p[i];
    f = f/(DB)n;
    while (step > 1e-10) {
        for (int i = -1; i <= 1; i++)
            for (int j = -1; j <= 1; j++) {
                PT t = f + PT(i,j)*step;
                if (all_dis(p,n,t) < all_dis(p,n,f))
                    f = t;
            }
        step /= 2;
    }
    return f;
}

// area of polygon (ccw or cw is ok)
DB polygon_area(PT *p, int n) {
    DB r = .0;
    p[n] = p[0];
    for (int i = 0; i < n; ++ i)
        r += crs(p[i], p[i+1]);
    return fabs(r) / 2.0;
}

// convex hull O(nlogn)
bool cmp_lex(PT a, PT b) {
    return !sig(real(a)-real(b))? imag(a)<imag(b) : real(a)<real(b);
}
void convex_hull(PT *p, int &n) {
    PT *r=new PT[n<<1];
    int i,t,k = 0;
    std::sort(p, p+n, cmp_lex);
    for (i=0; i<n; r[k++]=p[i++])
        while (k>=2&&ccw(r[k-2],r[k-1],p[i])<=0) k--;
    for (i=n-2,t=k+1; i>=0; i--)
        while (k>=t&&ccw(r[k-2],r[k-1],p[i])<=0) k--;
    for (delete r,n=k-1,i=0; i<n; i++)
        p[i] = r[i];
}

// The minimum distance between two convex polygons,
//   using rotating calipers.
// replace min() to max() can calculate maximum distance.
// p, q must be convex-hull and have same ccw or cw(?)
DB dispoly2_poly(PT *p, PT *q, int n, int m) {
    int i = 0, j = 0, tn = n, tm = m;
    for (int ti = 1; ti < n; ti++) if (imag(p[ti])<imag(p[i])) i = ti;
    for (int ti = 1; ti < m; ti++) if (imag(q[ti])>imag(q[j])) j = ti;
    DB r = abs(p[i] - q[j]);
    while (tn > 0 || tm > 0) {
        LI pl(p[i], p[(i+1)%n]), ql(q[j], q[(j+1)%m]);
        int dt = sig(crs(pl[1]-pl[0], ql[1]-ql[0]));

        if (dt <= 0) i=(i+1)%n, --tn;
        if (dt >= 0) j=(j+1)%m, --tm;

        if (dt < 0) r = min(r, disSP(pl, ql[0]));
        else if (dt > 0) r = min(r, disSP(ql, pl[0]));
        else r = min(r, disSS(pl, ql));
        // may not check intersect if two segments are parallel.
    }
    return r;
}

// TODO:test
bool inside_hull(PT *p, int n, PT p1) {
    int l = 0, r = n-1, m;
    while (r-l > 1) {
        m = (l+r)>>1;
        int d = ccw(p[l], p[m], p1);
        if (d == 0) break;
        else if (d < 0) r = m;
        else l = m;
    }
    if (r-l > 1) return (m-l>1) && isSP( LI(p[l], p[m]), p1);
    return ccw(p[l], p[r], p1) > 0;
}

// check if Point in simple polygon.
// 1: inside, 0: border, -1: outside
// TODO:test
int contains(PT *p, int n, PT p1) {
    int r = -1, i;
    for (p[n] = p[0], i = 0; i < n; i++) {
        PT a=p[i]-p1, b=p[i+1]-p1;
        if (imag(a) > imag(b)) std::swap(a, b);
        if (sig(imag(a))<=0 && sig(imag(b))>0 && sig(crs(a,b))>0)
            r = -r;
        if (sig(crs(a,b))<=0 && sig(dot(a,b))<=0) return 0;
    }
    return r;
}

// Cut Convex Hull O(n)
// left of L.a -> L.b
// TODO:test
void convex_cut(PT *p, int &n, LI L) {
    PT r[1001], v=L[1]-L[0];
    int rcnt=0, d, i;
    for (p[n]=p[0], i=0; i<n; i++) {
        if ((d=ccw(L[0],L[1],p[i])) >= 0)
            r[rcnt++] = p[i];
        if (d*ccw(L[0],L[1],p[i+1]) < 0)
            r[rcnt++] = crsLL(L, LI(p[i], p[i+1]));
    }
    for (n=rcnt,i=0; i<n; i++)
        p[i] = r[i];
}



// ///////////////////////////////////////////////////////////////////////////
// Circle Section
// ///////////////////////////////////////////////////////////////////////////


// Area of circular segment(弓形)
DB segment_area(DB r, DB th) {
    return pow2(r) * (th - sin(th)) / 2;
}


// concentric        (d = 0)             ----> 0: CO
// interior          (d < R - r)         ----> 1: IN
// interior tangents (d = R - r)         ----> 2: IN_TAN
// secants           (R - r < d < R + r) ----> 3: SEC
// exterior tangents (d = R + r)         ----> 4: EX_TAN
// exterior          (d > R + r)         ----> 5: EX
enum{CO, IN, IN_TAN, SEC, EX_TAN, EX};
int posi(CR j, CR k) {
    DB d=abs(j.o-k.o);
    if (sig(d)==0) return CO;
    int in=sig(d-fabs(j.r-k.r)), ex=sig(d-(j.r+k.r));
    return in<0? IN: !in? IN_TAN: !ex? EX_TAN: ex>0? EX: SEC;
}

bool isCL(CR c, LI l, bool border = false) {
    return sig(disLP(l,c.o) - c.r) < (border?-1:0);
}
bool isCS(CR c, LI s, bool border = true) {
    int d1 = sig(abs(c.o - s[0]) - c.r), d2 = sig(abs(c.o - s[1]) - c.r);
    if (d1 <= 0 && d2 <= 0)
        return border && (d1 == 0 || d2 == 0);
    return sig(disSP(s, c.o) - c.r) < (border?-1:0);
}

int crsCL(CR c, LI l, PT *p) {
    int d=sig(disLP(l,c.o)-c.r);
    if (d>0) return 0;
    else {
        PT pr=project(c.o,l), v=l[0]-l[1];
        if (!d) {p[0]=pr;return 1;}
        v=e(v) * sqrt(c.r*c.r - norm(c.o-pr));
        p[0]=pr+v; p[1]=pr-v;
        return 2;
    }
}

// -1 mean inf
int crsCC(CR j, CR k, PT *p) {
    int d=posi(j,k);
    if (d==IN || d==EX) return 0;
    if (d==CO && !sig(fabs(j.r-k.r))) return -1;

    if (d!=SEC) {
        p[0] = j.o + e(k.o-j.o, j.r);
        return 1;
    }

    PT v = k.o-j.o;
    DB co = (j.r*j.r + norm(v) - k.r*k.r) / (2 * j.r * abs(v));
    DB si = sqrt(fabs(1.0 - co*co));
    p[0] = j.o + e(Rot(v, co, -si), j.r);
    p[1] = j.o + e(Rot(v, co,  si), j.r);
    return 2;
}

// tangent(切线) of two circle
// return -1 mean inf tangents
// http://www.regentsprep.org/Regents/math/geometry/GP14/TanCircles.htm
//   -- to see more
// TODO:test
int tangent(CR j, CR k, LI *l) {
    int pos = posi(j, k);

    // concentric and same radii, has inf tangents
    if (pos == CO) {
        if (!sig(j.r-k.r)) return -1;
        // or ...
        else return 0;
    }

    // interior, 0 tangents
    if (pos == IN) return 0;
    // interior tangents, only 1 external tangent
    if (pos == IN_TAN)
        return 1;

    PT v = k.o-j.o;
    DB co, si;
    co = (j.r-k.r) / abs(v);
    si = sqrt(fabs(1.0-co*co));

    // rotate (co, si) and fix length to r
    l[0] = LI(j.o + e(Rot( v, co,-si),j.r),
              j.o + e(Rot( v, co, si),j.r));
    l[2] = LI(k.o + e(Rot(-v,-co,-si),k.r),
              k.o + e(Rot(-v,-co, si),k.r));

    // secants, only this 2 external tangents
    if (pos == SEC)
        return 2;

    // exterior tangent, 2 external tangents and 1 internal tangent
    if (pos == EX_TAN) {
        PT u = Rot(v,0,1);
        l[3] = LI(j.o + e(v,j.r), j.o + e(v,j.r) + u);
        return 3;
    }

    // exterior tangent, 2 external tangents and 2 internal tangents
    if (pos == EX) {
        co = (j.r + k.r) / abs(v);
        si = sqrt(1.0 - co*co);
        l[3] = LI(j.o + e(Rot( v, co,-si),j.r),
                  j.o + e(Rot( v, co, si),j.r));
        l[4] = LI(k.o + e(Rot(-v,-co,-si),k.r),
                  k.o + e(Rot(-v,-co, si),k.r));
        return 4;
    }
}


// http://www.darkswordzone.com/?p=1067
// minimum covering circle problem(最小圆覆盖)
// O(n) in random-implement.
inline bool out(PT &p, CR &c) {
    return abs(p-c.o)>c.r+EPS;
}
CR smallest_circle(PT *p, int n) {
    CR c(p[0], 0);
    random_shuffle(p, p+n);
    for (int i = 1; i < n; i++)
        if (out(p[i], c)) {
            c = CR(p[i], 0);
            for (int j = 0; j < i; j++) {
                if (out(p[j], c)) {
                    c.o = (p[i]+p[j])/2.0;
                    c.r = abs(p[j]-c.o);
                    for (int k = 0; k < j; k++)
                        if (out(p[k], c)) {
                            c.o = circumcenter(p[i], p[j], p[k]);
                            c.r = abs(p[i] - c.o);
                        }
                }
            }
        }
    return c;
}


// ///////////////////////////////////////////////////////////////////////////
// Common area Section
// ///////////////////////////////////////////////////////////////////////////

// signed area of intersection of circle(c.o, c.r) and
//  triangle(c.o, s.a, s.b) [cross(a-o, b-o)/2]
DB fix_acute(DB th) {return th<-PI ? th+TAU : th>PI ? th-TAU : th;}
DB area_cir_tri(CR c, LI s) {
    DB disoa = abs(c.o - s[0]), disob = abs(c.o - s[1]);

    // sector
    if (sig(disSP(s, c.o) - c.r) >= 0)
        return fix_acute(arg(s[1] - c.o) - arg(s[0] - c.o))
            * pow2(c.r) / 2.0;

    // triangle
    if (sig(disoa - c.r) <= 0 && sig(disob - c.r) <= 0)
        return crs(s[0]-c.o, s[1]-c.o) / 2.0;

    // three part: (A, a) (a, b) (b, B)
    PT rs[2];
    crsCL(c, s, rs);
    return area_cir_tri(c, LI(s[0], rs[0]))
        + area_cir_tri(c, LI(rs[0], rs[1]))
        + area_cir_tri(c, LI(rs[1], s[1]));
}
// common area of circle(c.o, c.r) and simple polyson(p[])
//  (ccw or cw is ok)
DB area_cir_poly(CR c, PT *p, int n) {
    DB res = .0;
    p[n] = p[0];
    for (int i = 0; i < n; ++ i)
        res += area_cir_tri(c, LI(p[i], p[(i+1)%n]));
    return fabs(res);
}


// ///////////////////////////////////////////////////////////////////////////
// Stream for input
// ///////////////////////////////////////////////////////////////////////////

// cin >> obj
istream& operator >>(istream &is, LI &s) {is >> s[0] >> s[1]; return is;}
istream& operator >>(istream &is, CR &c) {is >> c.o >> c.r; return is;}
// cout << obj
ostream& operator <<(ostream &os, LI &s) {os << "[" << s[0] << ", " << s[1] << "]"; return os;}
ostream& operator <<(ostream &os, CR &c) {os << "{" <<  c.o << ", " <<  c.r << "}"; return os;}


int main(int argc, char *argv[])
{
    cout << TAU << endl;
    cout << INF << endl;
    PT a, b, c;
    cin >> a >> b;
    cout << a << " " << b << endl;
    c = a + b;
    cout << c << endl;
    return 0;
}
