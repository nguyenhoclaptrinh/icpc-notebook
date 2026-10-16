// CENTROID — chặt cây tại trọng tâm, mỗi đỉnh thuộc O(log n) tầng
// Dấu hiệu: truy vấn trên mọi đường đi (tâm đường đi luôn là trọng tâm 1 tầng).
//   VD: đếm cặp đỉnh khoảng cách <= K (duyệt dist từ mỗi centroid, trừ tầng con).
// Bẫy: đánh dead[] khi tìm centroid; dữ liệu tính riêng mỗi tầng rồi gộp;
//   trừ double-count giữa các cây con; dfs đệ quy tràn stack với cây lệch.
struct Centroid {
    int n;
    vector<vector<int>> adj;
    vector<int> sub, dead, centPar;
    Centroid(int n = 0) { init(n); }
    void init(int n_) {
        n = n_;
        adj.assign(n + 1, {});
        sub.assign(n + 1, 0); dead.assign(n + 1, 0); centPar.assign(n + 1, 0);
    }
    void addEdge(int u, int v) { adj[u].push_back(v); adj[v].push_back(u); }
    int dfsSize(int u, int p) {
        sub[u] = 1;
        for (int v : adj[u]) if (v != p && !dead[v]) sub[u] += dfsSize(v, u);
        return sub[u];
    }
    // trọng tâm của thành phần size tot chứa u.
    int dfsCent(int u, int p, int tot) {
        for (int v : adj[u])
            if (v != p && !dead[v] && sub[v] > tot / 2) return dfsCent(v, u, tot);
        return u;
    }
    // phân rã từ entry; centPar[c] = trọng tâm cha (0 nếu gốc).
    // TODO tại mỗi centroid c: xử lý truy vấn đi qua c rồi đệ quy cây con.
    void build(int entry, int p) {
        int tot = dfsSize(entry, -1), c = dfsCent(entry, -1, tot);
        dead[c] = 1; centPar[c] = p;
        for (int v : adj[c]) if (!dead[v]) build(v, c);
    }
};
