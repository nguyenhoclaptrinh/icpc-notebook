// BSGS — log rời rạc: x nhỏ nhất với a^x = b mod m, O(sqrt m)
// Dấu hiệu: "tìm x sao cho a^x = b (mod m)".
//   VD: bsgs(2,3,5)=3 (8%5=3); vô nghiệm -> -1.
// Bẫy: m=1 -> 0; nhân dùng __int128; bảng băm reserve trước; m tới ~1e12
//   (bảng sqrt(m) entries, lớn hơn thì hết RAM/giờ).
long long bsgs_modpow(long long a, long long e, long long m) {
    long long r = 1 % m;
    a %= m;
    while (e) {
        if (e & 1) r = (__int128)r * a % m;
        a = (__int128)a * a % m;
        e >>= 1;
    }
    return r;
}
long long bsgs_egcd(long long a, long long b, long long &x, long long &y) {
    if (!b) { x = 1; y = 0; return a; }
    long long x1, y1, g = bsgs_egcd(b, a % b, x1, y1);
    x = y1; y = x1 - y1 * (a / b);
    return g;
}
// nghịch đảo modular (gcd(a,m)=1), -1 nếu không tồn tại.
long long bsgs_inv(long long a, long long m) {
    long long x, y;
    if (bsgs_egcd(a, m, x, y) != 1) return -1;
    x %= m;
    return x < 0 ? x + m : x;
}
// x nhỏ nhất với a^x = b (mod m), vô nghiệm -> -1.
long long bsgs(long long a, long long m, long long b) {
    if (m == 1) return 0;
    a = (a % m + m) % m; b = (b % m + m) % m;
    if (b == 1) return 0;
    long long cnt = 0, t = 1 % m, g;
    while ((g = std::gcd(a, m)) > 1) {
        if (b % g != 0) return -1;
        b /= g; m /= g;
        t = (__int128)t * (a / g) % m;
        if (++cnt > 60) return -1;
        if (t == b) return cnt;
    }
    // còn lại gcd(a,m)=1: giải a^y = b/t (mod m), đáp án y+cnt.
    long long tinv = bsgs_inv(t, m);
    if (tinv < 0) return -1;
    long long B = (__int128)b * tinv % m;
    long long sq = ceil(sqrt((long double)m));
    unordered_map<long long, long long> table;
    table.reserve(sq * 2);
    long long cur = B;
    for (long long j = 0; j < sq; ++j) {
        if (!table.count(cur)) table[cur] = j;
        cur = (__int128)cur * a % m;
    }
    long long pw = 1;
    for (long long i = 0; i < sq; ++i) pw = (__int128)pw * a % m;
    cur = pw;
    long long best = -1;
    for (long long i = 1; i <= sq; ++i) {
        auto it = table.find(cur);
        if (it != table.end()) {
            long long y = i * sq - it->second;
            if (y >= 0 && (best < 0 || y < best)) best = y;
        }
        cur = (__int128)cur * pw % m;
    }
    // Bỏ nghiệm y=0 giả khi B==1 đã return ở trên; kiểm tra lại cho chắc.
    if (best < 0) return -1;
    return best + cnt;
}
