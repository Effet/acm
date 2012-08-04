#include <cmath>

// Way-1
// 圆心o，原上两点a，b，求a逆时针到b的弧度。
// 弧长可由 弧度×半径
double circle_theta(Point o, Point a, Point b)
{
    double beta = atan2(b.y-o.y, b.x-o.x) - atan2(a.y-o.y, a.x-o.x);
    if (beta < 0)
        beta += 2.0 * PI;
    return beta;
}


// Way-2
#define pow2(x) ((x)*(x))
#define point_dis(a,b) (sqrt(pow2(a.x-b.x)+pow2(a.y-b.y)))

double cross(const Point &O, const Point &A, const Point &B)
{
	return (A.x - O.x) * (B.y - O.y) - (A.y - O.y) * (B.x - O.x);
}
// 弦长/直径 = sin(beta)  [边为直径的三角形为直角三角形]
// 根据矢量积判断角度是否大于PI。
double circle_theta_2(Point o, Point a, Point b)
{
    double beta = 2.0 * asin(point_dis(a, b) / (2.0 * point_dis(o, a)));
    if (cross(o, a, b) < 0)
        beta = 2.0 * PI - beta;
    return beta;
}
