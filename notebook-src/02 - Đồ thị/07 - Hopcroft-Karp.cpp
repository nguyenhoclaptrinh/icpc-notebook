// Hopcroft-Karp — ghép cặp cực đại đồ thị LƯỠNG PHÂN, O(E sqrt V)
// Dấu hiệu: 2 nhóm, mỗi đỉnh ≤ 1 cặp; "gán việc"; path cover DAG = n - matching.
//   VD: nL=3, nR=3, cạnh (0-0,0-1,1-1,2-1) -> ans=2.
// Bẫy: PHẢI lưỡng phân; sai nL/nR -> crash; mỗi test tạo hk mới;
//   input 1-based nhớ -1 (code 0-index).
struct HopcroftKarp {
    int nL, nR;
    vector<vector<int>> adj;
    vector<int> dist, pairU, pairV;

    HopcroftKarp(int nL = 0, int nR = 0) { init(nL, nR); }
    // tạo mới (gọi mỗi test cho sạch).
    void init(int nL_, int nR_) {
        nL = nL_; nR = nR_; adj.assign(nL, {});
    }
    // thêm cạnh trái u tới phải v, 0-index.
    void addEdge(int u, int v) { adj[u].push_back(v); }

    bool bfs() {
        queue<int> q;
        for (int u = 0; u < nL; u++) {
            if (pairU[u] == -1) { dist[u] = 0; q.push(u); }
            else dist[u] = -1;
        }
        bool found = false;
        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (int v : adj[u]) {
                int pu = pairV[v];
                if (pu != -1 && dist[pu] == -1) {
                    dist[pu] = dist[u] + 1; q.push(pu);
                }
                if (pu == -1) found = true;
            }
        }
        return found;
    }

    bool dfs(int u) {
        for (int v : adj[u]) {
            int pu = pairV[v];
            if (pu == -1 || (dist[pu] == dist[u] + 1 && dfs(pu))) {
                pairU[u] = v; pairV[v] = u; return true;
            }
        }
        dist[u] = -1;
        return false;
    }

    // số cặp cực đại; đồng thời điền pairU/pairV (-1 nếu lẻ).
    int maxMatching() {
        pairU.assign(nL, -1); pairV.assign(nR, -1); dist.resize(nL);
        int matching = 0;
        while (bfs())
            for (int u = 0; u < nL; u++)
                if (pairU[u] == -1 && dfs(u)) matching++;
        return matching;
    }
};
