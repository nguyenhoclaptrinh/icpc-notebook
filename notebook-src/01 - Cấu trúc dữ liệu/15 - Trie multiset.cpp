// Trie nhị phân multiset — order statistics trên số nguyên [0, 2^(BITS+1))
// Dấu hiệu: "số thứ k", "đếm/tổng các số <= x", "tổng k số nhỏ nhất".
// Cách gọi: t.insertNum(x); t.removeNum(x) (x vắng -> bỏ qua);
//   t.rank(k) với k 1-based (VD {1,1,5}: rank(2) == 1);
//   t.countLE(x); t.sumLE(x); t.sumRankLE(k) = tổng k số nhỏ nhất.
// Độ phức tạp: O(BITS) ~ O(log Amax) mỗi op.
// Lưu ý: BITS = 18 chỉ tới 2^19-1 (cần 1e9 thì đổi BITS = 30);
//   x phải >= 0; rank/sumRankLE yêu cầu 1 <= k <= size.
struct TrieMultiset
{
    static const int BITS = 18;
    struct Node {int next[2] = {0, 0}, p = 0, stop = 0, cnt = 0; ll sum = 0;};
    vector<Node> t;

    TrieMultiset() { t.assign(1, Node()); } // node 0 = root

    // thêm x.
    void insertNum(int x)
    {
        int v = 0;
        for (int i = BITS; i >= 0; --i) {
            int k = (x >> i) & 1;
            if (t[v].next[k] == 0) {
                t[v].next[k] = (int)t.size();
                t.push_back(Node());
                t.back().p = v;
            }
            v = t[v].next[k];
        }
        ++t[v].stop;
        while (v) ++t[v].cnt, t[v].sum += x, v = t[v].p;
        ++t[v].cnt;
        t[v].sum += x;
    }

    // xóa 1 bản sao x (vắng -> bỏ qua).
    void removeNum(int x)
    {
        int v = 0;
        for (int i = BITS; i >= 0; --i) {
            int k = (x >> i) & 1;
            if (t[v].next[k] == 0)
                return;
            v = t[v].next[k];
        }
        if (t[v].stop == 0) return; // x không tồn tại -> không xóa
        --t[v].stop;
        while (v) --t[v].cnt, t[v].sum -= x, v = t[v].p;
        --t[v].cnt;
        t[v].sum -= x;
    }

    // số thứ k (k 1-based, cần 1 <= k <= size).
    int rank(int k)
    {
        if (k < 1 || k > t[0].cnt) return -1;
        int v = 0, x = 0;
        for (int i = BITS; i >= 0; --i) {
            int C0 = (t[v].next[0]) ? t[t[v].next[0]].cnt : 0;
            if (k > C0) {
                x |= (1 << i);
                k -= C0;
                v = t[v].next[1];
            }
            else
                v = t[v].next[0];
        }
        return x;
    }

    // tổng các số <= x.
    ll sumLE(int x)
    {
        int v = 0;
        ll res = 0;
        for (int i = BITS; i >= 0; --i) {
            int k = (x >> i) & 1;
            if (k && t[v].next[0])
                res += t[t[v].next[0]].sum;
            if (t[v].next[k] == 0)
                return res;
            v = t[v].next[k];
        }
        res += t[v].sum;
        return res;
    }

    // tổng k số nhỏ nhất (k 1-based, cần 1 <= k <= size).
    ll sumRankLE(int k)
    {
        if (k < 1 || k > t[0].cnt) return 0;
        int v = 0;
        ll res = 0;
        for (int i = BITS; i >= 0; --i) {
            int C0 = (t[v].next[0]) ? t[t[v].next[0]].cnt : 0;
            ll T0 = (t[v].next[0]) ? t[t[v].next[0]].sum : 0;
            if (k > C0) {
                res += T0;
                k -= C0;
                v = t[v].next[1];
            }
            else
                v = t[v].next[0];
        }
        res += t[v].sum / t[v].stop * k;
        return res;
    }

    // đếm số <= x.
    int countLE(int x)
    {
        int v = 0;
        int res = 0;
        for (int i = BITS; i >= 0; --i) {
            int k = (x >> i) & 1;
            if (k && t[v].next[0])
                res += t[t[v].next[0]].cnt;
            if (t[v].next[k] == 0)
                return res;
            v = t[v].next[k];
        }
        res += t[v].stop;
        return res;
    }
};
