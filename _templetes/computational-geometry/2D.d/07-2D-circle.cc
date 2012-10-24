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
