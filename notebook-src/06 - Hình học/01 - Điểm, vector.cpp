// Điểm / vector 2D. Đổi T thành double để dùng số thực (sgn so với eps)
// dot(a, b):       a.x*b.x + a.y*b.y
// cross(a, b):     a.x*b.y - a.y*b.x (> 0 nếu b nằm bên trái a)
// cross(o, a, b):  cross(a - o, b - o) (> 0 nếu o -> a -> b rẽ trái)
// onSegment(p, a, b): p thuộc đoạn ab (kể cả đầu mút)
typedef ll T;

int sgn(T x)
{
    return (x > 0) - (x < 0);
}

struct Pt
{
    T x, y;

    Pt operator+(Pt o) const { return {x + o.x, y + o.y}; }
    Pt operator-(Pt o) const { return {x - o.x, y - o.y}; }
    Pt operator*(T k) const { return {x * k, y * k}; }
    bool operator<(Pt o) const { return x != o.x ? x < o.x : y < o.y; }
    bool operator==(Pt o) const { return x == o.x && y == o.y; }
};

T dot(Pt a, Pt b)
{
    return a.x * b.x + a.y * b.y;
}

T cross(Pt a, Pt b)
{
    return a.x * b.y - a.y * b.x;
}

T cross(Pt o, Pt a, Pt b)
{
    return cross(a - o, b - o);
}

T norm2(Pt a) // bình phương độ dài
{
    return dot(a, a);
}

Pt perp(Pt a) // xoay 90 độ ngược chiều kim đồng hồ
{
    return {-a.y, a.x};
}

double dist(Pt a, Pt b)
{
    return sqrt((double)norm2(a - b));
}

bool onSegment(Pt p, Pt a, Pt b)
{
    return sgn(cross(a, b, p)) == 0 && sgn(dot(a - p, b - p)) <= 0;
}
