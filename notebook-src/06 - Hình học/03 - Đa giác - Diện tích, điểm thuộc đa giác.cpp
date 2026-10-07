// Đa giác đơn (không tự cắt), đỉnh p[0..n-1] theo thứ tự
// polyArea2(p):      2 lần diện tích có dấu (> 0 nếu ngược chiều kim đồng hồ)
//                    (tránh chia đôi để giữ số nguyên; coi chừng tràn ll
//                    nếu toạ độ ~ 1e9)
// pointInPoly(q, p): 0: q ngoài đa giác, 1: q trên biên, 2: q trong đa giác
//                    O(n), đa giác lồi hay lõm đều được
T polyArea2(vector<Pt> &p)
{
    int n = p.size();
    T s = 0;
    for (int i = 0; i < n; i++)
        s += cross(p[i], p[(i + 1) % n]);
    return s;
}

int pointInPoly(Pt q, vector<Pt> &p)
{
    int n = p.size();
    bool in = false;
    for (int i = 0; i < n; i++) {
        Pt a = p[i], b = p[(i + 1) % n];
        if (onSegment(q, a, b))
            return 1;
        // tia từ q sang phải cắt cạnh ab?
        if ((a.y > q.y) != (b.y > q.y)) {
            T c = cross(b - a, q - a);
            if (b.y > a.y ? c > 0 : c < 0)
                in = !in;
        }
    }
    return in ? 2 : 0;
}
