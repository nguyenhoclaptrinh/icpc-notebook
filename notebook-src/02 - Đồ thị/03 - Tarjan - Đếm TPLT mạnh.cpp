// TARJAN — đếm thành phần liên thông mạnh (SCC) trên đồ thị CÓ HƯỚNG, O(n + m)
// Cách gọi: addEdge(u, v) 1-index; Solve() -> in số SCC. Gọi Solve() 1 lần duy nhất
//   (mảng num/low/deleted dùng chung, không tự reset cho test thứ 2).
using namespace std;
const int N = 1e5 + 5;

int numNode; // number of nodes
vector<int> adj[N];
int low[N], num[N], timeDfs, cnt_TPLT;
bool deleted[N];
stack<int> st;

// directed graph
void addEdge(int u, int v)
{
    adj[u].push_back(v);
}

void tarjan(int u)
{
    low[u] = num[u] = ++timeDfs;
    st.push(u);
    for (int v : adj[u]) {
        if (deleted[v]) continue;
        if (!num[v])
            tarjan(v),
            low[u] = min(low[u], low[v]);
        else
            low[u] = min(low[u], num[v]);
    }

    if (low[u] == num[u]) {
        ++cnt_TPLT;
        int v = numNode + 1; // set v = inf
        do {
            v = st.top(); st.pop();
            deleted[v] = 1;
        }
        while(v != u);
    }

}

void Solve()
{
    for (int i = 1; i <= numNode; i++)
        if (!num[i])
            tarjan(i);
    cout << cnt_TPLT; // đếm thành phần liên thông mạnh
}
