// t.update(x, y, w):       thay giá trị tại ô (x, y) thành w
// t.query(x1, y1, x2, y2): tính max HCN (x1, y1) - (x2, y2)
struct SegTree2D
{
    int n, m;
    vector<vector<ll>> a, t;

    // arr 1-indexed: arr[1..n][1..m]
    void build(vector<vector<ll>> &arr)
    {
        n = (int)arr.size() - 1;
        m = (int)arr[1].size() - 1;
        a = arr;
        t.assign((n + 1) << 2, vector<ll>((m + 1) << 2, LLONG_MIN));
        buildx(1, 1, n);
    }

    void buildy(int idX, int lx, int rx, int idY, int ly, int ry)
    {
        if (ly == ry) {
            if (lx == rx)
                return void(t[idX][idY] = a[lx][ly]);
            else
                return void(t[idX][idY] = max(t[idX*2][idY],
                  t[idX*2 + 1][idY]));
        }

        int mid = (ly + ry) / 2;
        buildy(idX, lx, rx, idY*2, ly, mid);
        buildy(idX, lx, rx, idY*2 + 1, mid + 1, ry);

        t[idX][idY] = max(t[idX][idY*2], t[idX][idY*2 + 1]);
    }

    void buildx(int idX, int lx, int rx)
    {
        if (lx == rx) {
            buildy(idX, lx, rx, 1, 1, m);
            return;
        }

        int mid = (lx + rx) / 2;
        buildx(idX*2, lx, mid);
        buildx(idX*2 + 1, mid + 1, rx);

        buildy(idX, lx, rx, 1, 1, m);
    }

    void updy(int idX, int lx, int rx, int idY, int ly, int ry,
              int x, int y, ll val)
    {
        if (ly == ry) {
            if (lx == rx)
                return void(t[idX][idY] = val);
            else
                return void(t[idX][idY] = max(t[idX*2][idY],
                  t[idX*2 + 1][idY]));
        }

        int mid = (ly + ry) / 2;
        if (ly <= y && y <= mid)
            updy(idX, lx, rx, idY*2, ly, mid, x, y, val);
        else
            updy(idX, lx, rx, idY*2 + 1, mid + 1, ry, x, y, val);

        t[idX][idY] = max(t[idX][idY*2], t[idX][idY*2 + 1]);
    }

    void updx(int idX, int lx, int rx, int x, int y, ll val)
    {
        if (lx == rx) {
            updy(idX, lx, rx, 1, 1, m, x, y, val);
            return;
        }

        int mid = (lx + rx) / 2;
        if (lx <= x && x <= mid)
            updx(idX*2, lx, mid, x, y, val);
        else
            updx(idX*2 + 1, mid + 1, rx, x, y, val);

        updy(idX, lx, rx, 1, 1, m, x, y, val);
    }

    ll gety(int idX, int idY, int ly, int ry, int y1, int y2)
    {
        if (ry < y1 || y2 < ly) return LLONG_MIN;

        if (ly == ry)
            return t[idX][idY];
        if (y1 <= ly && ry <= y2)
            return t[idX][idY];

        int mid = (ly + ry) / 2;
        ll t1 = gety(idX, idY*2, ly, mid, y1, y2),
           t2 = gety(idX, idY*2 + 1, mid + 1, ry, y1, y2);

        return max(t1, t2);
    }

    ll getx(int idX, int lx, int rx, int x1, int y1, int x2, int y2)
    {
        if (rx < x1 || x2 < lx) return LLONG_MIN;

        if (lx == rx)
            return gety(idX, 1, 1, m, y1, y2);
        if (x1 <= lx && rx <= x2)
            return gety(idX, 1, 1, m, y1, y2);

        int mid = (lx + rx) / 2;
        ll t1 = getx(idX*2, lx, mid, x1, y1, x2, y2),
           t2 = getx(idX*2 + 1, mid + 1, rx, x1, y1, x2, y2);

        return max(t1, t2);
    }

    void update(int x, int y, ll val)
    {
        updx(1, 1, n, x, y, val);
    }

    ll query(int x1, int y1, int x2, int y2)
    {
        return getx(1, 1, n, x1, y1, x2, y2);
    }
};
