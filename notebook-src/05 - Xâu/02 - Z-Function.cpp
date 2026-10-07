// đặt N = s.size()
// tìm các z[i] là giá trị K < N lớn I sao cho:
// - s[0, K-1] == s[i, i + K - 1]
// Lưu ý: z[0] = 0
// O(N)
vector<int> z_function(string s)
{
    int n = s.size();
    vector<int> z(n);
    for (int i = 1; i < n; ++i)
        while (i + z[i] < n && s[z[i]] == s[i + z[i]])
            ++z[i];

    return z;
}

// Tìm các vị trí xâu T xuất hiện trong S
// SUBMIT LINK: https://oj.vnoi.info/problem/substr
// đặt M = t.size(), N = s.size()
// tìm các vị trí i trong xâu S
// mà S[i, i + M - 1] == T
// O(N + M)
vector<int> string_matching(string s, string t)
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
            res.push_back(i - m);
    }
    return res;
}

// Đếm s.lượng xâu con liên tiếp phân biệt trong S
// đặt N = s.size()
// O(N^2)
int num_substr(string s)
{
    // Ý tưởng: giả sử số lượng xâu phân biệt
    //          là K, khi ta thêm kí tự c vào
    //          thì cần đếm thêm số lượng xâu
    //          khác nhau có hậu tố với chuỗi s + c
    vector<int> z = z_function(s);
    string tmp;
    int k = 0;
    int n = s.size();
    for (int i = 0; i < n; ++i) {
        tmp = s[i] + tmp;
        vector<int> z = z_function(tmp);
        int zmax = *max_element(z.begin(), z.end());
        k += (i + 1) - zmax;
    }
    return k;
}
