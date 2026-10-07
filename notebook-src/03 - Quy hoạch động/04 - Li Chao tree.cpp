// Li Chao tree: thêm đường thẳng y = k*x + b, hỏi min tại x. Dạng động
// (mỗi lần add tạo tối đa 1 node, không cần nén toạ độ), O(log(hi - lo))
// VD: dp[i] = min_j(m[j] * x[i] + b[j]) khi x[i] KHÔNG đơn điệu
// (x đơn điệu thì dùng convex hull trick deque cho nhẹ).
// Muốn max: add(-k, -b) và đổi dấu kết quả query.
// t.build(lo, hi):  các x hỏi nằm trong [lo, hi]
// t.add(k, b):      thêm đường y = k*x + b
// t.query(x):       min tại x (LLONG_MAX nếu chưa có đường nào)
// Yêu cầu |k * x| + |b| không tràn ll
struct LiChao
{
    struct Line
    {
        ll k, b;
        ll eval(ll x) { return k * x + b; }
    };

    struct Node
    {
        Line ln;
        int l, r;
    };

    ll lo, hi;
    int root;
    vector<Node> t;

    void build(ll _lo, ll _hi)
    {
        lo = _lo;
        hi = _hi;
        root = 0;
        t.assign(1, {{0, 0}, 0, 0}); // node 0: rỗng
    }

    int add(int id, ll l, ll r, Line nw)
    {
        if (!id) {
            t.push_back({nw, 0, 0});
            return (int)t.size() - 1;
        }
        ll mid = l + (r - l) / 2;
        bool lef = nw.eval(l) < t[id].ln.eval(l);
        bool m = nw.eval(mid) < t[id].ln.eval(mid);
        if (m)
            swap(t[id].ln, nw);
        if (l == r)
            return id;
        if (lef != m) {
            int c = add(t[id].l, l, mid, nw);
            t[id].l = c;
        } else {
            int c = add(t[id].r, mid + 1, r, nw);
            t[id].r = c;
        }
        return id;
    }

    void add(ll k, ll b)
    {
        root = add(root, lo, hi, {k, b});
    }

    ll query(ll x)
    {
        ll res = LLONG_MAX, l = lo, r = hi;
        for (int id = root; id; ) {
            res = min(res, t[id].ln.eval(x));
            ll mid = l + (r - l) / 2;
            if (x <= mid) {
                id = t[id].l;
                r = mid;
            } else {
                id = t[id].r;
                l = mid + 1;
            }
        }
        return res;
    }
};
