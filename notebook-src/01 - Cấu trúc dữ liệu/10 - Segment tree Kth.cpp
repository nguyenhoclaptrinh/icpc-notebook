// t.queryKthPos(u, v, k):
// tìm vị trí số nhỏ thứ Kth trong đoạn [L, R]
struct KthSegTree
{
    int n;
    vector<pair<int,int>> a; // (value, position)
    vector<vector<int>> t;   // positions, sorted

    // arr 1-indexed, giá trị đôi một khác nhau
    void build(vector<int> &arr)
    {
        n = (int)arr.size() - 1;
        a.resize(n + 1);
        for (int i = 1; i <= n; i++) a[i] = {arr[i], i};
        sort(a.begin() + 1, a.end());

        t.assign((n + 1) << 2, {});
        build(1, 1, n);
    }

    void build(int id, int l, int r)
    {
        if (l == r) return void(t[id].push_back(a[l].second));
        int mid = (l + r) / 2;
        build(id*2, l, mid);
        build(id*2 + 1, mid + 1, r);
        merge(t[id*2].begin(), t[id*2].end(),
              t[id*2+1].begin(), t[id*2+1].end(), back_inserter(t[id]));
    }

    int get(int id, int l, int r, int u, int v, int kth)
    {
        if (l == r) return t[id].back();
        int cnt = upper_bound(t[id*2].begin(), t[id*2].end(), v)
                - lower_bound(t[id*2].begin(), t[id*2].end(), u);

        int mid = (l + r) / 2;
        if (cnt >= kth)
            return get(id*2, l, mid, u, v, kth);
        else
            return get(id*2 + 1, mid + 1, r, u, v, kth - cnt);
    }

    int queryKthPos(int u, int v, int k)
    {
        return get(1, 1, n, u, v, k);
    }
};
