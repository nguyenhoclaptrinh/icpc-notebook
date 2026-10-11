// Li Chao động — thêm đường y = k*x + b, hỏi min tại x (không cần nén tọa độ)
// Dấu hiệu: dp[i] = min_j(m[j]*x[i] + b[j]) mà x[i] KHÔNG đơn điệu.
//   VD: build(-1e9,1e9); add(2,3); query(10) = 23.
// Độ phức tạp: O(log(HI-LO)) mỗi op, mỗi add tạo <= 1 node.
// Lưu ý: chỉ min; miền x nguyên rời rạc.
struct LiChao
{
    struct Line
    {
        ll k, b;
        // k*x+b, clamp về ll (input vừa trong ll).
        ll eval(ll x) {
            __int128 v = (__int128)k * x + b;
            if (v > LLONG_MAX) return LLONG_MAX;
            if (v < LLONG_MIN) return LLONG_MIN;
            return (ll)v;
        }
    };

    struct Node
    {
        Line ln;
        int l, r;
    };

    ll lo, hi;
    int root;
    vector<Node> t;

    // gọi trước; mọi x query trong [lo,hi].
    void build(ll _lo, ll _hi)
    {
        lo = _lo;
        hi = _hi;
        root = 0;
        t.assign(1, {{0, 0}, 0, 0}); // node 0: rỗng
    }

    // chèn đường vào node đoạn [l,r].
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

    // thêm đường y=k*x+b.
    void add(ll k, ll b)
    {
        root = add(root, lo, hi, {k, b});
    }

    // min tại x (ngoài [lo,hi] sai câm); rỗng -> LLONG_MAX.
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
