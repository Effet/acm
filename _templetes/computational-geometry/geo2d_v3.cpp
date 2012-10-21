#include <vector>
#include <complex>
#include <iostream>
#include <algorithm>
#include <cstdio>
using namespace std;

typedef double DB;
const DB EPS=1e-8, PI=acos(-1.0), TAU=2*PI, INF=1e99;

int sig(DB x) {return x < -EPS ? -1 : x > EPS ? 1 : 0;}
template<class T> T pow2(T x) {return x * x;}


struct PT {
    DB x, y;
    PT(DB x=0, DB y=0): x(x), y(y) {}

    PT operator -() {return PT(-x, -y);}
    PT operator +(PT v) {return PT(x+v.x, y+v.y);}
    PT operator -(PT v) {return PT(x-v.x, y-v.y);}
    PT operator *(DB s) {return PT(x * s, y * s);}
    PT operator /(DB s) {return PT(x / s, y / s);}

    DB operator *(PT v) {return x*v.x + y*v.y;}
    DB operator ^(PT v) {return x*v.y - y*v.x;}

    // rotate vector (Right/Left hand)
    PT R(DB co, DB si) {return PT(x*co-y*si, y*co+x*si);}
    PT L(DB co, DB si) {return PT(x*co+y*si, y*co-x*si);}
    PT R(DB th) {return R(cos(th), sin(th));}
    PT L(DB th) {return L(cos(th), sin(th));}

    DB len2() {return x*x + y*y;}
    DB len() {return sqrt(len2());}
    DB ang() {return atan2(y, x);}  // angle of vector
    PT e(DB s=1) {return *this / len() * s;}
};
// dot & cross product
DB   dot(PT o, PT a, PT b) {return (a-o)*(b-o);}
DB cross(PT o, PT a, PT b) {return (a-o)^(b-o);}


struct LI {
    PT a, b;
    LI(PT a, PT b): a(a), b(b) {}
};

bool parallel(LI l1, LI l2) {
    return sig((l1.a-l1.b) ^ (l2.a-l2.b)) == 0;
}
bool perpendicular(LI l1, LI l2) {
    return sig((l1.a-l1.b) * (l2.a-l2.b)) == 0;
}



// ///////////////////////////////////////////////////////////////////////////
// Point and Line/Segment Section
// ///////////////////////////////////////////////////////////////////////////

// Nearest point in line
PT project(PT p, LI l) {
    PT vl = l.b - l.a;
    return l.a + vl * ((p - l.a) * vl) / vl.len2();
}
// Mirorr point of line
PT reflect(PT p, LI l) {
    PT vp = p - l.a, vl = l.b - l.a;
    return p + (vl * ((vp * vl) / vl.len2()) - vp) * 2.0;
}


// distance from point to line
DB dis_p_li(PT p, LI l) {
    // dis(high) = area / bottom
    return fabs(cross(l.a, l.b, p)) / (l.a - l.b).len();
}
// distance from point to segment
DB dis_p_seg(PT p, LI s) {
    if (dot(s.a, s.b, p) > 0
        && dot(s.b, s.a, p) > 0) return dis_p_li(p, s);
    else
        return min((p - s.a).len(), (p - s.b).len());
}
// distance between two line
DB dis_li_li(LI l1, LI l2) {
    // if two line is cross, distance is 0
    return !parallel(l1, l2) ? .0 : dis_p_li(l1.a, l2);
}


// point-line
bool intersect_p_li(PT p, LI l) {
    // angle is zero
    return sig(cross(p, l.a, l.b)) == 0;
}
// point-segment
bool intersect_p_seg(PT p, LI s, bool border = false) {
    // x > -1 means x >= 0)
    return sig(cross(p, s.a, s.b)) == 0 // inline
        && sig(dot(s.a, s.b, p)) > (border?-1:0) // right of p1
        && sig(dot(s.b, s.a, p)) > (border?-1:0); // left of p2
}
// segment-line
bool intersect_seg_li(LI s, LI l, bool border = false) {
    return sig(cross(l.a, l.b, s.a)
                * cross(l.a, l.b, s.b)) > (border?-1:0);
}
bool intersect_seg_seg(LI s1, LI s2, bool border = false) {
    if (border && parallel(s1, s2)) // inline
        return intersect_p_seg(s1.a, s2, true)
            || intersect_p_seg(s1.b, s2, true)
            || intersect_p_seg(s2.a, s1, true)
            || intersect_p_seg(s2.b, s1, true);

    return intersect_seg_li(s1, s2, border) &&
        intersect_seg_li(s2, s1, border);
}
DB dis_seg_seg(LI s1, LI s2) {
    if (intersect_seg_seg(s1, s2, true)) return .0;
    return min(
        min(dis_p_seg(s1.a, s2),
            dis_p_seg(s1.b, s2)),
        min(dis_p_seg(s2.a, s1),
            dis_p_seg(s2.b, s1))
        );
}

