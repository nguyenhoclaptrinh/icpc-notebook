// LINEAR BASIS (XOR) — xor lớn nhất / xor được K không, O(61) mỗi op
// Dấu hiệu: "xor lớn nhất", "xor được K không", "đếm subset xor".
//   VD: a = {3,5} -> maxXor() = 6.
// Bẫy: basis rỗng -> maxXor()=0, canMake(0)=true; input âm/>=2^61 là UB;
//   đây KHÔNG phải max-subarray-xor (dạng đó dùng Trie).
struct LinearBasis {
    ll b[61];

    LinearBasis() { memset(b, 0, sizeof b); }

    // nhét x vào họ sinh.
    void insert(ll x) {
        for (int i = 60; i >= 0; i--) if (x >> i & 1) {
            if (!b[i]) { b[i] = x; return; }
            x ^= b[i];
        }
    }

    // xor lớn nhất ghép được (không đổi basis).
    ll maxXor() {
        ll ans = 0;
        for (int i = 60; i >= 0; i--) ans = max(ans, ans ^ b[i]);
        return ans;
    }

    // (start xor S) lớn nhất.
    ll maxXorWith(ll start) {
        ll ans = start;
        for (int i = 60; i >= 0; i--) ans = max(ans, ans ^ b[i]);
        return ans;
    }

    // true nếu x viết được thành xor 1 subset.
    bool canMake(ll x) {
        for (int i = 60; i >= 0; i--) if (x >> i & 1) {
            if (!b[i]) return false;
            x ^= b[i];
        }
        return true;
    }
};
