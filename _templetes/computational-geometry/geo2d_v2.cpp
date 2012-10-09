#include <vector>
#include <complex>
#include <iostream>
#include <cstdio>
using namespace std;

const double EPS = 1e-8;
const double PI  = acos(-1.0);
const double TAU = 2.0 * PI;
const double INF = 1e99;

int sig(double x) {return x < -EPS ? -1 : x > EPS ? 1 : 0;}
template<class T> T pow2(T x) {return x * x;}


class Vector {
public:
    double x, y;
    Vector() {}
    Vector(double x, double y): x(x), y(y) {}
    
    Vector operator -() const {return Vector(-x, -y);}
    Vector operator +(const Vector &v) const {return Vector(x+v.x, y+v.y);}
    Vector operator -(const Vector &v) const {return Vector(x-v.x, y-v.y);}
    Vector operator *(const double &s) const {return Vector(x * s, y * s);}
    Vector operator /(const double &s) const {return Vector(x / s, y / s);}

    double operator *(const Vector &v) const {return x*v.x + y*v.y;}
    double operator ^(const Vector &v) const {return x*v.y - y*v.x;}

    // rotate vector (Right/Left hand)
    Vector  R(double co, double si) {return Vector(x*co-y*si, y*co+x*si);}
    Vector  L(double co, double si) {return Vector(x*co+y*si, y*co-x*si);}
    Vector  R(double th) {return R(cos(th), sin(th));}
    Vector  L(double th) {return L(cos(th), sin(th));}

    double len2() {return x*x + y*y;}
    double len()  {return sqrt(len2());}
    double ang()  {return atan2(y, x);}  // angle of vector
    Vector e(double s = 1.0) {return *this / len() * s;}
};
typedef Vector Point;
typedef vector<Point> Polygon;
// dot & cross product
double   dot(Point o, Point a, Point b) {return (a-o)*(b-o);}
double cross(Point o, Point a, Point b) {return (a-o)^(b-o);}


class Line {
public:
    Point a, b;
    Line() {}
    Line(Point a, Point b): a(a), b(b) {}
};
typedef Line Segment;
bool parallel(Line l1, Line l2) {return sig((l1.a-l1.b) ^ (l2.a-l2.b)) == 0;}
bool perpendicular(Line l1, Line l2) {return sig((l1.a-l1.b) * (l2.a-l2.b)) == 0;}



// ///////////////////////////////////////////////////////////////////////////
// Point and Line/Segment Section
// ///////////////////////////////////////////////////////////////////////////

// Nearest point in line
Point project(Point p, Line l) {
    Vector vl = l.b - l.a;
    return l.a + vl * ((p - l.a) * vl) / vl.len2();
}
// Mirorr point of line
Point reflect(Point p, Line l) {
    Vector vp = p - l.a, vl = l.b - l.a;
    return p + (vl * ((vp * vl) / vl.len2()) - vp) * 2.0;
}


// distance from point to line
double dis_p_li(Point p, Line l) {
    // dis(high) = area / bottom
    return fabs(cross(l.a, l.b, p)) / (l.a - l.b).len();
}
// distance from point to segment
double dis_p_seg(Point p, Segment s) {
    if (dot(s.a, s.b, p) > 0
        && dot(s.b, s.a, p) > 0) return dis_p_li(p, Line(s));
    else
        return min((p - s.a).len(), (p - s.b).len());
}
// distance between two line
double dis_li_li(Line l1, Line l2) {
    // if two line is cross, distance is 0
    return !parallel(l1, l2) ? .0 : dis_p_li(l1.a, l2);
}



// point-line
bool intersect_p_li(Point p, Line l) {
    // angle is zero
    return sig(cross(p, l.a, l.b)) == 0;
}
// point-segment
bool intersect_p_seg(Point p, Segment s, bool border = false) {
    // x < -1 means x <= 0)
    return sig(cross(p, s.a, s.b)) == 0 // inline
        && sig(dot(s.a, s.b, p)) > (border?-1:0) // right of p1
        && sig(dot(s.b, s.a, p)) > (border?-1:0); // left of p2
}
// segment-line
bool intersect_seg_li(Segment s, Line l, bool border = false) {
    return sig(cross(l.a, l.b, s.a)
                * cross(l.a, l.b, s.b)) > (border?-1:0);
}
bool intersect_seg_seg(Segment s1, Segment s2, bool border = false) {
    if (border && parallel(s1, s2)) // inline
        return intersect_p_seg(s1.a, s2, true)
            || intersect_p_seg(s1.b, s2, true)
            || intersect_p_seg(s2.a, s1, true)
            || intersect_p_seg(s2.b, s1, true);
    
    return intersect_seg_li(s1, Line(s2), border) &&
        intersect_seg_li(s2, Line(s1), border);
}
double dis_seg_seg(Segment s1, Segment s2) {
    if (intersect_seg_seg(s1, s2, true)) return .0;
    return min(
        min(dis_p_seg(s1.a, s2),
            dis_p_seg(s1.b, s2)),
        min(dis_p_seg(s2.a, s1),
            dis_p_seg(s2.b, s1))
        );
}

