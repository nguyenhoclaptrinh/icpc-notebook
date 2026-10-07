// t.update(u, v, val): cộng val  [u..v]
// t.query(u, v):       tìm max đoạn [u..v]
struct LazySegTree
{
    struct Node {int val = 0, laz = 0;};
    int n;
    vector<Node> t;

    void build(int n_)
    {
        n = n_;
        t.assign((n + 1) << 2, Node());
    }

    void down(int id)
    {
        t[id*2].val     += t[id].laz;
        t[id*2].laz     += t[id].laz;
        t[id*2 + 1].val += t[id].laz;
        t[id*2 + 1].laz += t[id].laz;
        t[id].laz = 0;
    }

    void upd(int id, int l, int r, int u, int v, int val)
    {
        if (u > r || v < l) return;
        if (u <= l && r <= v) {
            t[id].val += val;
            t[id].laz += val;
            return;
        }

        down(id);

        int mid = (l + r) / 2;
        upd(id*2, l, mid, u, v, val);
        upd(id*2 + 1, mid + 1, r, u, v, val);

        t[id].val = max(t[id*2].val, t[id*2 + 1].val);
    }

    int get(int id, int l, int r, int u, int v)
    {
        if (u > r || v < l) return INT_MIN;
        if (u <= l && r <= v)
            return t[id].val;

        int mid = (l + r) / 2;
        down(id);

        return max(get(id*2, l, mid, u, v),
                   get(id*2 + 1, mid + 1, r, u, v));
    }

    void update(int u, int v, int val)
    {
        upd(1, 1, n, u, v, val);
    }

    int query(int u, int v)
    {
        return get(1, 1, n, u, v);
    }
};
