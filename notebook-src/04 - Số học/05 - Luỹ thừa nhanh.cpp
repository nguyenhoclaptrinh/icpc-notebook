ll Pow(ll a, ll b, ll m)
{
    if (b == 0) return 1 % m;
    ll t = Pow(a, b / 2, m);
    t = (t * t) % m;
    if (b & 1) return (t * (a % m)) % m;
    return t;
}

pair<ll, ll> fib(ll n, ll m) // {F(n), F(n+1)} mod m, F(0) = 0, F(1) = 1
{
    if (n == 0) return {0, 1 % m};
    auto [fk, fk1] = fib(n / 2, m);
    ll f2k = fk * ((2 * fk1 % m - fk + m) % m) % m; // F(2k)
    ll f2k1 = (fk * fk % m + fk1 * fk1 % m) % m;     // F(2k+1)
    if (n % 2 == 0) return {f2k, f2k1};
    return {f2k1, (f2k + f2k1) % m};
}
