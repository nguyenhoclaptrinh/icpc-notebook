// Đúng với mọi n < 2^64, không phụ thuộc Pow
pair<ull, ull> factor(ull n) // phân tích n = 2^s * d
{
    ull s = 0;
    while ((n & 1) == 0) {
        s++;
        n >>= 1;
    }
    return {s, n};
}

// nếu a^d % n != 1 % n và (a^d)^(2^r) với mọi 0 <= r < s
// thì n ko phải là snt --> false
bool test_a(ull s, ull d, ull n, ull a)
{
    if (n == a) return true;

    auto mul = [&](ull x, ull y) {
        return (ull)((unsigned __int128)x * y % n);
    };

    ull p = 1, b = a % n; // p = a^d % n
    for (ull e = d; e; e >>= 1, b = mul(b, b))
        if (e & 1)
            p = mul(p, b);
    if (p == 1) return true;

    for (; s > 0; s--) {
        if (p == n - 1)
            return true;
        p = mul(p, p);
    }

    return false;
}

bool miller(ull n)
{
    if (n < 2)
        return false;
    if ((n & 1) == 0)
        return n == 2;

    ull s, d;
    tie(s, d) = factor(n - 1);
    int list_a[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37};

    for (auto &a : list_a)
        if (!test_a(s, d, n, a))
            return false;
    return true;
}