// cross point of two line
Point cross_li_li(Line l1, Line l2) { // ensure not rarallel
    return l1.a +
        (l1.b-l1.a) * (((l1.a-l2.b) ^ (l2.a-l2.b)) /
                       ((l1.a-l1.b) ^ (l2.a-l2.b)));
}


// ///////////////////////////////////////////////////////////////////////////
// Circle Section
// ///////////////////////////////////////////////////////////////////////////

class Circle {
public:
    Point o;
    double r;
    Circle() {}
    Circle(Point o, double r): o(o), r(r) {}
    
    // interior          (d < R - r)         ----> -2
    // interior tangents (d = R - r)         ----> -1
    // concentric        (d = 0)
    // secants           (R - r < d < R + r) ---->  0
    // exterior tangents (d = R + r)         ---->  1
    // exterior          (d > R + r)         ---->  2
    int posi(Circle c) {
        double d = (o - c.o).len();
        int in = sig(d - fabs(r - c.r)), ex = sig(d - (r + c.r));
        return in<0 ? -2 : in==0? -1 : ex==0 ? 1 : ex>0? 2 : 0;
    }

    // Ensure this->posi(c) = (-1, 1)
    Point touch(Circle c) {
        return (c.o - o).e(r);
    }

    // IMPORTANT: Ensure this->posi(c) = 0
    // chord(弦) of two circle
    // two points is ccw in *this circle
    Line chord(Circle c) {
        Vector v = c.o - o;
        double co = (pow2(r) + v.len2() - pow2(c.r)) / (2 * r * v.len());
        double si = sqrt(fabs(1.0 - pow2(co)));
        return Line(v.L(co, si).e(r) + o, v.R(co, si).e(r) + o);
    }

    // IMPORTANT: Ensure this->posi(c) = (0, 1, 2)
    // if interior is true, only this->posi(c) = 2
    // two points of interior/exterior tangents in this circle
    // two points is ccw in *this circle
    Line tangent_points(Circle c, bool interior = false) {
        Point  v = c.o - o;
        double co = (interior ? r+c.r : r-c.r) / v.len();
        double si = sqrt(1.0 - pow2(co));
        return Line(v.L(co, si).e(r) + o, v.R(co, si).e(r) + o);
    }

    // IMPORTANT: Ensure this->posi(c) = (0, 1, 2)
    // if interior is true, only this->posi(c) = 2
    // vector for tangents
    // two start points is ccw in *this circle
    Line tangent_vector(Circle c, bool interior = false) {
        Point v = c.o - o;
        double si = (interior ? r+c.r : r-c.r) / v.len();
        double co = sqrt(1.0 - pow2(si));
        return Line(v.R(co, si).e(), v.L(co, si).e());
    }

    
    // tangent(切线) of two circle
    // return -1 mean inf tangents
    int tangent(Circle c, Line *l) {
        // concentric and same radii, has inf tangents
        if (sig((o - c.o).len()) == 0 && sig(r - c.r) == 0) return -1;
        
        int pos = this->posi(c);
        // interior, 0 tangents
        if (pos == -2) return 0;
        // interior tangents, only 1 external tangent
        if (pos == -1)
            return 1;

        Vector v = c.o - o;
        double co, si;
        co = (r - c.r) / v.len();
        si = sqrt(1.0 - pow2(co));

        // rotate (co, si) and fix length to r
        l[0] = Line(o + v.L(co, si).e(r),
                    o + v.R(co, si).e(r));
        l[2] = Line(c.o + (-v).L(-co, si).e(c.r),
                    c.o + (-v).R(-co, si).e(c.r));

        // secants, only this 2 external tangents
        if (pos == 0)
            return 2;

        // exterior tangent, 2 external tangents and 1 internal tangent
        if (pos ==  1) {
            Vector u(v.y, -v.x);
            l[3] = Line(o + v.e(r), o + v.e(r) + u);
            return 3;
        }

        // exterior tangent, 2 external tangents and 2 internal tangents
        if (pos == 2) {
            co = (r + c.r) / v.len();
            si = sqrt(1.0 - pow2(co));
            l[3] = Line(o + v.L(co, si).e(r),
                        o + v.L(co, si).e(r));
            l[4] = Line(c.o + (-v).L(-co, si).e(c.r),
                        c.o + (-v).R(-co, si).e(c.r));
            return 4;
        }
    }
};


