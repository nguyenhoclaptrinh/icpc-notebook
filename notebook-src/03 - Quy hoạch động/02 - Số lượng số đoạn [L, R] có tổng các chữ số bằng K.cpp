ll l, r; int k; // đếm số trong [L, R] có tổng chữ số bằng K: cnt(R) - cnt(L-1)
ll f[20][200][2]; // f[id][sum][tight]: bảng nhớ, reset bằng memset(f, -1) mỗi lần cnt
ll dp(string &s, int id, int sum, bool isSmaller)
{
    if (id == s.size())
        return sum == k;

    if (f[id][sum][isSmaller] != -1)
        return f[id][sum][isSmaller];

    ll res = 0;
    int maxDigit = (isSmaller ? 9 : int(s[id] - '0'));

    for (int i = 0; i <= maxDigit; i++) {
        bool curSmaller = isSmaller;
        if (i < maxDigit)
            curSmaller = 1;
        res += dp(s, id + 1, sum + i, curSmaller);
    }

    return f[id][sum][isSmaller] = res;
}

ll cnt(ll x) // đếm đoạn [1, X]
{
    string s = std::to_string(x);
    memset(f, -1, sizeof(f));
    ll res = dp(s, 0, 0, 0);
    // dp đếm cả số 0 (tổng chữ số = 0), nên khi K = 0 cần trừ đi 1
    if (k == 0) res--;
    return res;
}
