// Z-FUNCTION — tiền tố dài nhất khớp từng hậu tố, O(N)
// Dấu hiệu: "tiền tố khớp hậu tố", "đếm prefix xuất hiện bao nhiêu lần".
//   VD: s="aabcaabx" -> z[4]=3 ("aab").
// Lưu ý: '#' vắng mặt; num_substr O(N^2): N > 2000 dùng SAM.
// z[0]=0; cửa sổ [l,r] giữ O(N).
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

// vị trí T xuất hiện trong S (0-index), O(N+M).
// SUBMIT LINK: https://oj.vnoi.info/problem/substr
vector<int> z_matching(string s, string t)
{
    string p = t + '#' + s;
    int m = t.size();
    int n = s.size();
    vector<int> z = z_function(p);
    vector<int> res;
    for (int i = m + 1; i <= m + n; ++i) {
        // z[i]>=m: T bắt đầu tại i, vị trí trong s là i-m-1
        if (z[i] == m)
            res.push_back(i - m - 1);
    }
    return res;
}

// số xâu con phân biệt, O(N^2).
// Ý tưởng: thêm từng ký tự, cộng (i+1)-zmax.
int num_substr(string s)
{
    // cộng số xâu mới có hậu tố là tiền tố đang xét
    int k = 0;
    int n = s.size();
    for (int i = 0; i < n; ++i) {
        string tmp = s.substr(0, i + 1);
        reverse(tmp.begin(), tmp.end());
        vector<int> z = z_function(tmp);
        int zmax = *max_element(z.begin(), z.end());
        k += (i + 1) - zmax;
    }
    return k;
}
