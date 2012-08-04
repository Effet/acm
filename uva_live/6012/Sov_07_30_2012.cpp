#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <limits>
#include <climits>
#include <vector>
#include <string>

using namespace std;

const double EPS = 1e-8;
const double PI  = acos(-1.0);
const int MAX_N = 100 + 10;

#define pow2(x) ((x)*(x))
#define point_dis(a,b) (sqrt(pow2(a.x-b.x)+pow2(a.y-b.y)))

struct Point {
	double x, y, r;
    int id;

	bool operator <(const Point &p) const {
		return x < p.x || (x == p.x && y < p.y);
	}
};

// 2D cross product of OA and OB vectors, i.e. z-component of their 3D cross product.
// Returns a positive value, if OAB makes a counter-clockwise turn,
// negative for clockwise turn, and zero if the points are collinear.
double cross(const Point &O, const Point &A, const Point &B)
{
	return (A.x - O.x) * (B.y - O.y) - (A.y - O.y) * (B.x - O.x);
}

// Returns a list of points on the convex hull in counter-clockwise order.
// Note: the last point in the returned list is the same as the first one.
vector<Point> convex_hull(vector<Point> P)
{
	int n = P.size(), k = 0;
	vector<Point> H(2*n);

	// Sort points lexicographically
	sort(P.begin(), P.end());

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

	H.resize(k);
	return H;
}


double circle_theta(Point o, Point a, Point b)
{
    double beta = atan2(b.y-o.y, b.x-o.x) - atan2(a.y-o.y, a.x-o.x);
    if (beta < 0)
        beta += 2.0 * PI;
    return beta;
}


double circle_theta_2(Point o, Point a, Point b)
{
    double beta = 2.0 * asin(point_dis(a, b) / (2.0 * point_dis(o, a)));
    if (cross(o, a, b) < 0)
        beta = 2.0 * PI - beta;
    return beta;
}


Point rotate(Point o, Point a, double beta, double scale)
{
    Point x;
    a.x -= o.x;
    a.y -= o.y;

    x.x = (a.x * cos(beta) - a.y * sin(beta)) * scale;
    x.y = (a.x * sin(beta) + a.y * cos(beta)) * scale;

    x.x += o.x;
    x.y += o.y;
    return x;
}


int main()
{
    int t;
    cin >> t;
    while (t--)
    {
        int n;
        cin >> n;
        vector<Point> C(n);
        for (int i = 0; i < n; ++ i)
            cin >> C[i].x >> C[i].y >> C[i].r;

        if (n == 1)
        {
            printf("%.5lf\n", 2*PI*C[0].r);
            continue;
        }

        vector<Point> P;
        for (int i = 0; i < n; ++ i)
        {
            for (int j = i + 1; j < n; ++ j)
            {
                double D = point_dis(C[i], C[j]);
                double R = abs(C[i].r-C[j].r);

                double alpha = acos(R/D);
                double beta = PI - alpha;

                if (C[i].r < C[j].r)
                    swap(alpha, beta);

                Point i1 = rotate(C[i], C[j], alpha, C[i].r/D);
                Point i2 = rotate(C[i], C[j], - alpha, C[i].r/D);

                Point j1 = rotate(C[j], C[i], beta, C[j].r/D);
                Point j2 = rotate(C[j], C[i], - beta, C[j].r/D);

                i1.id = i; P.push_back(i1);
                i2.id = i; P.push_back(i2);
                j1.id = j; P.push_back(j1);
                j2.id = j; P.push_back(j2);
            }
        }


        vector<Point> CH = convex_hull(P);

        
        double ans = 0;
        int m = CH.size() - 1;
        for (int i = 0; i < m; ++ i)
        {
            if (CH[i].id != CH[i+1].id)
                ans += point_dis(CH[i], CH[i+1]);
            else
                ans += C[CH[i].id].r * circle_theta(C[CH[i].id], CH[i], CH[i+1]);
        }
        printf("%.5lf\n", ans);
    }
    return 0;
}
