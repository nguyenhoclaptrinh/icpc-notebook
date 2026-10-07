// Persistent segment tree đếm theo giá trị, phiên bản i chứa a[1..i]
// Bộ nhớ O(n log n), mỗi query O(log n), online
// t.build(arr):        arr 1-indexed, giá trị bất kỳ (có thể trùng, âm)
// t.kth(l, r, k):      số nhỏ thứ k trong a[l..r] (1 <= k <= r - l + 1)
// t.countLE(l, r, x):  số phần tử <= x trong a[l..r]
//                      (số phần tử > x là (r - l + 1) - countLE(l, r, x))
// Áp dụng: truy vấn số nhỏ thứ k / đếm ≤ x trên đoạn tĩnh, online.
// root[i]: gốc của phiên bản i (root[0] = 0 là cây rỗng)
struct PersistentSegTree
{
    int n, m;
    vector<int> vals, root, lc, rc, cnt;

    void build(vector<int> &arr)
    {
        n = (int)arr.size() - 1;
        vals.assign(arr.begin() + 1, arr.end());
        sort(vals.begin(), vals.end());
        vals.erase(unique(vals.begin(), vals.end()), vals.end());
        m = vals.size();

        lc = {0};
        rc = {0};
        cnt = {0};
        root.assign(n + 1, 0);
        for (int i = 1; i <= n; i++) {
            int pos = lower_bound(vals.begin(), vals.end(), arr[i])
                    - vals.begin() + 1;
            root[i] = insert(root[i - 1], 1, m, pos);
        }
    }

    // tạo bản sao của node prev với cnt tăng 1
    int newNode(int prev)
    {
        lc.push_back(lc[prev]);
        rc.push_back(rc[prev]);
        cnt.push_back(cnt[prev] + 1);
        return (int)cnt.size() - 1;
    }

    int insert(int prev, int l, int r, int pos)
    {
        int cur = newNode(prev);
        if (l == r)
            return cur;
        int mid = (l + r) / 2;
        if (pos <= mid)
            lc[cur] = insert(lc[prev], l, mid, pos);
        else
            rc[cur] = insert(rc[prev], mid + 1, r, pos);
        return cur;
    }

    int kth(int l, int r, int k)
    {
        int a = root[l - 1], b = root[r], lo = 1, hi = m;
        while (lo < hi) {
            int mid = (lo + hi) / 2;
            int c = cnt[lc[b]] - cnt[lc[a]];
            if (k <= c) {
                a = lc[a];
                b = lc[b];
                hi = mid;
            } else {
                k -= c;
                a = rc[a];
                b = rc[b];
                lo = mid + 1;
            }
        }
        return vals[lo - 1];
    }

    // số phần tử có chỉ số giá trị (đã nén) <= p
    int get(int a, int b, int lo, int hi, int p)
    {
        if (p < lo || a == b)
            return 0;
        if (hi <= p)
            return cnt[b] - cnt[a];
        int mid = (lo + hi) / 2;
        int res = get(lc[a], lc[b], lo, mid, p);
        if (p > mid)
            res += get(rc[a], rc[b], mid + 1, hi, p);
        return res;
    }

    int countLE(int l, int r, int x)
    {
        int p = upper_bound(vals.begin(), vals.end(), x) - vals.begin();
        return get(root[l - 1], root[r], 1, m, p);
    }
};
