// t.query(u, v):    tổng đoạn [u..v]
// t.update(p, val): a[p] = val
struct SegTree
{
    int n;
    vector<int> t, a;

    // arr 1-indexed
    void build(vector<int> &arr)
    {
        a = arr;
        n = (int)a.size() - 1;
        t.assign((n + 1) << 2, 0);
        build(1, 1, n);
    }

    void build(int id, int l, int r)
    {
        if (l == r) {t[id] = a[l]; return;}
        int mid = (l + r) / 2;
        build(id*2, l, mid);
        build(id*2 + 1, mid + 1, r);
        t[id] = t[id*2] + t[id*2 + 1];
    }

    int get(int id, int l, int r, int u, int v)
    {
        if (r < u || l > v) return 0;
        if (u <= l && r <= v) return t[id];
        int mid = (l + r) / 2;
        return get(id*2, l, mid, u, v)
             + get(id*2 + 1, mid + 1, r, u, v);
    }

    void upd(int id, int l, int r, int p, int val)
    {
        if (p < l || p > r) return;
        if (l == r) return void(t[id] = a[p] = val);
        int mid = (l + r) / 2;
        upd(id*2, l, mid, p, val);
        upd(id*2 + 1, mid + 1, r, p, val);
        t[id] = t[id*2] + t[id*2 + 1];
    }

    int query(int u, int v)
    {
        return get(1, 1, n, u, v);
    }

    void update(int p, int val)
    {
        upd(1, 1, n, p, val);
    }
};
