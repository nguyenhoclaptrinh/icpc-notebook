// Đếm số nghiệm nguyên dương (x, y >= 1) của a*x + b*y = c
// Diophantine(a, b, c) -> số nghiệm, trả 0 nếu không tồn tại
// (không tồn tại khi gcd(a,b) không chia hết c, hoặc c quá nhỏ)
//
// Áp dụng: đếm cách phân tích c thành tổng có trọng số a, b với
// số lượng dương -- vd bài toán đổi tiền/chia kẹo đếm số cách
ll MOD(ll a, ll m)
{
    return (a % m + m) % m;
}

int Diophantine(int a, int b, int c)
{
    ll m = a, n = b, xA = 1, xB = 0;
    while (n > 0)
    {
        ll q = m / n;
        ll r = m - q * n;
        ll xr = xA - q * xB;
        m = n; xA = xB;
        n = r; xB = xr;
    }
    if (c % m != 0) return 0;
    ll p = b / m;
    ll xMax = (c - b) / a;
    xA = MOD(xA * c / m, p);
    ll res = (xMax - xA) / p + (xA != 0);

    return ((xMax < xA)? 0 : res);
}
