#include <set>
#include <cmath>
#include <vector>
#include <iostream>
#include <algorithm>
#include <ctime>
#include <cstdio>
using namespace std;

#define EPS 1e-8
#define INF 1e99

typedef vector<struct Point> Points;
typedef vector<struct Plane> Planes;
typedef vector<int> Side;


int sign(double x) {return x < - EPS ? -1 : x > EPS ? 1 : 0;}


struct Point {
    double x, y, z;
    Point  operator -(const Point &p) const {return (Point){x-p.x, y-p.y, z-p.z};}
    Point  operator ^(const Point &p) const {return (Point){y*p.z - z*p.y, z*p.x - x*p.z, x*p.y - y*p.x};}
    double operator *(const Point &op) const {return x * op.x + y * op.y + z * op.z;}
    double length() {return sqrt(x*x + y*y + z*z + 0.0);}
};


struct Plane {
    Point  a, b, c;
    Point  normal() const { return (a - b) ^ (b - c); }
    double dist2p(const Point &p) {return fabs(normal()*(p - a)) / normal().length();}
    bool   same_side(const Point &p1, const Point &p2) {return normal()*(p1 - a) * (normal()*(p2 - a)) > EPS;}
};


vector<int> rnd;

Side getFirstSide(vector<Point> &p) {
	int i1 = 0;
	for (int i = 0; i < p.size(); ++i) {
		if (p[i].z < p[i1].z
            || p[i].z == p[i1].z && p[i].x < p[i1].x
            || p[i].z == p[i1].z && p[i].x == p[i1].x && p[i].y < p[i1].y) {
			i1 = i;
		}
	}
	int i2 = i1 == 0 ? 1 : 0;
	for (int i = 0; i < p.size(); ++i) {
		if (i != i1) {
			Point zDir = (Point){0, 0, 1};
			double curCos = (p[i] - p[i1]) * zDir / (p[i] - p[i1]).length();
			double bestCos = (p[i2] - p[i1]) * zDir / (p[i2] - p[i1]).length();
			if (curCos < bestCos) {
				i2 = i;
			}
		}
	}
	int i3 = -1;
	int n = p.size();
	for (int ri = 0; ri < n; ++ri) {
		int i = rnd[ri];
		if (i != i1 && i != i2) {
			Point norm = (p[i1] - p[i]) ^ (p[i2] - p[i]);
			bool sg[] = {0, 0, 0};
			for (int t = 0; t < n; ++t) {
				int j = rnd[t];
				sg[1 + sign((p[j] - p[i]) * norm)] = true;
				if (sg[0] && sg[2]) {
					break;
				}
			}
			if (sg[0] ^ sg[2]) {
				i3 = i;
				if (sg[0] == false) {
					swap(i3, i2);
				}
				break;
			}
		}
	}
	vector<int> res;
	res.push_back(i1);
	res.push_back(i2);
	res.push_back(i3);
	return res;
}

set<int> used;

int getSideKey(int i, int j, int k) {
	int key = (i * 1000 + j) * 1000 + k;
	return key;
}

bool checkUsed(int i, int j, int k) {
	int key = getSideKey(i, j, k);
	return used.find(key) != used.end();
}

void setUsed(int key) {
	used.insert(key);
}

double getAngle(const Point &n1, const Point &n2) {
	return atan2((n1 ^ n2).length(), n1 * n2);
}

double getNormsAngle(int i, int j, int k, int t, vector<Point> &p) {
	Point n1 = (p[j] - p[i]) ^ (p[k] - p[i]);
	Point n2 = (p[t] - p[i]) ^ (p[j] - p[i]);
	return getAngle(n1, n2);
}

void dfs(int i, int j, int k, vector<Point> &p, vector<Side> &sides) {
	if (i < j && i < k) {
		vector<int> side(3);
		side[0] = i;
		side[1] = j;
		side[2] = k;
		sides.push_back(side);
	}
	int key = getSideKey(i, j, k);
	setUsed(key);
	int n = p.size();
	if (!checkUsed(j, k, i)) {
		dfs(j, k, i, p, sides);
	}
	if (!checkUsed(k, i, j)) {
		dfs(k, i, j, p, sides);
	}
	int bestT = -1;
	double bestAngle = 1e20;
	Point curNorm = (p[j] - p[i]) ^ (p[k] - p[i]);
	Point dir = p[j] - p[i];
	for (int t = 0; t < n; ++t) {
		if (t != i && t != j && t != k) {
			Point newNorm = (p[t] - p[i]) ^ dir;
			double curAng = curNorm * newNorm / newNorm.length();
			if (bestT == -1 || curAng > bestAngle) {
				bestT = t;
				bestAngle = curAng;
			}
		}
	}
	if (!checkUsed(i, bestT, j)) {
		dfs(i, bestT, j, p, sides);
	}
}

vector<Side> ConvexHull_3D_nlogn(vector<Point> p) {
	int i, j, k;
	Side side0 = getFirstSide(p);
	vector<Side> sides;
	used.clear();
	dfs(side0[0], side0[1], side0[2], p, sides);
	return sides;
}


void solve(vector<Side> CH, Points &P)
{
    int m;
    scanf("%d", &m);
    while (m--)
    {
        Point p;
        scanf("%lf%lf%lf", &p.x, &p.y, &p.z);

        double ans = INF;

        for (int i = 0; i < CH.size(); ++ i)
        {
            Plane pl = (Plane){P[CH[i][0]], P[CH[i][1]], P[CH[i][2]]};
            ans = min(ans, pl.dist2p(p));
        }
        printf("%.4lf\n", ans);
    }
}

int main()
{
    int n;
    while (scanf("%d", &n) != EOF)
    {
        if (n == 0)
            break;
        
        vector<Point> P(n);
        for (int i = 0; i < n; i++)
            scanf("%lf%lf%lf", &P[i].x, &P[i].y, &P[i].z);
        
        rnd.resize(n);
        for (int i = 0; i < n; ++i) rnd[i] = i;
        random_shuffle(rnd.begin(), rnd.end());

        vector<Side> CH = ConvexHull_3D_nlogn(P);

        solve(CH, P);
    }
    
    return 0;
}
