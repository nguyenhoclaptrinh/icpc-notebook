// Sàng nguyên tố trong [1, R]. O(R log log R). Yêu cầu R >= 0
vector<bool> primeSieve(int R)
{
    if (R < 2) return vector<bool>(max(R + 1, 0), false);
    vector<bool> isPrime(R + 1, true);
    isPrime[0] = isPrime[1] = false;

    for (int i = 2; (ll)i * i <= R; i++)
        if (isPrime[i])
            for (int j = i * i; j <= R; j += i)
                isPrime[j] = false;

    return isPrime;
}

// Sàng nguyên tố trong [L, R] (0 <= L <= R). O((R-L+1) log log R + sqrt(R))
vector<bool> primeSieve_range(int L, int R)
{
    vector<bool> isPrime(R - L + 1, true);

    for (ll i = 2; i * i <= R; i++)
        for (ll j = max(i * i, (L + i - 1) / i * i); j <= R; j += i)
            isPrime[(int)(j - L)] = false;

    // Xét riêng trường hợp số 1
    if (1 >= L) isPrime[1 - L] = false;

    return isPrime;
}
