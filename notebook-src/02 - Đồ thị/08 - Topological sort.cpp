// TOPOLOGICAL SORT (Kahn) — sắp xếp đỉnh trên đồ thị CÓ HƯỚNG không chu trình
// Dấu hiệu nhận biết: "thứ tự thực hiện", "điều kiện trước-sau", "phát hiện chu trình".
// Cách gọi: Topo ts(n); ts.addEdge(u, v) nghĩa là u TRƯỚC v;
//   ts.sort() -> thứ tự topo; trả về vector RỖNG nếu có chu trình.
// 0-index. Độ phức tạp: O(n + m).
// Lưu ý: muốn thứ tự từ điển nhỏ nhất -> thay queue bằng priority_queue
//   (greater<int>); muốn đếm số thứ tự topo -> dùng DP/bitmask, không dùng hàm này.
struct Topo {
    int n;
    vector<vector<int>> adj;

    Topo(int n = 0) { init(n); }
    void init(int n_) { n = n_; adj.assign(n, {}); }
    void addEdge(int u, int v) { adj[u].push_back(v); } // u trước v

    vector<int> sort() {
        vector<int> indeg(n, 0);
        for (int u = 0; u < n; u++)
            for (int v : adj[u]) indeg[v]++;
        queue<int> q;
        for (int i = 0; i < n; i++)
            if (indeg[i] == 0) q.push(i);
        vector<int> ord;
        while (!q.empty()) {
            int u = q.front(); q.pop();
            ord.push_back(u);
            for (int v : adj[u])
                if (--indeg[v] == 0) q.push(v);
        }
        if ((int)ord.size() != n) return {}; // có chu trình
        return ord;
    }
};
