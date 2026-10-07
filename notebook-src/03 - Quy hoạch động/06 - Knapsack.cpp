// KNAPSACK — 3 bản chuẩn. w = trọng lượng, v = giá trị, C = sức chứa.
// Dấu hiệu nhận biết: "chọn vật tối đa C", "mỗi vật có giới hạn số lượng".
// Cách gọi (trả về giá trị lớn nhất, không bắt buộc dùng hết C):
//   knap01(w, v, C):        mỗi món lấy TỐI ĐA 1 lần  -> duyệt C NGƯỢC.
//   knapUnbounded(w, v, C): mỗi món lấy NHIỀU lần    -> duyệt C XUÔI.
//   knapBounded(w, v, cnt, C): món i lấy tối đa cnt[i] lần (tách nhị phân).
// Độ phức tạp: O(n*C). C > 2e5 hoặc tổng v nhỏ -> đổi sang DP theo giá trị.
// Lưu ý: w[i], v[i] vừa trong int (tích w[i]*take khi tách nhị phân).
ll knap01(const vector<int> &w, const vector<int> &v, int C) {
    vector<ll> dp(C + 1, 0);
    for (int i = 0; i < (int)w.size(); i++)
        for (int c = C; c >= w[i]; c--)
            dp[c] = max(dp[c], dp[c - w[i]] + v[i]);
    return dp[C];
}

ll knapUnbounded(const vector<int> &w, const vector<int> &v, int C) {
    vector<ll> dp(C + 1, 0);
    for (int i = 0; i < (int)w.size(); i++)
        for (int c = w[i]; c <= C; c++)
            dp[c] = max(dp[c], dp[c - w[i]] + v[i]);
    return dp[C];
}

ll knapBounded(const vector<int> &w, const vector<int> &v,
               const vector<int> &cnt, int C) {
    vector<int> w2, v2; // tách mỗi món thành các món 0/1 (1,2,4,...,rest)
    for (int i = 0; i < (int)w.size(); i++) {
        int k = 1, rest = cnt[i];
        while (rest > 0) {
            int take = min(k, rest);
            w2.push_back(w[i] * take);
            v2.push_back(v[i] * take);
            rest -= take;
            k <<= 1;
        }
    }
    return knap01(w2, v2, C);
}
