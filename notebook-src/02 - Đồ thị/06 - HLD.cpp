// HLD: update điểm + hỏi max trên đường đi / cây con (đỉnh 1-based, gốc 1)
// Dấu hiệu: cây N,Q tới 2e5, "update w[u]" + "hỏi max trên u-v / subtree".
//   VD: queryPath(2, 3) với w = {_,10,20,30} -> 30.
// Bẫy: dfs đệ quy — cây lệch N=2e5 có thể tràn stack; sum cần đổi sang long long.
// t.build(n, adj, w); t.update(u, val); t.queryPath(u, v); t.querySub(u).
// par, h, sz: cha, độ cao (h[root] = 1), kích thước cây con
// pos[i]: vị trí của i trên segment tree (0-indexed), cây con i là
//         đoạn [pos[i], pos[i] + sz[i] - 1]
// Khi cần truy vấn cạnh, đặt w[v] = trọng số (par[v], v) và:
// int l = t.findLCA(u, v), old = t.w[l];
// t.update(l, NEG);
// int res = t.queryPath(u, v);
// t.update(l, old);
struct HLD
{
    static constexpr int NEG = INT_MIN;

    int n, cur;
    vector<vector<int>> adj;
    vector<int> w, par, h, sz, heavy, head, pos, t;

    int comb(int a, int b)
    {
        return max(a, b);
    }

    // dựng O(n); adj,w 1-based [1..n]; gốc cứng đỉnh 1.
    void build(int _n, vector<vector<int>> &_adj, vector<int> &_w)
    {
        n = _n;
        adj = _adj;
        w = _w;
        par.assign(n + 1, 0);
        h.assign(n + 1, 0);
        sz.assign(n + 1, 0);
        heavy.assign(n + 1, 0);
        head.assign(n + 1, 0);
        pos.assign(n + 1, 0);
        cur = 0;
        dfs1(1, 0);
        dfs2(1, 1);

        t.assign(2 * n, NEG);
        for (int i = 1; i <= n; i++)
            t[n + pos[i]] = w[i];
        for (int i = n - 1; i >= 1; i--)
            t[i] = comb(t[i * 2], t[i * 2 + 1]);
    }

    void dfs1(int u, int p)
    {
        par[u] = p;
        h[u] = h[p] + 1;
        sz[u] = 1;
        for (int &v : adj[u])
            if (v != p) {
                dfs1(v, u);
                sz[u] += sz[v];
                if (sz[v] > sz[heavy[u]])
                    heavy[u] = v;
            }
    }

    // đỉnh u thuộc chuỗi có đầu là hd
    void dfs2(int u, int hd)
    {
        head[u] = hd;
        pos[u] = cur++;
        if (heavy[u])
            dfs2(heavy[u], hd);
        for (int &v : adj[u])
            if (v != par[u] && v != heavy[u])
                dfs2(v, v);
    }

    // w[u] = val, O(log n).
    void update(int u, int val)
    {
        w[u] = val;
        int p = pos[u] + n;
        for (t[p] = val; p > 1; p >>= 1)
            t[p >> 1] = comb(t[p], t[p ^ 1]);
    }

    // kết quả trên đoạn [l, r] của segment tree
    int get(int l, int r)
    {
        int res = NEG;
        for (l += n, r += n + 1; l < r; l >>= 1, r >>= 1) {
            if (l & 1) res = comb(res, t[l++]);
            if (r & 1) res = comb(res, t[--r]);
        }
        return res;
    }

    // max trên u-v gồm LCA, O(log^2 n).
    int queryPath(int u, int v)
    {
        int res = NEG;
        while (head[u] != head[v]) {
            if (h[head[u]] < h[head[v]])
                swap(u, v);
            res = comb(res, get(pos[head[u]], pos[u]));
            u = par[head[u]];
        }
        if (h[u] > h[v])
            swap(u, v);
        return comb(res, get(pos[u], pos[v]));
    }

    // LCA của u,v, O(log n).
    int findLCA(int u, int v)
    {
        while (head[u] != head[v]) {
            if (h[head[u]] < h[head[v]])
                swap(u, v);
            u = par[head[u]];
        }
        return h[u] < h[v] ? u : v;
    }

    // max cây con u, O(log n).
    int querySub(int u)
    {
        return get(pos[u], pos[u] + sz[u] - 1);
    }
};
