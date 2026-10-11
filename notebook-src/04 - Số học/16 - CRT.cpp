// CRT — ghép hệ đồng dư x ≡ r[i] (mod m[i]), không cần m nguyên tố cùng nhau
// Dấu hiệu: "tìm x nhỏ nhất đồng thời chia dư ...".
//   VD: x≡2 (mod 3), x≡3 (mod 5) -> {8, 15}.
// Độ phức tạp: O(n log Amax).
// Lưu ý: m[i] > 0; chuẩn hóa r[i] trước khi gọi; lcm vừa trong 64-bit.
// Nghiệm X+k*M; vô nghiệm -> {0,-1}; cần ext_gcd (file 01).
pair<ll, ll> crt(const vector<ll> &r, const vector<ll> &m) {
    __int128 x = r[0], M = m[0];
    for (int i = 1; i < (int)r.size(); i++) {
        ll p, q;
        ext_gcd((ll)M, m[i], p, q); // M vừa trong ll theo giả thiết
        ll g = std::gcd((ll)M, m[i]);
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
