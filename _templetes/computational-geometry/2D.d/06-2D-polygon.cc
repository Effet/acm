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
    for (i=n-2,t=k+1; i>=0; r[k++]=p[i--])
        while (k>=t&&ccw(r[k-2],r[k-1],p[i])<=0) k--;
    for (delete r,n=k-1,i=0; i<n; i++)
        p[i] = r[i];
}

// 两凸多边形间最小距离，将min()函数改为max()为求最大距离
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
