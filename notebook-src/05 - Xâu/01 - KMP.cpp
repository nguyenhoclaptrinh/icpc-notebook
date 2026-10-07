// tìm các pi[i] là giá trị K <= i lớn I sao cho:
// - s[0, K-1] == s[i - K + 1, i]
// Lưu ý: pi[0] = 0
// đặt N = s.size()
// O(N)
vector<int> prefix_function(string s)
{
    int n = s.size();
    vector<int> pi(n);
    for (int i = 1; i < n; i++) {
        int j = pi[i - 1];
        while (j > 0 && s[i] != s[j])
            j = pi[j - 1];

        if (s[i] == s[j])
            j++;

        pi[i] = j;
    }
    return pi;
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
    vector<int> pi = prefix_function(p);

    vector<int> res;
    for (int i = m + 1; i <= m + n; ++i) {
        // Tìm thấy KQ:
        // p[0, m - 1] == p[i - pi[i] + 1, i] == T
        // -> tồn tại xâu con trong S bằng T
        if (pi[i] == m)
            res.push_back(i - 2*m + 1);
    }

    return res;
}
