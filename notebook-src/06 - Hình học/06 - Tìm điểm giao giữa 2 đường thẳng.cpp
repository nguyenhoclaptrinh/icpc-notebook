// intersect(l1, l2, x, y): giao 2 đường thẳng, trả về false nếu song song/trùng
//   (x, y là tọa độ giao điểm khi có nghiệm duy nhất)
bool intersect(line l1, line l2, double &x, double &y)
{
    ll D = l1.a * l2.b - l2.a * l1.b;
    if (D == 0) return false; // song song hoặc trùng nhau
    x = (double)(l1.b * l2.c - l2.b * l1.c) / D;
    y = (double)(l2.a * l1.c - l1.a * l2.c) / D;
    return true;
}
