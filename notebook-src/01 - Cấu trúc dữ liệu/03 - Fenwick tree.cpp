// t.build(n):     khởi tạo mảng n phần tử (1-indexed), toàn 0
// t.build(arr):   khởi tạo từ arr[1..n] trong O(n)
// t.update(i, w): a[i] += w
// t.query(i):     tổng a[1..i]
// t.query(l, r):  tổng a[l..r]
// t.lower_bound(s): i nhỏ nhất sao cho a[1] + ... + a[i] >= s
//                 (n + 1 nếu không tồn tại). Yêu cầu a[i] >= 0.
//                 Nếu a[i] = số lần i xuất hiện, đây là phần tử thứ s
struct Fenwick
{
    int n, lg;
    vector<ll> t;

    void build(int _n)
    {
        n = _n;
        t.assign(n + 1, 0);
        for (lg = 1; lg * 2 <= n; lg *= 2);
    }

    // arr 1-indexed: arr[1..n]
    void build(vector<ll> &arr)
    {
        n = (int)arr.size() - 1;
        t = arr;
        for (int i = 1; i <= n; i++) {
            int j = i + (i & -i);
            if (j <= n) t[j] += t[i];
        }
        for (lg = 1; lg * 2 <= n; lg *= 2);
    }

    void update(int i, ll w)
    {
        for (; i <= n; i += i & -i) t[i] += w;
    }

    ll query(int i)
    {
        ll s = 0;
        for (; i > 0; i -= i & -i) s += t[i];
        return s;
    }

    ll query(int l, int r)
    {
        return query(r) - query(l - 1);
    }

    int lower_bound(ll s)
    {
        int pos = 0;
        for (int pw = lg; pw > 0; pw >>= 1) {
            if (pos + pw <= n && t[pos + pw] < s) {
                pos += pw;
                s -= t[pos];
            }
        }
        return pos + 1;
    }
};
