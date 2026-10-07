// HOPCROFT-KARP — ghép cặp cực đại trên đồ thị LƯỠNG PHÂN, O(E sqrt V)
// Dấu hiệu nhận biết: ghép đôi 2 nhóm (trái-phải), mỗi đỉnh tối đa 1 cặp;
//   "phủ tối thiểu", "đường đi phủ nhau trên DAG" (chuyển về matching).
// Cách gọi: HopcroftKarp hk(nLeft, nRight);
//   hk.addEdge(u, v) với u nhóm trái, v nhóm phải (0-index);
//   hk.maxMatching() -> số cặp; hk.pairU[u] = v được ghép (-1 nếu lẻ).
// Độ phức tạp: O(E sqrt V). Nhanh hơn Kuhn (DFS đơn) rất nhiều.
// Lưu ý: đồ thị PHẢI lưỡng phân. Vertex cover cực tiểu (Kőnig):
//   |cover| = |matching|; min path cover trên DAG = n - |matching|.
struct HopcroftKarp {
    int nL, nR;
    vector<vector<int>> adj;
    vector<int> dist, pairU, pairV;

    HopcroftKarp(int nL = 0, int nR = 0) { init(nL, nR); }
    void init(int nL_, int nR_) {
        nL = nL_; nR = nR_; adj.assign(nL, {});
    }
    void addEdge(int u, int v) { adj[u].push_back(v); } // u trái, v phải

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

    int maxMatching() {
        pairU.assign(nL, -1); pairV.assign(nR, -1); dist.resize(nL);
        int matching = 0;
        while (bfs())
            for (int u = 0; u < nL; u++)
                if (pairU[u] == -1 && dfs(u)) matching++;
        return matching;
    }
};
