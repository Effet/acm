#include <cstdio>
#include <cmath>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

#define pow2(x) ((x)*(x))

const double EPS = 1e-6;
const double PI  = acos(-1.0);

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

struct Range {
    double th;
    int    t;
    bool   operator <(const Range &s) const {return sign(th - s.th) < 0 || (sign(th - s.th) == 0 && t > s.t);}
};


int main(int argc, char *argv[])
{
    int t;
    cin >> t;
    while (t--)
    {
        int n;
        cin >> n;
        vector<pair<Point, Point> > L(n);
        for (int i = 0; i < n; ++ i)
        {
            L[i].first.get();
            L[i].second.get();
        }
        Point o;
        o.get();

        vector<Range> S;
        
        int nc = 0;
        for (int j = 0; j < n; ++ j)
        {
            pair<Point, Point> ps = L[j];
            Point a = ps.first, b = ps.second;
            a = (a - o).e(); b = (b - o).e();
            int rd = sign(b ^ a);
            if (rd == 0 && sign(b * a) <= 0)
            {
                ++ nc;
                continue;
            }
            else if (rd < 0)
                swap(a, b);

            double jL = atan2(a.y, a.x), jR = atan2(b.y, b.x);
            
            if(sign(jR - jL) > 0) ++ nc;
            S.push_back((Range){jL, -1});
            S.push_back((Range){jR,  1});
        }
        sort(S.begin(), S.end());

        int ans = 0;
        double pj = - PI;
        for(int j = 0; j < S.size(); ++ j)
        {
            ans = max(ans, nc);
            nc += S[j].t;
        }
        ans = max(ans, nc);
        
        cout << ans << endl;
    }
    return 0;
}
