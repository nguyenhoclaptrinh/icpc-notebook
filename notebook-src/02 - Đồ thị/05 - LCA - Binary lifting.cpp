// LCA và max trọng số các đỉnh trên đường đi u - v (không có update)
// Muốn min / tổng / gcd: sửa hàm comb và NEG (min: INT_MAX, tổng, gcd: 0)
// t.build(n, adj, w):  adj[1..n]: danh sách kề, w[1..n]: trọng số đỉnh,
//                      gốc là đỉnh 1. O(n log n)
// t.findLCA(u, v):     LCA của u và v, O(log n)
// t.query(u, v):       max w trên đường đi u - v, O(log n)
// h[i]: độ cao của i (h[root] = 1, h[0] = 0)
// up[i][j]: tổ tiên thứ 2^j của i (0 nếu không tồn tại)
// mx[i][j]: max w trên 2^j đỉnh bắt đầu từ i đi lên (không tính up[i][j])
struct LCA
{
    static constexpr int LOG = 20; // 2^LOG > n
    static constexpr int NEG = INT_MIN;

    int n;
    vector<vector<int>> adj;
    vector<int> w, h;
    vector<array<int, LOG>> up, mx;

    int comb(int a, int b)
    {
        return max(a, b);
    }

    void build(int _n, vector<vector<int>> &_adj, vector<int> &_w)
    {
        n = _n;
        adj = _adj;
        w = _w;
        h.assign(n + 1, 0);
        up.assign(n + 1, {});
        mx.assign(n + 1, {});
        mx[0].fill(NEG);
        dfs(1, 0);
    }

    // dfs đỉnh u có cha là đỉnh p
    void dfs(int u, int p)
    {
        h[u] = h[p] + 1;
        up[u][0] = p;
        mx[u][0] = w[u];
        for (int j = 1; j < LOG; j++) {
            up[u][j] = up[up[u][j - 1]][j - 1];
            mx[u][j] = comb(mx[u][j - 1], mx[up[u][j - 1]][j - 1]);
        }
        for (int &v : adj[u])
            if (v != p)
                dfs(v, u);
    }

    int findLCA(int u, int v)
    {
        if (h[u] < h[v])
            swap(u, v);
        for (int j = 0; j < LOG; j++)
            if ((h[u] - h[v]) >> j & 1)
                u = up[u][j];
        if (u == v)
            return u;

        for (int j = LOG - 1; j >= 0; j--)
            if (up[u][j] != up[v][j]) {
                u = up[u][j];
                v = up[v][j];
            }
        return up[u][0];
    }

    int query(int u, int v)
    {
        int res = NEG;
        if (h[u] < h[v])
            swap(u, v);
        for (int j = 0; j < LOG; j++)
            if ((h[u] - h[v]) >> j & 1) {
                res = comb(res, mx[u][j]);
                u = up[u][j];
            }
        if (u == v)
            return comb(res, w[u]);

        for (int j = LOG - 1; j >= 0; j--)
            if (up[u][j] != up[v][j]) {
                res = comb(res, comb(mx[u][j], mx[v][j]));
                u = up[u][j];
                v = up[v][j];
            }
        // u, v là con của LCA
        return comb(comb(res, comb(w[u], w[v])), w[up[u][0]]);
    }
};
