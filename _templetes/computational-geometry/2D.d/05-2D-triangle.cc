DB area_triangle(PT p1, PT p2, PT p3) {
	return fabs(crs(p2-p1,p3-p1)) / 2;
}
DB area_triangle(DB a, DB b, DB c){
	DB s=(a+b+c)/2;
	return sqrt(s*(s-a)*(s-b)*(s-c));
}

// Circumscribed circle(外心)
PT circumcenter(PT a, PT b, PT c) {
    PT ab=(a+b)/2.0, ac=(a+c)/2.0, ba=Rot(b-a,0.0,1.0), ca=Rot(c-a,0.0,1.0);
    return crsLL(LI(ab,ab+ba), LI(ac,ac+ca));
}
// PT circumcenter_1(PT a, PT b, PT c){
//     PT ret;
//     DB a1=b.x-a.x,b1=b.y-a.y,c1=(a1*a1+b1*b1)/2;
//     DB a2=c.x-a.x,b2=c.y-a.y,c2=(a2*a2+b2*b2)/2;
//     DB d=a1*b2-a2*b1;
//     ret.x=a.x+(c1*b2-c2*b1)/d;
//     ret.y=a.y+(a1*c2-a2*c1)/d;
//     return ret;
// }

// Inscribed circle(内心)
PT incenter(PT a, PT b, PT c) {
    DB t1 = (arg(b-c) + arg(a-c))/2;
    DB t2 = (arg(c-a) + arg(b-a))/2;
    return crsLL(LI(c, c+PT(cos(t1), sin(t1))),
                 LI(a, a+PT(cos(t2), sin(t2))));
}

// Altitude (高线/垂心)
PT perpencenter(PT a, PT b, PT c) {
    return crsLL(LI(c, c+Rot(b-a,0,1)),
                 LI(a, a+Rot(c-b,0,1)));
}

// Barycenter(重心)
// 到三角形三顶点距离的平方和最小的点
// 三角形内到三边距离之积最大的点
PT barycenter(PT a, PT b, PT c) {
    return crsLL(LI((a+b)/2.0, c), LI((a+c)/2.0, b));
}

// Equilateral triangle(等边三角形)
LI get_equil(PT a, PT b, PT c) {
    PT v=(b-a)*(sqrt(3.0)/2.0), m=(a+b)/2.0;
    return LI(c, m + (ccw(a, b, c)>0 ? Rot(v,0,-1): Rot(v,0,1)));
}
// 模拟退火算法参看 polygon 部分
PT fermat_point(PT a, PT b, PT c) {
    DB A = abs(b-c), B = abs(a-c), C = abs(a-b);
    // make edge C is largest, A is smallest
    if (B > C) swap(b, c), swap(B, C);
    if (A > C) swap(a, c), swap(A, C);
    // if (A > B) swap(a, b), swap(A, B);

    if (dot(a-c, b-c)/A/B <= -0.5)
        return c;

    return crsLL(get_equil(a, b, c),
                 get_equil(b, c, a));
}
DB fermat_dis(DB a, DB b, DB c) {
    if (a > c) swap(a, c);
    if (b > c) swap(b, c);
    if ((a*a + b*b - c*c) / (2*a*b) <= -0.5)
        return a+b;
    else {
        DB p = (a+b+c)/2, s = sqrt(s*(s-a)*(s-b)*(s-c));
        return sqrt((a*a+b*b+c*c + 4*sqrt(3.0)*s)/2);
    }
}
