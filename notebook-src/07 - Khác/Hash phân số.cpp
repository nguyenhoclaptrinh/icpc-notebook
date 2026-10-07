ull hashFrac(ll num, ll den)
{
    ll g = __gcd(llabs(num), llabs(den));
    if (g == 0)
        return 0;
    num /= g;
    den /= g;
    if (den < 0 || (den == 0 && num < 0)) {
        num = -num;
        den = -den;
    }
    return hashPair((int)num, (int)den);
}

ull hashSlope(ii a, ii b)
{
    return hashFrac((ll)b.se - a.se, (ll)b.fi - a.fi);
}
