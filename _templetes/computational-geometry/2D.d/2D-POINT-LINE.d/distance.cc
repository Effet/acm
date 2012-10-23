#include "../2D.cc"

DB disLP(LI l, PT p) {
    // dis(high) = area / bottom
    return fabs(crs(l[0]-p,l[1]-p)) / abs(l[0]-l[1]);
}
DB disLL(LI l, LI m) {
    return !is_para(l,m) ? 0 : disLP(m,l[0]);
}
DB disLS(LI l, LI s) {
    return isLS(l,s) ? 0 : min(disLP(l,s[0]), disLP(l,s[1]));
}
DB disSP(LI s, PT p) {
    if (dot(s[1]-s[0],p-s[0]) > 0
        && dot(s[0]-s[1],p-s[1]) > 0) return disLP(s,p);
    else
        return min(abs(p-s[0]), abs(p-s[1]));
}
DB disSS(LI s, LI t) {
    if (isSS(s,t)) return 0;
    return min(min(disSP(s,t[0]),disSP(s,t[1])),
               min(disSP(t,s[0]),disSP(t,s[1])));
}
