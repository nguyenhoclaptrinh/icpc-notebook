// SEGMENT TREE BEATS — range chmin + hỏi sum/max, amortized O((n+q) log n)
// Dấu hiệu: "a[i] = min(a[i], val) trên [l,r]" (chmax làm đối xứng).
//   VD: build(a); update(0,n-1,5); query(0,n-1) -> sum sau khi min.
// Bẫy: chỉ chmin/chmax (không gán/cộng chung); second max khởi tạo -INF;
//   luôn push() trước khi xuống con.
struct SegBeats {
    struct Node { long long sum; int mx, se, cnt; };
    static const int NEG = INT_MIN;
    int n;
    vector<Node> t;
    SegBeats() {}
    SegBeats(const vector<int> &a) { build(a); }
    // dựng từ mảng a (0-index).
    void build(const vector<int> &a) {
        n = (int)a.size();
        t.assign(4 * max(1, n), {});
        if (n) build(1, 0, n - 1, a);
    }
    void build(int v, int l, int r, const vector<int> &a) {
        if (l == r) { t[v] = {(long long)a[l], a[l], NEG, 1}; return; }
        int m = (l + r) / 2;
        build(v * 2, l, m, a); build(v * 2 + 1, m + 1, r, a);
        pull(v);
    }
    // gộp 2 con (giữ max, second max, đếm max).
    void pull(int v) {
        const Node &a = t[v * 2], &b = t[v * 2 + 1];
        t[v].sum = a.sum + b.sum;
        if (a.mx == b.mx) t[v] = {t[v].sum, a.mx, max(a.se, b.se), a.cnt + b.cnt};
        else if (a.mx > b.mx) t[v] = {t[v].sum, a.mx, max(a.se, b.mx), a.cnt};
        else t[v] = {t[v].sum, b.mx, max(b.se, a.mx), b.cnt};
    }
    // ép node v xuống x (chỉ gọi khi se < x < mx).
    void applyMin(int v, int x) {
        if (t[v].mx <= x) return;
        t[v].sum -= (long long)(t[v].mx - x) * t[v].cnt;
        t[v].mx = x;
    }
    // đẩy max cha xuống con trước khi đi tiếp.
    void push(int v) {
        applyMin(v * 2, t[v].mx);
        applyMin(v * 2 + 1, t[v].mx);
    }
    // a[i] = min(a[i], x) với i trong [l,r].
    void update(int l, int r, int x) { if (n) update(1, 0, n - 1, l, r, x); }
    void update(int v, int tl, int tr, int l, int r, int x) {
        if (l > r || t[v].mx <= x) return;
        if (tl == l && tr == r && t[v].se < x) { applyMin(v, x); return; }
        push(v);
        int tm = (tl + tr) / 2;
        update(v * 2, tl, tm, l, min(r, tm), x);
        update(v * 2 + 1, tm + 1, tr, max(l, tm + 1), r, x);
        pull(v);
    }
    // tổng trên [l,r].
    long long query(int l, int r) { return n ? query(1, 0, n - 1, l, r) : 0; }
    long long query(int v, int tl, int tr, int l, int r) {
        if (l > r) return 0;
        if (tl == l && tr == r) return t[v].sum;
        push(v);
        int tm = (tl + tr) / 2;
        return query(v * 2, tl, tm, l, min(r, tm))
             + query(v * 2 + 1, tm + 1, tr, max(l, tm + 1), r);
    }
    // max trên [l,r].
    int queryMax(int l, int r) { return n ? queryMax(1, 0, n - 1, l, r) : NEG; }
    int queryMax(int v, int tl, int tr, int l, int r) {
        if (l > r) return NEG;
        if (tl == l && tr == r) return t[v].mx;
        push(v);
        int tm = (tl + tr) / 2;
        return max(queryMax(v * 2, tl, tm, l, min(r, tm)),
                   queryMax(v * 2 + 1, tm + 1, tr, max(l, tm + 1), r));
    }
};
