// t.build(n, m):               bảng n x m (1-indexed), toàn 0
// t.update(x1, y1, x2, y2, w): cộng w vào HCN (x1, y1) - (x2, y2)
// t.prefix(x, y):              tổng HCN (1, 1) - (x, y)
// t.query(x1, y1, x2, y2):     tổng HCN (x1, y1) - (x2, y2)
struct Fenwick2D
{
    int n, m;
    vector<vector<array<ll, 4>>> t;

    void build(int _n, int _m)
    {
        n = _n;
        m = _m;
        t.assign(n + 1, vector<array<ll, 4>>(m + 1, {0, 0, 0, 0}));
    }

    // d(x, y) += w, với d là mảng sai phân 2D
    void add(int x, int y, ll w)
    {
        ll v[4] = {w, w * x, w * y, w * x * y};
        for (int i = x; i <= n; i += i & -i)
            for (int j = y; j <= m; j += j & -j)
                for (int k = 0; k < 4; k++)
                    t[i][j][k] += v[k];
    }

    ll prefix(int x, int y)
    {
        ll s[4] = {0, 0, 0, 0};
        for (int i = x; i > 0; i -= i & -i)
            for (int j = y; j > 0; j -= j & -j)
                for (int k = 0; k < 4; k++)
                    s[k] += t[i][j][k];
        return (ll)(x + 1) * (y + 1) * s[0] - (ll)(y + 1) * s[1]
             - (ll)(x + 1) * s[2] + s[3];
    }

    void update(int x1, int y1, int x2, int y2, ll w)
    {
        add(x1, y1, w);
        add(x1, y2 + 1, -w);
        add(x2 + 1, y1, -w);
        add(x2 + 1, y2 + 1, w);
    }

    ll query(int x1, int y1, int x2, int y2)
    {
        return prefix(x2, y2) - prefix(x1 - 1, y2)
             - prefix(x2, y1 - 1) + prefix(x1 - 1, y1 - 1);
    }
};
