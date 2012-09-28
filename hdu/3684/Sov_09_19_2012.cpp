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

    // bool  operator ==(const Point  &p) const {return sign(x-p.x) == 0 && sign(y-p.y) == 0;}
    bool  operator  <(const Point  &p) const {return x < p.x || x == p.x && y < p.y;}
    // bool  operator  <(const Point  &p) const {return sign(x-p.x) < 0 || sign(x-p.x) == 0 && sign(y-p.y) < 0;}

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
    // TODO: 须修改
    bool half_seg_intersect(Line s) {return s.seg_seg_intersect(Line(a, b+(b-a)*INF));}
    // 包括端点和部分重合 TODO:须修改
    bool seg_seg_intersect_in(Line s) {
        return (parallel(s)&&p_in_line(s.a) && (p_in_seg_in(s.a)||p_in_seg_in(s.b)||s.p_in_seg(a)||s.p_in_seg(b))) ||
            (!same_side(s.a, s.b)&&!s.same_side(a, b));
    }
    bool half_seg_intersect_in(Line s) {return s.seg_seg_intersect_in(Line(a, b+(b-a)*INF));}

    // 两直线交点 （保证不平行）
    Point intersection(Line l) {return a + (a-b) * (((a-b)^(a-l.a))/((a-b)^(l.a-l.b)));}

    // 点在线上映射（最近点） FIXME: 可能有错
    Point p_line(Point p) {return intersection(Line(p, p+Point(b.x-a.x, a.y-b.y)));}
    // 点到直线距离
    // Point p_dist(Point p) {return fabs(((a-p)^(b-p))) / (b-a).len();}

    void get() {a.get(); b.get();}
    void print() {cout << "Line:" << endl; cout << " `--"; a.print(); cout << " `--"; b.print();}
};


#define zero(x) (((x)>0?(x):-(x))<EPS)

//计算cross product (P1-P0)x(P2-P0)
double xmult(Point p1,Point p2,Point p0){
	return (p1.x-p0.x)*(p2.y-p0.y)-(p2.x-p0.x)*(p1.y-p0.y);
}
double xmult(double x1,double y1,double x2,double y2,double x0,double y0){
	return (x1-x0)*(y2-y0)-(x2-x0)*(y1-y0);
}

//判三点共线
int dots_inline(Point p1,Point p2,Point p3){
	return zero(xmult(p1,p2,p3));
}
int dots_inline(double x1,double y1,double x2,double y2,double x3,double y3){
	return zero(xmult(x1,y1,x2,y2,x3,y3));
}

//判点是否在线段上,包括端点
int dot_online_in(Point p,Line l){
	return zero(xmult(p,l.a,l.b))&&(l.a.x-p.x)*(l.b.x-p.x)<EPS&&(l.a.y-p.y)*(l.b.y-p.y)<EPS;
}
int dot_online_in(Point p,Point l1,Point l2){
	return zero(xmult(p,l1,l2))&&(l1.x-p.x)*(l2.x-p.x)<EPS&&(l1.y-p.y)*(l2.y-p.y)<EPS;
}
int dot_online_in(double x,double y,double x1,double y1,double x2,double y2){
	return zero(xmult(x,y,x1,y1,x2,y2))&&(x1-x)*(x2-x)<EPS&&(y1-y)*(y2-y)<EPS;
}

//判两点在线段同侧,点在线段上返回0
int same_side(Point p1,Point p2,Line l){
	return xmult(l.a,p1,l.b)*xmult(l.a,p2,l.b)>EPS;
}
int same_side(Point p1,Point p2,Point l1,Point l2){
	return xmult(l1,p1,l2)*xmult(l1,p2,l2)>EPS;
}

//判两点在线段异侧,点在线段上返回0
int opposite_side(Point p1,Point p2,Line l){
	return xmult(l.a,p1,l.b)*xmult(l.a,p2,l.b)<-EPS;
}
int opposite_side(Point p1,Point p2,Point l1,Point l2){
	return xmult(l1,p1,l2)*xmult(l1,p2,l2)<-EPS;
}


