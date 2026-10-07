// LINEAR BASIS (XOR) — cơ sở nhị phân cho các bài xor
// Dấu hiệu nhận biết: "xor lớn nhất", "chọn subset để xor = K",
//   "có biểu diễn được x qua xor không", "đếm số subset xor = 0".
// Cách gọi: insert(x) từng số; maxXor(); maxXorWith(start); canMake(x).
//   Số phần tử độc lập = đếm số b[i] != 0 -> số subset xor phân biệt = 2^cnt.
// Độ phức tạp: O(60) mỗi thao tác. GIẢ THIẾT: mọi số < 2^61.
// Lưu ý: chỉ dùng cho XOR, không dùng cho phép toán khác.
struct LinearBasis {
    ll b[61];

    LinearBasis() { memset(b, 0, sizeof b); }

    void insert(ll x) {
        for (int i = 60; i >= 0; i--) if (x >> i & 1) {
            if (!b[i]) { b[i] = x; return; }
            x ^= b[i];
        }
    }

    ll maxXor() { // xor lớn nhất xor được từ tập đã insert
        ll ans = 0;
        for (int i = 60; i >= 0; i--) ans = max(ans, ans ^ b[i]);
        return ans;
    }

    ll maxXorWith(ll start) { // (start xor S) lớn nhất
        ll ans = start;
        for (int i = 60; i >= 0; i--) ans = max(ans, ans ^ b[i]);
        return ans;
    }

    bool canMake(ll x) { // x có viết được thành xor 1 subset không
        for (int i = 60; i >= 0; i--) if (x >> i & 1) {
            if (!b[i]) return false;
            x ^= b[i];
        }
        return true;
    }
};
