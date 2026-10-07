// t.build(n, m, k):                khối n x m x k (1-indexed), toàn 0
// t.update(x, y, z, w):            a[x][y][z] += w
// t.query(x1, y1, z1, x2, y2, z2): tổng (x1, y1, z1) - (x2, y2, z2)
struct Fenwick3D
{
    int n, m, k;
    vector<vector<vector<ll>>> t;

    void build(int _n, int _m, int _k)
    {
        n = _n;
        m = _m;
        k = _k;
        t.assign(n + 1, vector<vector<ll>>(m + 1, vector<ll>(k + 1, 0)));
    }

    void update(int x, int y, int z, ll w)
    {
        for (int i = x; i <= n; i += i & -i)
            for (int j = y; j <= m; j += j & -j)
                for (int l = z; l <= k; l += l & -l)
                    t[i][j][l] += w;
    }

    ll prefix(int x, int y, int z)
    {
        ll s = 0;
        for (int i = x; i > 0; i -= i & -i)
            for (int j = y; j > 0; j -= j & -j)
                for (int l = z; l > 0; l -= l & -l)
                    s += t[i][j][l];
        return s;
    }

    ll query(int x1, int y1, int z1, int x2, int y2, int z2)
    {
        ll res = 0;
        for (int mask = 0; mask < 8; mask++) {
            ll v = prefix(mask & 1 ? x1 - 1 : x2,
                          mask & 2 ? y1 - 1 : y2,
                          mask & 4 ? z1 - 1 : z2);
            res += __builtin_popcount(mask) & 1 ? -v : v;
        }
        return res;
    }
};
