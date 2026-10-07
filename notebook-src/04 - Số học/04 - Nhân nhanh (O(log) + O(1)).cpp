// NHÂN NHANH — (a * b) % m khi a, b, m < 2^63
// Dấu hiệu nhận biết: nhân 2 số lớn mod số lớn, tràn int64.
// Cách gọi: MultLog(a, b, m) — O(log b), an toàn tuyệt đối.
//           MultO1(a, b, m)  — O(1), dùng long double, nhanh hơn.
// Độ phức tạp: MultLog O(log b), MultO1 O(1).
// Lưu ý: MultO1 chỉ dùng khi m < 2^62 (tràn long double).
ll MultLog(ll a, ll b, ll m) // O(log(b))
{
    if (b == 0) return 0;
    ll t = MultLog(a, b / 2, m);
    t = (t + t) % m;
    if (b & 1) return (t + a % m) % m;
    return t;
}

ll MultO1(ll a, ll b, ll m) // O(1)
{
    a %= m; b %= m;
    ull q = (long double) a * b / m;
    ll  r = ll(a * b - q * m) % ll(m);
    if (r < 0) r += m;
    return r;
}
