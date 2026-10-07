// TỔ HỢP — tổ hợp và chỉnh hợp, cơ bản và modulo
// Dấu hiệu nhận biết: "chọn k từ n", "số cách sắp xếp", "tính tổ hợp modulo".
// Cách gọi:
//   nCr(n, r): tổ hợp không mod, O(r), tràn ll nếu n > 20.
//   buildComb(n, mod): tiền xử lý fact/invFact, O(n), mod phải là SNT.
//   nCrMod(n, r), nPrMod(n, r): truy vấn O(1) sau khi buildComb.
// Lưu ý: nCr không mod chỉ dùng n <= 20 (tràn ll). MODC để tránh tên với template.
ll nCr(int n, int r)
{
	if (r < 0 || r > n) return 0;
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

// Tiền xử lý O(N), mỗi truy vấn O(1) (MODC phải là SNT, n < MODC)
const int MAXN = 1000005;
ll fact[MAXN], invFact[MAXN], MODC;

void buildComb(int n, ll mod)
{
    MODC = mod;
    fact[0] = 1;
    for (int i = 1; i <= n; i++) fact[i] = fact[i - 1] * i % MODC;
    invFact[n] = Pow(fact[n], MODC - 2, MODC);
    for (int i = n - 1; i >= 0; i--)
        invFact[i] = invFact[i + 1] * (i + 1) % MODC;
}

ll nCrMod(int n, int r)
{
    if (r < 0 || r > n) return 0;
    return fact[n] * invFact[r] % MODC * invFact[n - r] % MODC;
}

// Chỉnh hợp: A(n, r) = n! / (n - r)!, cần buildComb() trước
ll nPrMod(int n, int r)
{
    if (r < 0 || r > n) return 0;
    return fact[n] * invFact[n - r] % MODC;
}
