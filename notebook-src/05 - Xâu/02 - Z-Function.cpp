// Z-FUNCTION — z[i] = tiền tố dài nhất khớp từng hậu tố, O(N)
// Dấu hiệu: "tiền tố khớp hậu tố", "đếm prefix xuất hiện bao nhiêu lần".
//   VD: s="aabcaabx" -> z[4]=3 ("aab").
// Độ phức tạp: O(N).
vector<int> z_function(string s)
{
    int n = s.size();
    vector<int> z(n);
    int l = 0, r = 0; // [l, r] = đoạn khớp dài nhất đã biết
    for (int i = 1; i < n; ++i) {
        if (i < r) z[i] = min(r - i, z[i - l]);
        while (i + z[i] < n && s[z[i]] == s[i + z[i]]) ++z[i];
        if (i + z[i] > r) l = i, r = i + z[i];
    }
    return z;
}