// cross point of two line
PT cross_li_li(LI l1, LI l2) { // ensure not rarallel
    return l1.a +
        (l1.b-l1.a) * (((l1.a-l2.b) ^ (l2.a-l2.b)) /
                       ((l1.a-l1.b) ^ (l2.a-l2.b)));
}



// ///////////////////////////////////////////////////////////////////////////
// Triangle Section
// ///////////////////////////////////////////////////////////////////////////

DB area_triangle(PT p1, PT p2, PT p3) {
	return fabs(cross(p1,p2,p3)) / 2;
}
DB area_triangle(DB a, DB b, DB c){
	DB s=(a+b+c)/2;
	return sqrt(s*(s-a)*(s-b)*(s-c));
}

// Circumscribed circle(外心)
PT circumcenter(PT a, PT b, PT c) {
    PT ab=(a+b)/2, ac=(a+c)/2, ba=(b-a).R(0,1), ca=(c-a).R(0,1);
    return cross_li_li(LI(ab,ab+ba), LI(ac,ac+ca));
}
PT circumcenter_1(PT a, PT b, PT c){
    PT ret;
    DB a1=b.x-a.x,b1=b.y-a.y,c1=(a1*a1+b1*b1)/2;
    DB a2=c.x-a.x,b2=c.y-a.y,c2=(a2*a2+b2*b2)/2;
    DB d=a1*b2-a2*b1;
    ret.x=a.x+(c1*b2-c2*b1)/d;
    ret.y=a.y+(a1*c2-a2*c1)/d;
    return ret;
}

// Inscribed circle(内心)
PT incenter(PT a, PT b, PT c) {
    DB t1 = ((b-c).ang() + (a-c).ang())/2;
    DB t2 = ((c-a).ang() + (b-a).ang())/2;
    return cross_li_li(LI(c, c+PT(cos(t1), sin(t1))),
                       LI(a, a+PT(cos(t2), sin(t2))));
    // return cross_li_li(LI(c, (a-c).R(((b-c).ang() - (a-c).ang())/2) + c),
    //                    LI(a, (b-a).R(((c-a).ang() - (b-a).ang())/2) + a));
}

// Altitude (高线/垂心)
PT perpencenter(PT a, PT b, PT c) {
    return cross_li_li(LI(c, c+(b-a).R(0,1)),
                       LI(a, a+(c-b).R(0,1)));
}

// Barycenter(重心)
// 到三角形三顶点距离的平方和最小的点
// 三角形内到三边距离之积最大的点
PT barycenter(PT a, PT b, PT c) {
    return cross_li_li(LI((a+b)/2, c), LI((a+c)/2, b));
}

