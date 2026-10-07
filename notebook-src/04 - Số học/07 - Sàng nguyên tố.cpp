// sieve primes in [1, R]. O(R * log(log(R)))
vector<bool> primeSieve(int R)
{
    vector<bool> isPrime(R + 1, true);
    isPrime[0] = isPrime[1] = false;

    for (int i = 2; i * i <= R; i++)
        if (isPrime[i])
            for (int j = i * i; j <= R; j += i)
                isPrime[i] = false;

    return isPrime;
}

// sieve primes in [L, R]. O(sqrt(R) * K): K is constant
vector<bool> primeSieve_range(int L, int R)
{
    vector<bool> isPrime(R - L + 1, true);

    for ( i = 2; i * i <= R; i++)
        for ( j = max(i * i, (L + i - 1) / i * i); j <= R; j += i)
            isPrime[j - L] = false;

    // Xét riêng trường hợp số 1
    if (1 >= L) isPrime[1 - L] = false;

    return isPrime;
}
