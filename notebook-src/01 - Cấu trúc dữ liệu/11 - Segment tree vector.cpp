// t.query(u, v, val):
// tìm số phần tử trong đoạn LỚN HƠN K
struct MergeSortTree
{
    int n;
    vector<int> a;
    vector<vector<int>> t;

    // arr 1-indexed
    void build(vector<int> &arr)
    {
        a = arr;
        n = (int)a.size() - 1;
        t.assign((n + 1) << 2, {});
        build(1, 1, n);
    }

    void build(int id, int l, int r)
    {
        if (l == r) {t[id].push_back(a[l]); return;}
        int mid = (l + r) / 2;
        build(id*2, l, mid);
        build(id*2 + 1, mid + 1, r);

        int sz1 = t[id*2].size(), sz2 = t[id*2 + 1].size();

        t[id].reserve(sz1 + sz2);
        int i = 0, j = 0;
        while(i < sz1 && j < sz2) {
            if (t[id*2][i] < t[id*2 + 1][j])
                t[id].push_back(t[id*2][i++]);
            else
                t[id].push_back(t[id*2 + 1][j++]);
        }
        while(i < sz1) t[id].push_back(t[id*2][i++]);
        while(j < sz2) t[id].push_back(t[id*2 + 1][j++]);
    }

    int get(int id, int l, int r, int u, int v, int val)
    {
        if (r < u || l > v) return 0;
        if (u <= l && r <= v)
            return int(t[id].end() - upper_bound(t[id].begin(),
              t[id].end(), val));
        int mid = (l + r) / 2;
        return get(id*2, l, mid, u, v, val)
             + get(id*2 + 1, mid + 1, r, u, v, val);
    }

    int query(int u, int v, int val)
    {
        return get(1, 1, n, u, v, val);
    }
};
