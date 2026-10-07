// Cần DSU
#include <bits/stdc++.h>
using namespace std;
const int N = 5e5 + 5;

int p, n, m;
DSU dsu;

// {u, v, weight, index}
pair<pair<int, int>, pair<int, int>> edge[N];

void Inp()
{
    cin >> p;
    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        // u, v, w
        cin >> edge[i].second.first >>
               edge[i].second.second >>
               edge[i].first.first;
        edge[i].first.second = i;
    }
}

void Solve()
{
    dsu.build(n);
    sort(edge + 1, edge + m + 1);
    vector<int> res;
    for (int i = 1; i <= m; i++) {
        if (!dsu.unite(edge[i].second.first, edge[i].second.second))
            continue;

        res.push_back(edge[i].first.second);
        if (res.size() == n - 1) break;
    }
    for (int &x : res) cout << x << ' ';
}
