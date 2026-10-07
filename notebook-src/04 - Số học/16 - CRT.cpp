// CRT (Chinese Remainder) — ghép hệ đồng dư: x ≡ r[i] (mod m[i])
// Dấu hiệu nhận biết: "tìm x nhỏ nhất đồng thời chia dư ...".
// KHÔNG yêu cầu các m nguyên tố cùng nhau (tự xử lý trường hợp chung ước).
// Cách gọi: crt(r, m) -> {X, M} nghĩa là nghiệm có dạng X + k*M;
//   vô nghiệm -> {0, -1} (kiểm tra M == -1).
// Độ phức tạp: O(n log Amax).
// Lưu ý: lcm trung gian phải vừa trong 64-bit; tích M*t dùng __int128.
//   m[i] phải > 0; tự chuẩn hóa r[i] về [0, m[i]) trước khi gọi nếu cần.
pair<ll, ll> crt(const vector<ll> &r, const vector<ll> &m) {
    __int128 x = r[0], M = m[0];
    for (int i = 1; i < (int)r.size(); i++) {
        ll p, q;
        ext_gcd((ll)M, m[i], p, q); // M vừa trong ll theo giả thiết
        ll g = p * (ll)M + q * m[i]; // p*M + q*m[i] = gcd(M, m[i])
        __int128 diff = (__int128)r[i] - x;
        if (diff % g != 0) return {0, -1}; // vô nghiệm
        __int128 lcm = M / g * m[i];
        __int128 t = (diff / g * p) % (m[i] / g);
        if (t < 0) t += m[i] / g;
        x = (x + M * t) % lcm;
        if (x < 0) x += lcm;
        M = lcm;
    }
    return {(ll)x, (ll)M};
}
