#include <bits/stdc++.h>
using namespace std;
const int ioo = INT_MAX;
const int N   = 1e5 + 5;

int n, m;
vector<int> adj[N];
bool joint[N], seen[N];
int low[N], num[N], timeDfs, cnt_joint, cnt_bridge;

void addEdge(int u, int v)
{
    adj[u].push_back(v);
    adj[v].push_back(u);
}

void inp()
{
    cin >> n >> m; int u, v;
    while(m-- > 0)
        cin >> u >> v,
        addEdge(u, v);
}

void dfs(int u, int pre)
{
    low[u] = num[u] = ++timeDfs; seen[u] = 1;
    int child = 0;

    for (int v : adj[u])
    {
        if (v == pre) continue;
        if (!seen[v])   // gặp cung xuôi
        {
            dfs(v, u);
            low[u] = min(low[u], low[v]);

            if (low[v] == num[v]) ++cnt_bridge;

            ++child; // tăng số lượng con của u

            // nếu u là gốc cây dfs
            if (u == pre) {
                // và nếu u có nhiều hơn 1 con
                if (child > 1)
                    joint[u] = 1; // -> u là khớp
            }

            // ngược lại nếu u không phải là gốc cây
            // nhưng low[v] >= num[u]
            else if (low[v] >= num[u])
                joint[u] = 1; // -> u vẫn sẽ là khớp
        }
        else // gặp cung ngược
            low[u] = min(low[u], num[v]);
    }
}

void solve()
{
    for (int i = 1; i <= n; i++)
        if (!num[i])
            dfs(i, i);

    for (int i = 1; i <= n; i++)
        cnt_joint += joint[i];
    cout << cnt_joint << ' ' << cnt_bridge;
}
