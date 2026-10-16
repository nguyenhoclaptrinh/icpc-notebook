// HASH XÂU 2 MOD — so sánh xâu con O(1) sau build O(N), s 0-indexed
// Dấu hiệu: "2 đoạn bằng nhau?", "palindrome truy vấn?", "LCP nhị phân?".
// Cách gọi: StrHash h(S); h.get(l, r) -> {h1, h2} đoạn [l, r] bao 2 đầu;
//   VD: S = "ababa", get(0,2) == get(2,4) ("aba").
// Độ phức tạp: build O(N), query O(1).
// Lưu ý: 2 mod 1e9+7/1e9+9 chống va chạm; base 31, nhân vừa trong ll;
//   mọi ký tự ASCII đều được (không chỉ 'a'..'z');
//   get(l,r) yêu cầu 0 <= l <= r < n.
struct StrHash {
    static const int M1 = 1000000007, M2 = 1000000009, B = 31;
    vector<int> p1, p2, h1, h2;
    StrHash() {}
    StrHash(const string &s) { build(s); }
    void build(const string &s) {
        int n = (int)s.size();
        p1.assign(n + 1, 0); p2.assign(n + 1, 0);
        h1.assign(n + 1, 0); h2.assign(n + 1, 0);
        p1[0] = p2[0] = 1;
        for (int i = 0; i < n; i++) {
            int c = (unsigned char)s[i] + 1;
            p1[i + 1] = (int)((long long)p1[i] * B % M1);
            p2[i + 1] = (int)((long long)p2[i] * B % M2);
            h1[i + 1] = (int)(((long long)h1[i] * B + c) % M1);
            h2[i + 1] = (int)(((long long)h2[i] * B + c) % M2);
        }
    }
    pair<int, int> get(int l, int r) const { // [l, r] bao 2 đầu
        int x1 = (int)((h1[r + 1] - (long long)h1[l] * p1[r - l + 1]) % M1);
        if (x1 < 0) x1 += M1;
        int x2 = (int)((h2[r + 1] - (long long)h2[l] * p2[r - l + 1]) % M2);
        if (x2 < 0) x2 += M2;
        return {x1, x2};
    }
};
