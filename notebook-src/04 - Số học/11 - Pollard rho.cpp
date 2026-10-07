// Phân tích thừa số nguyên tố số lớn, n < 2^64
// Cần miller(n) trong "Kiểm tra SNT – Miller Rabin"
// factorize(n):  các thừa số nguyên tố của n (có lặp, đã sắp xếp)
//                trung bình O(n^(1/4)) phép nhân modulo
//                VD: factorize(12) = {2, 2, 3}, factorize(1) = {}

// tìm một ước thực sự của hợp số lẻ n (thuật toán rho của Pollard)
ull rho(ull n)
{
    static mt19937_64 rng(712367);
    while (true) {
        ull c = rng() % (n - 1) + 1, x = rng() % n, y = x, d = 1;
        auto f = [&](ull v) {
            return (ull)(((unsigned __int128)v * v + c) % n);
        };
        while (d == 1) {
            x = f(x);
            y = f(f(y));
            d = __gcd(x > y ? x - y : y - x, n);
        }
        if (d != n)
            return d;
    }
}

void split(ull n, vector<ull> &res)
{
    if (n == 1)
        return;
    if (miller(n)) {
        res.push_back(n);
        return;
    }
    ull d = rho(n);
    split(d, res);
    split(n / d, res);
}

vector<ull> factorize(ull n)
{
    vector<ull> res;
    // tách các thừa số nhỏ trước cho nhanh (và tránh rho với n chẵn)
    for (ull p = 2; p < 100 && p * p <= n; p++)
        while (n % p == 0) {
            res.push_back(p);
            n /= p;
        }
    split(n, res);
    sort(res.begin(), res.end());
    return res;
}