// Area of circular segment(弓形)
double segment_area(double r, double th) {
    return pow2(r) * (th - sin(th)) / 2;
}


bool intersect_cir_li(Circle c, Line l, bool border = false) {
    return sig(dis_p_li(c.o, l) - c.r) < (border?-1:0);
}
bool intersect_cir_seg(Circle c, Segment s, bool border = true) {
    int d1 = sig((c.o - s.a).len() - c.r), d2 = sig((c.o - s.b).len() - c.r);
    if (d1 <= 0 && d2 <= 0)
        return border && (d1 == 0 || d2 == 0);
    return sig(dis_p_seg(c.o, s) - c.r) < (border?-1:0);
}


// The segment which line intersect with circle
// Ensure intersect(Circle c, Line l) is true
Segment cross_cir_li(Circle c, Line l) {
    Point p = project(c.o, l);
    Vector v = l.a - l.b;
    v = v.e() * sqrt(pow2(c.r) - (c.o - p).len2());
    return  Segment(p + v, p - v);
}


// ///////////////////////////////////////////////////////////////////////////
// Triangle Section
// ///////////////////////////////////////////////////////////////////////////

double area_triangle(Point p1, Point p2, Point p3) {
	return fabs(cross(p1,p2,p3)) / 2;
}
double area_triangle(double a, double b, double c){
	double s=(a+b+c)/2;
	return sqrt(s*(s-a)*(s-b)*(s-c));
}


struct point{double x,y;};
struct line{point a,b;};

double dist(point p1,point p2){
	return sqrt((p1.x-p2.x)*(p1.x-p2.x)+(p1.y-p2.y)*(p1.y-p2.y));
}

point intersection(line u,line v){
	point ret=u.a;
	double t=((u.a.x-v.a.x)*(v.a.y-v.b.y)-(u.a.y-v.a.y)*(v.a.x-v.b.x))
        /((u.a.x-u.b.x)*(v.a.y-v.b.y)-(u.a.y-u.b.y)*(v.a.x-v.b.x));
	ret.x+=(u.b.x-u.a.x)*t;
	ret.y+=(u.b.y-u.a.y)*t;
	return ret;
}

//外心
point circumcenter(point a,point b,point c){
	line u,v;
	u.a.x=(a.x+b.x)/2;
	u.a.y=(a.y+b.y)/2;
	u.b.x=u.a.x-a.y+b.y;
	u.b.y=u.a.y+a.x-b.x;
	v.a.x=(a.x+c.x)/2;
	v.a.y=(a.y+c.y)/2;
	v.b.x=v.a.x-a.y+c.y;
	v.b.y=v.a.y+a.x-c.x;
	return intersection(u,v);
}

//内心
point incenter(point a,point b,point c){
	line u,v;
	double m,n;
	u.a=a;
	m=atan2(b.y-a.y,b.x-a.x);
	n=atan2(c.y-a.y,c.x-a.x);
	u.b.x=u.a.x+cos((m+n)/2);
	u.b.y=u.a.y+sin((m+n)/2);
	v.a=b;
	m=atan2(a.y-b.y,a.x-b.x);
	n=atan2(c.y-b.y,c.x-b.x);
	v.b.x=v.a.x+cos((m+n)/2);
	v.b.y=v.a.y+sin((m+n)/2);
	return intersection(u,v);
}

//垂心
point perpencenter(point a,point b,point c){
	line u,v;
	u.a=c;
	u.b.x=u.a.x-a.y+b.y;
	u.b.y=u.a.y+a.x-b.x;
	v.a=b;
	v.b.x=v.a.x-a.y+c.y;
	v.b.y=v.a.y+a.x-c.x;
	return intersection(u,v);
}

