// Z-FUNCTION — z[i] = tiền tố dài nhất của s khớp với s[i..n-1]
// Dấu hiệu nhận biết: "tiền tố", "xâu con chung", "số lần xuất hiện".
// Cách gọi: z = z_function(s); z[0] = 0.
// Độ phức tạp: O(N) — dùng cửa sổ [l, r] giới hạn số lần so sánh.
// Lưu ý: z[0] luôn là 0 (không tự so sánh).
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

// Tìm các vị trí xâu T xuất hiện trong S (bản dùng Z-function)
// SUBMIT LINK: https://oj.vnoi.info/problem/substr
// đặt M = t.size(), N = s.size()
// tìm các vị trí i trong xâu S
// mà S[i, i + M - 1] == T
// O(N + M)
vector<int> z_matching(string s, string t)
{
    string p = t + '#' + s;
    int m = t.size();
    int n = s.size();
    vector<int> z = z_function(p);
    vector<int> res;
    for (int i = m + 1; i <= m + n; ++i) {
        // Tìm thấy KQ:
        // p[0, m - 1] == p[i, i + z[i] - 1] == T
        // -> tồn tại xâu con trong S bằng T
        if (z[i] == m)
            res.push_back(i - m - 1); // vị trí trong s: i - (m + 1)
    }
    return res;
}

// Đếm số lượng xâu con liên tiếp phân biệt trong S
// đặt N = s.size()
// O(N^2)
int num_substr(string s)
{
    // Ý tưởng: giả sử số lượng xâu phân biệt
    //          là K, khi ta thêm kí tự c vào
    //          thì cần đếm thêm số lượng xâu
    //          khác nhau có hậu tố với chuỗi s + c
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
