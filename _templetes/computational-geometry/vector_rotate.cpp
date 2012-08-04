// rotate OA counter-clock.
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