// Equilateral triangle(等边三角形)
LI get_equil(PT a, PT b, PT c) {
    PT v=(b-a)*(sqrt(3.0)/2), m=(a+b)/2;
    return LI(c, m + (cross(a, b, c)>0 ? v.L(0,1): v.R(0,1)));
}
// 模拟退火算法参看 polygon 部分
PT fermat_point(PT a, PT b, PT c) {
    DB A = (b-c).len(), B = (a-c).len(), C = (a-b).len();
    // make edge C is largest, A is smallest
    if (B > C) swap(b, c), swap(B, C);
    if (A > C) swap(a, c), swap(A, C);
    // if (A > B) swap(a, b), swap(A, B);

    if (dot(c, a, b)/A/B <= -0.5)
        return c;
    
    return cross_li_li(get_equil(a, b, c),
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

typedef vector<PT> PG;

// barycenter of polygon (ccw or cw is ok)
PT barycenter(PG P) {
    PT c(0, 0); DB r = 0, t; // t is sum of area * 2
    int n = P.size();
    for (int i = 0; i < n; ++ i) {
        c = c + (P[i] + P[(i+1)%n]) * (t = P[i] ^ P[(i+1)%n]);
        r += t;
    }
    return c / (3 * r);
}

// Fermat point(费马点)
// total distance to every point is minimal.
DB all_dis(PT *p, int n, PT f) {
    DB r = 0;
    for (int i = 0; i < n; i++)
        r += (f-p[i]).len();
    return r;
}
PT fermat_point(PT *p, int n) {
	PT f(0,0), t;
    DB step = 0;
    for (int i = 0; i < n; i++)
        step+=fabs(p[i].x)+fabs(p[i].y), f=f+p[i];
    f = f/n;
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
DB polygon_area(PG P) {
    DB r = .0;
    int n = P.size();
    for (int i = 0; i < n; ++ i)
        r += (P[i] ^ P[(i+1)%n]);
    return fabs(r) / 2;
}

// The minimum distance between two convex polygons,
//   using rotating calipers.
// p, q must be convex-hull and have same ccw or cw(?)
DB dis_poly2_poly(PT *p, PT *q, int n, int m) {
    int i = 0, j = 0, tn = n, tm = m;
    for (int ti = 1; ti < n; ti++) if (p[ti].y<p[i].y) i = ti;
    for (int ti = 1; ti < m; ti++) if (q[ti].y>q[j].y) j = ti;
    DB r = (p[i] - q[j]).len();
    while (tn > 0 || tm > 0) {
        LI pl(p[i], p[(i+1)%n]), ql(q[j], q[(j+1)%m]);
        int dt = sig((pl.b-pl.a) ^ (ql.b-ql.a));

        if (dt <= 0) i=(i+1)%n, --tn;
        if (dt >= 0) j=(j+1)%m, --tm;

        if (dt < 0) r = min(r, dis_p_seg(ql.a, pl));
        else if (dt > 0) r = min(r, dis_p_seg(pl.a, ql));
        else r = min(r, dis_seg_seg(pl, ql));
        // may not check intersect if two segments are parallel.
    }
    return r;
}

// TODO:test
bool inside_hull(PT *p, int n, PT p1) {
    int l = 0, r = n-1, m;
    while (r-l > 1) {
        m = (l+r)>>1;
        int d = sig(cross(p[l], p[m], p1));
        if (d == 0) break;
        else if (d < 0) r = m;
        else l = m;
    }
    if (r-l > 1) return (m-l>1) && intersect_p_seg(p1, LI(p[l], p[m]));
    return sig(cross(p[l], p[r], p1)) > 0;
}

// ///////////////////////////////////////////////////////////////////////////
// Circle Section
// ///////////////////////////////////////////////////////////////////////////

struct CR {
    PT o; DB r;
    CR(PT o, DB r=1): o(o), r(r) {}

    // interior          (d < R - r)         ----> -2
    // interior tangents (d = R - r)         ----> -1
    // concentric        (d = 0)
    // secants           (R - r < d < R + r) ---->  0
    // exterior tangents (d = R + r)         ---->  1
    // exterior          (d > R + r)         ---->  2
    int posi(CR c) {
        DB d = (o - c.o).len();
        int in = sig(d - fabs(r - c.r)), ex = sig(d - (r + c.r));
        return in<0 ? -2 : in==0? -1 : ex==0 ? 1 : ex>0? 2 : 0;
    }

    // Ensure this->posi(c) = (-1, 1)
    PT touch(CR c) {
        return (c.o - o).e(r);
    }

    // IMPORTANT: Ensure this->posi(c) = 0
    // chord(弦) of two circle
    // two points is ccw in *this circle
    LI chord(CR c) {
        PT v = c.o - o;
        DB co = (pow2(r) + v.len2() - pow2(c.r)) / (2 * r * v.len());
        DB si = sqrt(fabs(1.0 - pow2(co)));
        return LI(v.L(co, si).e(r) + o, v.R(co, si).e(r) + o);
    }

    // IMPORTANT: Ensure this->posi(c) = (0, 1, 2)
    // if interior is true, only this->posi(c) = 2
    // two points of interior/exterior tangents in this circle
    // two points is ccw in *this circle
    LI tangent_points(CR c, bool interior = false) {
        PT  v = c.o - o;
        DB co = (interior ? r+c.r : r-c.r) / v.len();
        DB si = sqrt(1.0 - pow2(co));
        return LI(v.L(co, si).e(r) + o, v.R(co, si).e(r) + o);
    }

    // IMPORTANT: Ensure this->posi(c) = (0, 1, 2)
    // if interior is true, only this->posi(c) = 2
    // vector for tangents
    // two start points is ccw in *this circle
    LI tangent_vector(CR c, bool interior = false) {
        PT v = c.o - o;
        DB si = (interior ? r+c.r : r-c.r) / v.len();
        DB co = sqrt(1.0 - pow2(si));
        return LI(v.R(co, si).e(), v.L(co, si).e());
    }


    // tangent(切线) of two circle
    // return -1 mean inf tangents
    // http://www.regentsprep.org/Regents/math/geometry/GP14/TanCircles.htm
    //   -- to see more
    int tangent(CR c, LI *l) {
        // concentric and same radii, has inf tangents
        if (sig((o - c.o).len()) == 0 && sig(r - c.r) == 0) return -1;

        int pos = this->posi(c);
        // interior, 0 tangents
        if (pos == -2) return 0;
        // interior tangents, only 1 external tangent
        if (pos == -1)
            return 1;

        PT v = c.o - o;
        DB co, si;
        co = (r - c.r) / v.len();
        si = sqrt(1.0 - pow2(co));

        // rotate (co, si) and fix length to r
        l[0] = LI(o + v.L(co, si).e(r),
                  o + v.R(co, si).e(r));
        l[2] = LI(c.o + (-v).L(-co, si).e(c.r),
                  c.o + (-v).R(-co, si).e(c.r));

        // secants, only this 2 external tangents
        if (pos == 0)
            return 2;

        // exterior tangent, 2 external tangents and 1 internal tangent
        if (pos ==  1) {
            PT u(v.y, -v.x);
            l[3] = LI(o + v.e(r), o + v.e(r) + u);
            return 3;
        }

        // exterior tangent, 2 external tangents and 2 internal tangents
        if (pos == 2) {
            co = (r + c.r) / v.len();
            si = sqrt(1.0 - pow2(co));
            l[3] = LI(o + v.L(co, si).e(r),
                      o + v.L(co, si).e(r));
            l[4] = LI(c.o + (-v).L(-co, si).e(c.r),
                      c.o + (-v).R(-co, si).e(c.r));
            return 4;
        }
    }
};


// Area of circular segment(弓形)
DB segment_area(DB r, DB th) {
    return pow2(r) * (th - sin(th)) / 2;
}


bool intersect_cir_li(CR c, LI l, bool border = false) {
    return sig(dis_p_li(c.o, l) - c.r) < (border?-1:0);
}
bool intersect_cir_seg(CR c, LI s, bool border = true) {
    int d1 = sig((c.o - s.a).len() - c.r), d2 = sig((c.o - s.b).len() - c.r);
    if (d1 <= 0 && d2 <= 0)
        return border && (d1 == 0 || d2 == 0);
    return sig(dis_p_seg(c.o, s) - c.r) < (border?-1:0);
}


// The segment which line intersect with circle
// Ensure intersect(Circle c, Line l) is true
LI cross_cir_li(CR c, LI l) {
    PT p = project(c.o, l);
    PT v = l.a - l.b;
    v = v.e() * sqrt(pow2(c.r) - (c.o - p).len2());
    return  LI(p + v, p - v);
}


// http://www.darkswordzone.com/?p=1067
// minimum covering circle problem(最小圆覆盖)
// O(n) in random-implement.
inline bool out(PT p, CR c) {
    return (p-c.o).len()>c.r+EPS;
}
CR smallest_circle(PT *p, int n) {
    CR c(p[0], 0);
    random_shuffle(p, p+n);
    for (int i = 1; i < n; i++)
        if (out(p[i], c)) {
            c = CR(p[i], 0);
            for (int j = 0; j < i; j++) {
                if (out(p[j], c)) {
                    c.o = (p[i]+p[j])/2;
                    c.r = (p[j]-c.o).len();
                    for (int k = 0; k < j; k++)
                        if (out(p[k], c)) {
                            c.o = circumcenter(p[i], p[j], p[k]);
                            c.r = (p[i] - c.o).len();
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
    DB disoa = (c.o - s.a).len(), disob = (c.o - s.b).len();

    // sector
    if (sig(dis_p_seg(c.o, s) - c.r) >= 0)
        return fix_acute((s.b - c.o).ang() - (s.a - c.o).ang())
            * pow2(c.r) / 2.0;

    // triangle
    if (sig(disoa - c.r) <= 0 && sig(disob - c.r) <= 0)
        return cross(c.o, s.a, s.b) / 2.0;

    // three part: (A, a) (a, b) (b, B)
    LI rs = cross_cir_li(c, s);
    return area_cir_tri(c, LI(s.a, rs.a))
        + area_cir_tri(c, LI(rs.a, rs.b))
        + area_cir_tri(c, LI(rs.b, s.b));
}
// common area of circle(c.o, c.r) and simple polyson(p[])
//  (ccw or cw is ok)
DB area_cir_polygon(CR c, PG p) {
    DB res = .0;
    int n = p.size();
    for (int i = 0; i < n; ++ i)
        res += area_cir_tri(c, LI(p[i], p[(i+1)%n]));
    return fabs(res);
}


// ///////////////////////////////////////////////////////////////////////////
// Stream for input
// ///////////////////////////////////////////////////////////////////////////

// cin >> obj
istream& operator >>(istream &is, PT &p) {is >> p.x >> p.y; return is;}
istream& operator >>(istream &is, LI &s) {is >> s.a >> s.b; return is;}
istream& operator >>(istream &is, CR &c) {is >> c.o >> c.r; return is;}
// cout << obj
ostream& operator <<(ostream &os, PT &p) {os << "(" << p.x << ","  << p.y << ")"; return os;}
ostream& operator <<(ostream &os, LI &s) {os << "[" << s.a << ", " << s.b << "]"; return os;}
ostream& operator <<(ostream &os, CR &c) {os << "{" << c.o << ", " << c.r << "}"; return os;}


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
