#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

const double EPS = 1e-8;
const double PI  = acos(-1.0);
const double INF = 1e99;

double  pow2(double x)  {return x * x;}
int     sign(double x)  {return x < -EPS ? -1 : x > EPS ? 1 : 0;}
// Fix angle in [0, 2*PI]
double fix_p(double th) {return th < 0 ? th + 2*PI : th;}
// Fix angle in [-PI, PI]
double   fix(double th) {return th < -PI ? th+2*PI : th > PI ? th-2*PI : th;}
double _acos(double th) {return th <= -1 ?      PI : th >= 1 ?       0 : acos(th);}
double _asin(double th) {return th <= -1 ?   -PI/2 : th >= 1 ?    PI/2 : asin(th);}


struct Point {
    double x, y;
    int id; // Used in Circle Convex Hull
    Point(){} Point(double x, double y) : x(x), y(y) {}

    Point  operator -() const {return Point(-x, -y);}
    Point  operator +(const Point  &p) const {return Point(x+p.x, y+p.y);}
    Point  operator -(const Point  &p) const {return Point(x-p.x, y-p.y);}
    Point  operator *(const double &s) const {return Point(x*s, y*s);}
    Point  operator /(const double &s) const {return Point(x/s, y/s);}

    double operator ^(const Point  &v) const {return x*v.y - y*v.x;}
    double operator *(const Point  &v) const {return x*v.x + y*v.y;}

    bool  operator  <(const Point  &p) const {return x < p.x || x == p.x && y < p.y;}

    // 向量平行/垂直
    bool      parallel(Point v) {return sign(*this^v) == 0;}
    bool perpendicular(Point v) {return sign(*this*v) == 0;}

    // rotate vector (Right/Left hand)
    Point  R(double th) {return Point(x*cos(th)-y*sin(th), x*sin(th)+y*cos(th));}
    Point  L(double th) {return R(2*PI - th);}

    double len2()  {return x*x + y*y;}
    double len()   {return sqrt(len2());}
    double ang()   {return atan2(y, x);}
    Point  e()     {return Point(x/len(), y/len());}
    // void   get()   {cin >> x >> y;}
    void   get()   {scanf("%lf%lf", &x, &y);}
    void   print() {cout << "Point: (" << x << ", " << y << ")" << endl;}
};

struct Line {
    Point a, b;
    int id;
    Line(){} Line(Point a, Point b) : a(a), b(b) {}

    bool operator <(const Line &l) const {return (b-a).ang() < (l.b-l.a).ang();}

    
    // 判点在直线/射线(a到b)/线段上
    bool p_in_line(Point p) {return sign((b-a) ^ (p-a)) == 0;}
    // 包括端点
    bool p_in_half_in(Point p) {return p_in_line(p) && sign((b-a)*(p-a)) >= 0;}
    bool p_in_seg_in(Point p) {return p_in_line(p) && sign((b-a)*(p-a)) >= 0 && sign((a-b)*(p-b)) >= 0;}
    // 不包括
    bool p_in_half(Point p) {return p_in_line(p) && sign((b-a)*(p-a)) > 0;}
    bool p_in_seg(Point p) {return p_in_line(p) && sign((b-a)*(p-a)) > 0 && sign((a-b)*(p-b)) > 0;}

    
    // 判两点在直线同侧/异侧 (点不在线上)
    bool     same_side(Point p1, Point p2) {return sign((b-a)^(p1-a)) * sign((b-a)^(p2-a)) > 0;}
    bool opposite_side(Point p1, Point p2) {return sign((b-a)^(p1-a)) * sign((b-a)^(p2-a)) < 0;}

    
    // 直线平行/垂直
    bool      parallel(Line l) {return (b-a).parallel(l.b-l.a);}
    bool perpendicular(Line l) {return (b-a).perpendicular(l.b-l.a);}

    
    // 线段/射线与线段相交 (不包括端点和部分重合)
    bool  seg_seg_intersect(Line s) {return opposite_side(s.a, s.b) && s.opposite_side(a, b);}
    // 包括端点和部分重合
    bool seg_seg_intersect_in(Line s) {
        if (p_in_line(s.a) && p_in_line(s.b))
            return p_in_seg_in(s.a) || p_in_seg_in(s.b) || s.p_in_seg_in(a) || s.p_in_seg_in(b);
        return !same_side(s.a, s.b) && !s.same_side(a, b);
    }

    
    // 两直线交点 (保证不平行)
    Point intersection(Line l) {return a + (b-a) * (((a-l.b)^(l.a-l.b))/((a-b)^(l.a-l.b)));}
    
