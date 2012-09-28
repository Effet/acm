#include <cstdio>
#include <cmath>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

#define pow2(x) ((x)*(x))

const double EPS = 1e-8;
const double PI = acos(-1.0);

int sign(double x) {return x < - EPS ? -1 : x > EPS ? 1 : 0;}

struct Point {
    double x, y;
    Point  operator +(const Point  &p) const {return (Point){x+p.x, y+p.y};}
    Point  operator -(const Point  &p) const {return (Point){x-p.x, y-p.y};}
    Point  operator *(const double &s) const {return (Point){x*s, y*s};}
    Point  operator /(const double &s) const {return (Point){x/s, y/s};}
    
    double operator ^(const Point  &p) const {return x*p.y - y*p.x;}
    double operator *(const Point  &p) const {return x*p.x + y*p.y;}
    
    double length2() {return x*x + y*y;}
    double length()  {return sqrt(length2());}
    Point  e()       {return (Point){x/length(), y/length()};}
    void   get()     {cin >> x >> y;}
};

struct Circle {
    Point  o;
    double r;

    double arc_area(double beta) {return 0.5 * pow2(r) * (beta - sin(beta));}

    // -1: 内含 (d < R - r), 内切 (d = R - r)
    //  0: 相交 (R - r < d < R + r)
    //  1: 外切 (d = R + r), 外离 (d > R + r)
    int rel(const Circle &c) const {
		double d = (o - c.o).length();
		if(sign(d - fabs(r - c.r)) <= 0 || sign(d) == 0)
            return -1;
		return sign(r + c.r - d) > 0 ? 0 : 1;
	}
    
    pair<Point, Point>
    union_pts(const Circle &c) const {
        Point v = c.o - o, v2, X;
        double cos_beta = (pow2(r) + v.length2() - pow2(c.r)) / (2 * r * v.length());
        v = v.e(); v2 = (Point){-v.y, v.x} * (r * sqrt(1.0 - pow2(cos_beta)));
        X = o + v * (r * cos_beta);
        return make_pair(X + v2, X - v2);
    }
    
    void get() {o.get(); cin >> r;}
};

struct Segment {
    double beta;
    int    t;
    Point  p;
    bool   operator <(const Segment &s) const {return sign(beta - s.beta) < 0;}
};


vector<double>
union_circle(vector<Circle> &C)
{
    int n = C.size();
    vector<double> area(n + 1, 0);
    for (int i = 0; i < n; ++ i)
    {
        Point pts = (Point){- C[i].r, 0} + C[i].o;

        vector<Segment> S(2);
        S[0] = (Segment){- PI,  1, pts};
        S[1] = (Segment){  PI, -1, pts};
        
        int nc = 0;
        
        for (int j = 0; j < n; ++ j)
        {
            if (j  == i) continue;
            
            int rd = C[i].rel(C[j]);
            if (rd ==  1) continue;
            if (rd == -1) {
                if(sign(C[j].r - C[i].r) > 0) {
                    S.push_back((Segment){- PI,  1, pts});
                    S.push_back((Segment){  PI, -1, pts});
                }
                continue;
            }

            pair<Point, Point> ps = C[i].union_pts(C[j]);
            Point a = ps.first - C[i].o, b = ps.second - C[i].o;
            double jL = atan2(a.y, a.x), jR = atan2(b.y, b.x) ;
            
            if(sign(jR - jL) > 0) ++ nc;
            S.push_back((Segment){jL, -1, ps.first});
            S.push_back((Segment){jR,  1, ps.second});
        }
        sort(S.begin(), S.end());

        double pj = - PI;
        Point  pp = pts;
        for(int j = 0; j < S.size(); ++ j)
        {
            double ts = C[i].arc_area(S[j].beta - pj) + (pp ^ S[j].p) * 0.5;

            area[nc] += ts;
            if(nc > 1)
                area[nc - 1] -= ts;
            
            nc += S[j].t;
            pj  = S[j].beta;
            pp  = S[j].p;
        }
    }
    return area;
}


int main(int argc, char *argv[])
{
    int n;
    while (cin >> n)
    {
        vector<Circle> C(n);
        
        for (int i = 0; i < n; ++ i)
            C[i].get();

        vector<double> v = union_circle(C);

        double odd = 0, evn = 0;
        for (int i = n; i >= 1; -- i)
            (i & 0x1 ? odd : evn) += v[i];

        printf("%.5lf %.5lf\n", odd, evn);
    }
    return 0;
}
