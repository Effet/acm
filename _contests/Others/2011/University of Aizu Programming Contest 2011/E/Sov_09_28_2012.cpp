#include <vector>
#include <complex>
#include <iostream>
#include <algorithm>
#include <cstdio>
using namespace std;

const double EPS = 1e-12;
const double PI  = acos(-1.0);
const double INF = 1e99;

double pow2(double x) {return x * x;}
int sign(double x) {return x < -EPS ? -1 : x > EPS ? 1 : 0;}


#define x real()
#define y imag()
typedef complex<double> Vector;
typedef complex<double> Point;
typedef vector<Point> Polygon;

class Segment {
public:
    Point p1, p2;
    Segment() {}
    Segment(const Segment &s) {p1 = s.p1; p2 = s.p2;}
    Segment(Point a, Point b) : p1(a), p2(b) {}
};

class Line : public Segment {
public:
    double a, b, c;
    Line() {}
    Line(Segment s) : Segment(s) {init_1();}
    Line(Point p1, Point p2) : Segment(p1, p2) {init_1();}
    Line(double a, double b, double c) : Segment() {init_2();}

    void init_1() {}
    void init_2() {}
};


bool cmp(const Point &a, const Point &b) {
    return a.x < b.x || (a.x == b.x && a.y < b.y);
}


// dot & cross product
double   dot(Vector v1, Vector v2) {return v1.x * v2.x + v1.y * v2.y;}
double cross(Vector v1, Vector v2) {return v1.x * v2.y - v1.y * v2.x;}
double   dot(Point o, Point a, Point b) {return dot(a-o, b-o);}
double cross(Point o, Point a, Point b) {return cross(a-o, b-o);}


Polygon convex_hull(Polygon &P)
{
	int n = P.size(), k = 0;
	Polygon H(2*n);
 
	// Sort points lexicographically
	sort(P.begin(), P.end(), cmp);
 
	// Build lower hull
	for (int i = 0; i < n; i++) {
		while (k >= 2 && cross(H[k-2], H[k-1], P[i]) <= 0) k--;
		H[k++] = P[i];
	}
 
	// Build upper hull
	for (int i = n-2, t = k+1; i >= 0; i--) {
		while (k >= t && cross(H[k-2], H[k-1], P[i]) <= 0) k--;
		H[k++] = P[i];
	}
 
	H.resize(k - 1);
	return H;
}


// distance
double dis(Point a, Point b) {return abs(a - b);}
double dis(Point p, Line l) {return fabs(cross(l.p1-p, l.p2-p)) / dis(l.p1, l.p2);}


// intersection point
Point intersection(Line l1, Line l2) { // ensure not rarallel
    return l1.p1 +
        (l1.p2-l1.p1) * (cross(l1.p1-l2.p2, l2.p1-l2.p2) /
                         cross(l1.p1-l1.p2, l2.p1-l2.p2));
}


// If Vector is complex number.
Vector rotate(Vector v, double co, double si) {return v * Vector(co, si);}
Vector rotate(Vector v, double th) {return v * polar(1.0, th);}
Point rotate(Point o, Point a, double co, double si) {return o + rotate(a-o, co, si);}
Point rotate(Point o, Point a, double th) {return o + rotate(a-o, th);}


int main(int argc, char *argv[])
{
    int N, R, Q;
    while (cin >> N >> R >> Q)
    {
        if (!N && !R && !Q)
            break;
        
        Polygon P(N);
        for (int i = 0; i < N; ++ i)
            cin >> P[i].x >> P[i].y;
        
        P = convex_hull(P);

        N = P.size();

        int start = 0;
        Point o(.0, .0);
        for (int i = 0; i < N; ++ i)
            if (norm(P[i]) == pow2(R)) {
                start = i; break;
            }

        while (Q --)
        {
            int nxt;
            double co, si;
            for (int i = 1; i < N; ++ i)
            {
                nxt = (start + i) % N;

                double _co = abs(P[nxt] - P[start]) / 2.0 / (R + .0);
                double _si = sqrt(1.0 - pow2(_co));

                Point v1 = rotate(P[start], o, _co, _si);

                co = dot(P[start], P[nxt], v1) / abs(P[nxt] - P[start]) / (R + .0);
                si = cross(P[start], P[nxt], v1) / abs(P[nxt] - P[start]) / (R + .0);

                bool flag = true;
                for (int j = i + 1; j < N; ++ j)
                    if (sign(norm(rotate(P[start], P[(start+j) % N], co, si)) - pow2(R)) > 0) {
                        flag = false; break;
                    }

                if (flag)
                    break;
            }
            for (int j = 1; j < N; ++ j)
                P[(start+j) % N] = rotate(P[start], P[(start+j) % N], co, si);

            printf("%.12lf %.12lf\n", P[nxt].x, P[nxt].y);

            start = nxt;
        }
    }
    return 0;
}
