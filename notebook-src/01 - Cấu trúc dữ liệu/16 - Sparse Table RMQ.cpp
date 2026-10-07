// SPARSE TABLE — truy vấn min/max trên mảng TĨNH (không update)
// Dấu hiệu nhận biết: mảng cố định + nhiều query min/max trên đoạn [l, r].
// CHỈ dùng cho phép toán LẶP LẠI ĐƯỢC (idempotent): min, max, gcd, and/or.
// Muốn tổng/sum -> dùng Fenwick (file 03) hoặc Segment tree (file 06).
// Cách gọi: SparseTable st(a) với a[0..n-1]; st.queryMin(l, r), st.queryMax(l, r)
//   (0-index, bao gồm cả 2 đầu, yêu cầu l <= r).
// Độ phức tạp: build O(n log n), query O(1), bộ nhớ O(n log n).
// Lưu ý: kiểu int; đổi int -> long long nếu giá trị lớn.
struct SparseTable {
    int n, K;
    vector<vector<int>> mn, mx;
    vector<int> lg;

    SparseTable() {}
    SparseTable(const vector<int> &a) { build(a); }

    void build(const vector<int> &a) {
        n = (int)a.size();
        K = 1;
        while ((1 << K) <= n) K++;
        mn.assign(K, vector<int>(n));
        mx.assign(K, vector<int>(n));
        mn[0] = a;
        mx[0] = a;
        for (int k = 1; k < K; k++)
            for (int i = 0; i + (1 << k) <= n; i++) {
                mn[k][i] = min(mn[k - 1][i], mn[k - 1][i + (1 << (k - 1))]);
                mx[k][i] = max(mx[k - 1][i], mx[k - 1][i + (1 << (k - 1))]);
            }
        lg.assign(n + 1, 0);
        for (int i = 2; i <= n; i++) lg[i] = lg[i / 2] + 1;
    }

    int queryMin(int l, int r) { // 0-index, l <= r
        int k = lg[r - l + 1];
        return min(mn[k][l], mn[k][r - (1 << k) + 1]);
    }

    int queryMax(int l, int r) { // 0-index, l <= r
        int k = lg[r - l + 1];
        return max(mx[k][l], mx[k][r - (1 << k) + 1]);
    }
};
