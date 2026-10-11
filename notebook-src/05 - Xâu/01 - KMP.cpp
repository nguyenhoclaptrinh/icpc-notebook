// KMP — tìm pattern T trong S + biên/chu kỳ, O(N+M)
// Dấu hiệu: "tìm mọi vị trí xuất hiện", "chu kỳ/border nhỏ nhất".
//   VD: S="ababa", T="aba" -> {0, 2}.
// Lưu ý: '#' vắng mặt trong S,T.
// pi[i] = border dài nhất của tiền tố s[0..i].
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

// vị trí T xuất hiện trong S (0-index), O(N+M).
// SUBMIT LINK: https://oj.vnoi.info/problem/substr
vector<int> string_matching(string s, string t)
{
    string p = t + '#' + s;
    int m = t.size();
    int n = s.size();
    vector<int> pi = prefix_function(p);

    vector<int> res;
    for (int i = m + 1; i <= m + n; ++i) {
        // pi[i]==m: T kết thúc tại i, vị trí trong S là i-2*m
        if (pi[i] == m)
            res.push_back(i - 2*m);
    }

    return res;
}
