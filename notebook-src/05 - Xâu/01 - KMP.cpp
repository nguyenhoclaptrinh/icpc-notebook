// KMP — tìm mọi vị trí T xuất hiện trong S, O(N+M)
// Cách gọi: string_matching(S, T) -> vị trí 0-index.
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
            // Vị trí bắt đầu trong p: i - m + 1
            // Vị trí tương ứng trong s: (i - m + 1) - (m + 1) = i - 2*m
            res.push_back(i - 2*m);
    }

    return res;
}
