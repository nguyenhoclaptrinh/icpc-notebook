ll Mult(ll a, ll b, ll m) // O(log(b))
{
    if (b == 0) return 0;
    ll t = Mult(a, b / 2, m);
    t = (t + t) % m;
    if (b & 1) return (t + a % m) % m;
    return t;
}

ll Mult(ll a, ll b, ll m) // O(1)
{
    a %= m; b %= m;
    ull q = (long double) a * b / m;
    ll  r = ll(a * b - q * m) % ll(m);
    if (r < 0) r += m;
    return r;
}
