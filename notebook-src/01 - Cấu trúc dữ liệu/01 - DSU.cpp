// t.build(n):     n đỉnh 1..n, mỗi đỉnh là một tập riêng
// t.find(x):      đại diện của tập chứa x
// t.unite(a, b):  gộp 2 tập, trả về false nếu đã cùng tập
// t.same(a, b):   a, b có cùng tập không
// t.size(x):      số phần tử của tập chứa x
// t.comps:        số tập hiện có
// Độ phức tạp mỗi thao tác: O(alpha(n))
struct DSU
{
    int n, comps;
    vector<int> p, sz;

    void build(int _n)
    {
        n = comps = _n;
        p.resize(n + 1);
        iota(p.begin(), p.end(), 0);
        sz.assign(n + 1, 1);
    }

    int find(int x)
    {
        while (p[x] != x) {
            p[x] = p[p[x]];
            x = p[x];
        }
        return x;
    }

    bool unite(int a, int b)
    {
        a = find(a);
        b = find(b);
        if (a == b) return false;
        if (sz[a] < sz[b]) swap(a, b);
        p[b] = a;
        sz[a] += sz[b];
        comps--;
        return true;
    }

    bool same(int a, int b)
    {
        return find(a) == find(b);
    }

    int size(int x)
    {
        return sz[find(x)];
    }
};
