#include "../2D.cc"

PT crsLL(LI l, LI m) {
    DB A = crs(l[1]-l[0], m[1]-m[0]);
    DB B = crs(l[1]-l[0], l[1]-m[0]);
    if (abs(A) < EPS && abs(B) < EPS) return m[0]; // same line
    if (abs(A) < EPS) assert(false);
    return m[0] + B / A * (m[1] - m[0]);
}
