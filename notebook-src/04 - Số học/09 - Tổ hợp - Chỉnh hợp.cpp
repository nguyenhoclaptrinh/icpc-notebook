// O(r)
ll nCr(int n, int r)
{
	// p holds the value of n*(n-1)*(n-2)...,
	// k holds the value of r*(r-1)...
	ll p = 1, k = 1;

	// C(n, r) == C(n, n - r),
	if (n - r < r) r = n - r;

	if (r != 0) {
		while (r) {
			p *= n; k *= r;
			ll m = __gcd(p, k);
			p /= m; k /= m;
			n--; r--;
		}
	}
	else
		p = 1;

	return p;
}

// Tiền xử lý O(N), mỗi truy vấn O(1) (MOD phải là SNT)
ll fact[N], invFact[N], MOD;

void buildComb(int n, ll mod)
{
    MOD = mod;
    fact[0] = 1;
    for (int i = 1; i < n; i++) fact[i] = fact[i - 1] * i % MOD;
    invFact[n - 1] = Pow(fact[n - 1], MOD - 2, MOD);
    for (int i = n - 2; i >= 0; i--)
        invFact[i] = invFact[i + 1] * (i + 1) % MOD;
}

ll nCrMod(int n, int r)
{
    if (r < 0 || r > n) return 0;
    return fact[n] * invFact[r] % MOD * invFact[n - r] % MOD;
}

// Chỉnh hợp: A(n, r) = n! / (n - r)!, cần buildComb() trước
ll nPrMod(int n, int r)
{
    if (r < 0 || r > n) return 0;
    return fact[n] * invFact[n - r] % MOD;
}