// barycenter of triangle
//
//重心
//到三角形三顶点距离的平方和最小的点
//三角形内到三边距离之积最大的点
Point barycenter(Point a, Point b, Point c) {
    return cross_li_li(Line((a+b)/2, c), Line((a+c)/2, b));
}

//费马点
//到三角形三顶点距离之和最小的点
point fermentpoint(point a,point b,point c){
	point u,v;
	double step=fabs(a.x)+fabs(a.y)+fabs(b.x)+fabs(b.y)+fabs(c.x)+fabs(c.y);
	int i,j,k;
	u.x=(a.x+b.x+c.x)/3;
	u.y=(a.y+b.y+c.y)/3;
	while (step>1e-10)
		for (k=0;k<10;step/=2,k++)
			for (i=-1;i<=1;i++)
				for (j=-1;j<=1;j++){
					v.x=u.x+step*i;
					v.y=u.y+step*j;
					if (dist(u,a)+dist(u,b)+dist(u,c)>dist(v,a)+dist(v,b)+dist(v,c))
						u=v;
				}
	return u;
}


// ///////////////////////////////////////////////////////////////////////////
// Polygon Section
// ///////////////////////////////////////////////////////////////////////////

// barycenter of polygon (ccw or cw is ok)
Point barycenter(Polygon P) {
    Point c(.0, .0); double r = .0, t; // t is sum of area * 2
    int n = P.size();
    for (int i = 0; i < n; ++ i) {
        c = c + (P[i] + P[(i+1)%n]) * (t = P[i] ^ P[(i+1)%n]);
        r += t;
    }
    return c / (3 * r);
}

// area of polygon (ccw or cw is ok)
double polygon_area(Polygon P) {
    double r = .0;
    int n = P.size();
    for (int i = 0; i < n; ++ i)
        r += (P[i] ^ P[(i+1)%n]);
    return fabs(r) / 2;
}



// ///////////////////////////////////////////////////////////////////////////
// Common area Section
// ///////////////////////////////////////////////////////////////////////////

// signed area of intersection of circle(c.o, c.r) and
//  triangle(c.o, s.a, s.b) [cross(a-o, b-o)/2]
double fix_acute(double th) {return th<-PI ? th+TAU : th>PI ? th-TAU : th;}
double area_cir_tri(Circle c, Segment s) {
    double disoa = (c.o - s.a).len(), disob = (c.o - s.b).len();
    
    // sector
    if (sig(dis_p_seg(c.o, s) - c.r) >= 0)
        return fix_acute((s.b - c.o).ang() - (s.a - c.o).ang())
            * pow2(c.r) / 2.0;

    // triangle
    if (sig(disoa - c.r) <= 0 && sig(disob - c.r) <= 0)
        return cross(c.o, s.a, s.b) / 2.0;

    // three part: (A, a) (a, b) (b, B)
    Segment rs = cross_cir_li(c, Line(s));
    return area_cir_tri(c, Segment(s.a, rs.a))
        + area_cir_tri(c, Segment(rs.a, rs.b))
        + area_cir_tri(c, Segment(rs.b, s.b));
}
// common area of circle(c.o, c.r) and simple polyson(p[])
//  (ccw or cw is ok)
double area_cir_polygon(Circle c, Polygon p) {
    double res = .0;
    int n = p.size();
    for (int i = 0; i < n; ++ i)
        res += area_cir_tri(c, Segment(p[i], p[(i+1)%n]));
    return fabs(res);
}


// ///////////////////////////////////////////////////////////////////////////
// Stream for input
// ///////////////////////////////////////////////////////////////////////////

// cin >> obj
istream& operator >>(istream &is, Vector  &p) {is >> p.x >> p.y; return is;}
istream& operator >>(istream &is, Segment &s) {is >> s.a >> s.b; return is;}
istream& operator >>(istream &is, Circle  &c) {is >> c.o >> c.r; return is;}
// cout << obj
ostream& operator <<(ostream &os, Vector  &p) {os << "(" << p.x << ","  << p.y << ")"; return os;}
ostream& operator <<(ostream &os, Segment &s) {os << "[" << s.a << ", " << s.b << "]"; return os;}
ostream& operator <<(ostream &os, Circle  &c) {os << "{" << c.o << ", " << c.r << "}"; return os;}


// int main(int argc, char *argv[])
// {
//     return 0;
// }
