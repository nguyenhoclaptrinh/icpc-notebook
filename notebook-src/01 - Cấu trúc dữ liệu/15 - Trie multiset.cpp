// multiset dùng trie nhị phân, giá trị x phải nằm trong [0, 2^19)
// t.insertNum(x): thêm x vào multiset
// t.removeNum(x): bỏ x khỏi multiset
// t.rank(k):      tìm số đứng thứ k
// t.sumLE(x):     tổng các số <= x
// t.sumRankLE(k): tổng k số nhỏ nhất
// t.countLE(x):   đếm số lượng số <= x
struct TrieMultiset
{
    static const int BITS = 18;
    struct Node {int next[2] = {0, 0}, p = 0, stop = 0, cnt = 0; ll sum = 0;};
    vector<Node> t;

    TrieMultiset() { t.assign(1, Node()); } // node 0 = root

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

    int rank(int k)
    {
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

    ll sumRankLE(int k)
    {
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