    // 点在线上映射 (最近点) FIXME: 可能有错
    Point p_line(Point p) {return intersection(Line(p, p+Point(b.x-a.x, a.y-b.y)));}
    // 点到直线距离
    // Point p_dist(Point p) {return fabs(((a-p)^(b-p))) / (b-a).len();}

    void get() {a.get(); b.get();}
    void print() {cout << "Line:" << endl; cout << " `--"; a.print(); cout << " `--"; b.print();}
};


vector<Point> convex_hull(vector<Point> &P)
{
    int n = P.size(), k = 0;
    vector<Point> H(2*n);
    
	// Sort points lexicographically
	sort(P.begin(), P.end());

	// Build lower hull
	for (int i = 0; i < n; i++) {
        while (k >= 2 && sign((H[k-1]-H[k-2])^(P[i]-H[k-2])) <= 0) -- k;
		H[k++] = P[i];
	}

	// Build upper hull
	for (int i = n-2, t = k+1; i >= 0; i--) {
        while (k >= t && sign((H[k-1]-H[k-2])^(P[i]-H[k-2])) <= 0) -- k;
		H[k++] = P[i];
	}

    H.resize(k);
    return H;
}


int main(int argc, char *argv[])
{
    int t;
    scanf("%d", &t);
    while (t--)
    {
        int n;
        scanf("%d", &n);
        vector<vector<Point> > P(n);
        vector<int> low(n), hih(n);
        for (int i = 0; i < n; ++ i)
        {
            int q;
            scanf("%d", &q);
            vector<Point> p(q);
            for (int j = 0; j < q; ++ j) p[j].get();

            // cnt[i] = convex_hull(q, p, P[i]) - 1;
            P[i] = convex_hull(p);
            P[i].resize(P[i].size() - 1);

            double y_min = INF, y_max = -INF;
            // for (int j = 0; j < cnt[i]; ++ j) {
            for (int j = P[i].size() - 1; j >= 0; -- j) {
                if (y_min > P[i][j].y) {y_min = P[i][j].y; low[i] = j;}
                if (y_max < P[i][j].y) {y_max = P[i][j].y; hih[i] = j;}
            }
        }
        int m;
        scanf("%d", &m);
        vector<Line> L(m+8);
        for (int i = 0; i < m; ++ i) {
            L[i].get(); L[i].b = L[i].b * 10000000000.0 + L[i].a;
            L[i].id = i;
        }
        Point o(0, 0);
        int x[3] = {-1, 0, 1};
        for (int i = 0; i < 3; ++ i)
            for (int j = 0; j < 3; ++ j)
                if (x[i] != 0 || x[j] != 0)
                {
                    L[m] = Line(o, Point(x[i]+.0, x[j]+.0));
                    L[m].id = m;
                    ++ m;
                }

        
        sort(L.begin(), L.end());

        vector<int> hash(m), ans(m, -1);

        for (int i = 0; i < m; ++ i) hash[L[i].id] = i;
        // for (int i = 0; i < m; ++ i) ans[i] = -1;
        for (int i = 0; i < m; ++ i)
        {
            double dis = INF;
            for (int j = 0; j < n; ++ j)
            {
                int h = hih[j], l = low[j], k = P[j].size();
                while (sign((P[j][(h+1)%k] - P[j][h]) ^ (L[i].b - L[i].a)) > 0)
                    h = (h + 1) % k;
                while (sign((P[j][(l+1)%k] - P[j][l]) ^ (L[i].a - L[i].b)) > 0)
                    l = (l + 1) % k;
                hih[j] = h; low[j] = l;

                Line li(P[j][h], P[j][l]);

                if (L[i].seg_seg_intersect_in(li))
                {
                    double _dis = (L[i].a - L[i].intersection(li)).len();
                    if (dis > _dis)
                    {
                        dis = _dis;
                        ans[i] = j;
                    }
                }
            }
        }

        for (int i = 0; i < m - 8; ++ i)
        {
            int k = ans[hash[i]];
            if (k == -1)
                printf("MISS\n");
            else
                printf("HIT %d\n", k);
        }
        printf("*****\n");
    }
    return 0;
}
