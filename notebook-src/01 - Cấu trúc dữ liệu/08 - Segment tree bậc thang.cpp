// t.update(u, v, f, d): a[u + k] += f + k * d, với k = 0..v-u
//                       (bậc thang a[u] += 1, a[u+1] += 2, ...: f = d = 1;
//                        cộng thường val: f = val, d = 0)
// t.query(u, v):        tổng đoạn [u..v] (giá trị một ô: query(i, i)), O(log n)
// Lazy (a, b): cộng a + b * i vào mỗi phần tử i của đoạn
struct StairSegTree
{
    struct Node {ll sum = 0, a = 0, b = 0;};
    int n;
    vector<Node> t;

    void build(int n_)
    {
        n = n_;
        t.assign((n + 1) << 2, Node());
    }

    void apply(int id, int l, int r, ll a, ll b)
    {
        ll len = r - l + 1;
        t[id].sum += a * len + b * ((ll)(l + r) * len / 2);
        t[id].a += a;
        t[id].b += b;
    }

    void down(int id, int l, int r)
    {
        int mid = (l + r) / 2;
        apply(id*2, l, mid, t[id].a, t[id].b);
        apply(id*2 + 1, mid + 1, r, t[id].a, t[id].b);
        t[id].a = t[id].b = 0;
    }

    void upd(int id, int l, int r, int u, int v, ll a, ll b)
    {
        if (u > r || v < l) return;
        if (u <= l && r <= v)
            return apply(id, l, r, a, b);

        down(id, l, r);

        int mid = (l + r) / 2;
        upd(id*2, l, mid, u, v, a, b);
        upd(id*2 + 1, mid + 1, r, u, v, a, b);

        t[id].sum = t[id*2].sum + t[id*2 + 1].sum;
    }

    ll get(int id, int l, int r, int u, int v)
    {
        if (u > r || v < l) return 0;
        if (u <= l && r <= v)
            return t[id].sum;

        down(id, l, r);

        int mid = (l + r) / 2;
        return get(id*2, l, mid, u, v) + get(id*2 + 1, mid + 1, r, u, v);
    }

    void update(int u, int v, ll f, ll d)
    {
        upd(1, 1, n, u, v, f - d * u, d);
    }

    ll query(int u, int v)
    {
        return get(1, 1, n, u, v);
    }
};
