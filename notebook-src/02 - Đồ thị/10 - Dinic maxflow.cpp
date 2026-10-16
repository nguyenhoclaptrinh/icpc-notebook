// DINIC — luồng cực đại / lát cắt cực tiểu, O(V²E)
// Dấu hiệu: "luồng cực đại", "lát cắt cực tiểu", "ghép cặp có sức chứa".
//   VD: addEdge(s,t,cap); maxflow(s,t) -> giá trị luồng.
// Bẫy: tự thêm cạnh ngược cap 0; cap long long; đỉnh 0-index; INF đủ lớn.
struct Dinic {
    struct Edge { int to; long long cap; int rev; };
    int n;
    vector<vector<Edge>> g;
    vector<int> level, it;
    Dinic(int n = 0) { init(n); }
    // tạo mới n đỉnh 0-index.
    void init(int n_) { n = n_; g.assign(n, {}); }
    // thêm cạnh u->v sức chứa cap.
    void addEdge(int u, int v, long long cap) {
        g[u].push_back({v, cap, (int)g[v].size()});
        g[v].push_back({u, 0, (int)g[u].size() - 1});
    }
    bool bfs(int s, int t) {
        level.assign(n, -1);
        queue<int> q;
        level[s] = 0; q.push(s);
        while (!q.empty()) {
            int v = q.front(); q.pop();
            for (auto &e : g[v])
                if (e.cap > 0 && level[e.to] < 0) {
                    level[e.to] = level[v] + 1; q.push(e.to);
                }
        }
        return level[t] >= 0;
    }
    long long dfs(int v, int t, long long f) {
        if (v == t) return f;
        for (int &i = it[v]; i < (int)g[v].size(); i++) {
            Edge &e = g[v][i];
            if (e.cap > 0 && level[v] < level[e.to]) {
                long long d = dfs(e.to, t, min(f, e.cap));
                if (d > 0) { e.cap -= d; g[e.to][e.rev].cap += d; return d; }
            }
        }
        return 0;
    }
    // giá trị luồng cực đại s->t.
    long long maxflow(int s, int t) {
        long long flow = 0, INF = (long long)4e18, f;
        while (bfs(s, t)) {
            it.assign(n, 0);
            while ((f = dfs(s, t, INF)) > 0) flow += f;
        }
        return flow;
    }
};
