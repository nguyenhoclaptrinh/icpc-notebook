// Heavy-Light Decomposition: max trọng số đỉnh trên đường đi, có update
// Muốn min / tổng / gcd: sửa hàm comb và NEG (min: INT_MAX, tổng, gcd: 0)
// (phép toán phải giao hoán)
// t.build(n, adj, w):  adj[1..n]: danh sách kề, w[1..n]: trọng số đỉnh,
//                      gốc là đỉnh 1. O(n)
// t.update(u, val):    w[u] = val, O(log n)
// t.queryPath(u, v):   max w trên các đỉnh của đường đi u - v
//                      (gồm cả u, v và LCA), O(log^2 n)
// t.querySub(u):       max w trên các đỉnh của cây con u (gồm cả u),
//                      O(log n)
// t.findLCA(u, v):     LCA của u và v, O(log n)
// par, h, sz: cha, độ cao (h[root] = 1), kích thước cây con
// heavy[i]: con có cây con lớn nhất (0 nếu là lá)
// head[i]: đỉnh trên cùng của chuỗi chứa i
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

    int findLCA(int u, int v)
    {
        while (head[u] != head[v]) {
            if (h[head[u]] < h[head[v]])
                swap(u, v);
            u = par[head[u]];
        }
        return h[u] < h[v] ? u : v;
    }

    int querySub(int u)
    {
        return get(pos[u], pos[u] + sz[u] - 1);
    }
};
