// Cần "Điểm, vector"
// segIntersect(a, b, c, d): đoạn ab và cd có điểm chung không
//                           (kể cả chạm đầu mút, chồng lên nhau, suy biến)
// distPointLine(p, a, b):   khoảng cách từ p đến đường thẳng ab (a != b)
// distPointSeg(p, a, b):    khoảng cách từ p đến đoạn ab
bool segIntersect(Pt a, Pt b, Pt c, Pt d)
{
    int d1 = sgn(cross(c, d, a)), d2 = sgn(cross(c, d, b));
    int d3 = sgn(cross(a, b, c)), d4 = sgn(cross(a, b, d));
    if (d1 * d2 < 0 && d3 * d4 < 0)
        return true;
    return onSegment(a, c, d) || onSegment(b, c, d)
        || onSegment(c, a, b) || onSegment(d, a, b);
}

double distPointLine(Pt p, Pt a, Pt b)
{
    return fabs((double)cross(a, b, p)) / dist(a, b);
}

double distPointSeg(Pt p, Pt a, Pt b)
{
    if (sgn(dot(p - a, b - a)) <= 0)
        return dist(p, a);
    if (sgn(dot(p - b, a - b)) <= 0)
        return dist(p, b);
    return distPointLine(p, a, b);
}
