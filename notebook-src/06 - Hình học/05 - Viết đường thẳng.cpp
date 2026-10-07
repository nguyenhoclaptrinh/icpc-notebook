// Đường thẳng dạng A*x + B*y + C = 0
struct line { ll a, b, c; };

line writeLine(Pt P, Pt Q) // đường thẳng qua P, Q (giả thiết P != Q)
{
    ll A = P.y - Q.y;
    ll B = Q.x - P.x;
    ll C = -(A * P.x + B * P.y);
    return {A, B, C};
}