//判两线段相交,包括端点和部分重合
int intersect_in(Line u,Line v){
	if (!dots_inline(u.a,u.b,v.a)||!dots_inline(u.a,u.b,v.b))
		return !same_side(u.a,u.b,v)&&!same_side(v.a,v.b,u);
	return dot_online_in(u.a,v)||dot_online_in(u.b,v)||dot_online_in(v.a,u)||dot_online_in(v.b,u);
}
int intersect_in(Point u1,Point u2,Point v1,Point v2){
	if (!dots_inline(u1,u2,v1)||!dots_inline(u1,u2,v2))
		return !same_side(u1,u2,v1,v2)&&!same_side(v1,v2,u1,u2);
	return dot_online_in(u1,v1,v2)||dot_online_in(u2,v1,v2)||dot_online_in(v1,u1,u2)||dot_online_in(v2,u1,u2);
}

//计算两直线交点,注意事先判断直线是否平行!
//线段交点请另外判线段相交(同时还是要判断是否平行!)
Point intersection(Line u,Line v){
	Point ret=u.a;
	double t=((u.a.x-v.a.x)*(v.a.y-v.b.y)-(u.a.y-v.a.y)*(v.a.x-v.b.x))
        /((u.a.x-u.b.x)*(v.a.y-v.b.y)-(u.a.y-u.b.y)*(v.a.x-v.b.x));
	ret.x+=(u.b.x-u.a.x)*t;
	ret.y+=(u.b.y-u.a.y)*t;
	return ret;
}
Point intersection(Point u1,Point u2,Point v1,Point v2){
	Point ret=u1;
	double t=((u1.x-v1.x)*(v1.y-v2.y)-(u1.y-v1.y)*(v1.x-v2.x))
        /((u1.x-u2.x)*(v1.y-v2.y)-(u1.y-u2.y)*(v1.x-v2.x));
	ret.x+=(u2.x-u1.x)*t;
	ret.y+=(u2.y-u1.y)*t;
	return ret;
}




const int N = 100 + 10;
const int MAX_N = 1000 + 10;
const int MAX_M = 10000 + 10;

Point P[N][MAX_N];
Point p[MAX_N];
int cnt[N], low[N], hih[N];

Line L[MAX_M];
int hash[MAX_M], ans[MAX_M];

// 凸包模板
// http://www.algorithmist.com/index.php/Monotone_Chain_Convex_Hull
// vector<Point> convex_hull(vector<Point> P)
int convex_hull(int n, Point *P, Point *H)
{
	int k = 0;
    
	// Sort points lexicographically
	sort(P, P + n);

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

    return k;
}

int main(int argc, char *argv[])
{
    int t;
    scanf("%d", &t);
    while (t--)
    {
        int n;
        scanf("%d", &n);
        for (int i = 0; i < n; ++ i)
        {
            int q;
            scanf("%d", &q);
            for (int j = 0; j < q; ++ j) p[j].get();

            cnt[i] = convex_hull(q, p, P[i]) - 1;

            double y_min = INF, y_max = -INF;
            for (int j = 0; j < cnt[i]; ++ j) {
                if (y_min > P[i][j].y) {y_min = P[i][j].y; low[i] = j;}
                if (y_max < P[i][j].y) {y_max = P[i][j].y; hih[i] = j;}
            }
        }
        int m;
        scanf("%d", &m);
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
        
        sort(L, L + m);

        for (int i = 0; i < m; ++ i) hash[L[i].id] = i;
        for (int i = 0; i < m; ++ i) ans[i] = -1;
        for (int i = 0; i < m; ++ i)
        {
            double dis = INF;
            for (int j = 0; j < n; ++ j)
            {
                int h = hih[j], l = low[j], k = cnt[j];
                // cout << h << " " << l << " " << k << endl;
                while (sign((P[j][(h+1)%k] - P[j][h]) ^ (L[i].b - L[i].a)) > 0)
                    h = (h + 1) % k;
                while (sign((P[j][(l+1)%k] - P[j][l]) ^ (L[i].a - L[i].b)) > 0)
                    l = (l + 1) % k;
                hih[j] = h; low[j] = l;

                Line li(P[j][h], P[j][l]);

                // L[i].print();
                // cout << h << " " << l << endl;
                // li.print();
                // if (L[i].half_seg_intersect_in(li))
                if (intersect_in(L[i], li))
                {
                    // double _dis = (L[i].a - L[i].intersection(li)).len();
                    double _dis = (L[i].a - intersection(L[i], li)).len2();
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
