#include "../2D.cc"

bool is_para(LI j, LI k) {return !sig(crs(j[0]-j[1], k[0]-k[1]));}
bool is_perp(LI j, LI k) {return !sig(dot(j[0]-j[1], k[0]-k[1]));}

bool isLP(LI l, PT p) {return !sig(crs(p-l[1], p-l[0]));}
bool isLL(LI l, LI m) {
    return abs(crs(l[1]-l[0], m[1]-m[0])) > EPS || // non-parallel
        abs(crs(l[1]-l[0], m[0]-m[1])) < EPS;      // same line
}
bool isLS(LI l, LI s) {
    return crs(l[1]-l[0], s[0]-l[0]) *
        crs(l[1]-l[0], s[1]-l[0]) < EPS;
}
bool isSP(LI s, PT p) {
    // triangle inequality
    return abs(s[0]-p)+abs(s[1]-p)-abs(s[1]-s[0]) < EPS;
}
bool isSS(LI s, LI t) {
    return ccw(s[0],s[1],t[0])*ccw(s[0],s[1],t[1]) <= 0 &&
        ccw(t[0],t[1],s[0])*ccw(t[0],t[1],s[1]) <= 0;
}
