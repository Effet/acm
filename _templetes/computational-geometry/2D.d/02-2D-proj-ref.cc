// Nearest point in line
PT project(PT p, LI l) {
    DB t = dot(p-l[0], l[1]-l[0]) / norm(l[1]-l[0]);
    return l[0] + t*(l[1]-l[0]);
}
// Mirorr point of line
PT reflect(PT p, LI l) {
    return p + 2.0 * (project(p, l) - p);
}
