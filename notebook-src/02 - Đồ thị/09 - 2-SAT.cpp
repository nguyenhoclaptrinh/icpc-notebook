// 2-SAT — gán boolean thỏa mọi mệnh đề OR 2 literal, O(n + m)
// Dấu hiệu: biến đúng/sai + ràng buộc đôi ("nếu-thì"); Katu Puzzle.
//   VD: (x0∨x1),(¬x0∨x1),(x0∨¬x1) -> YES 1 1.
// Bẫy: đỉnh 0-index [0,2n); phủ định v^1; chiều gán đã chốt bằng VD trên;
//   dfs đệ quy: đồ thị sâu quá tràn stack.
struct TwoSat {
    int n;
    vector<vector<int>> g, rg;
    vector<int> comp, order, used, val;
    TwoSat(int n = 0) { init(n); }
    // tạo mới n biến (literal: false 2*i, true 2*i+1).
    void init(int n_) {
        n = n_;
        g.assign(2 * n, {}); rg.assign(2 * n, {});
    }
    // cạnh kéo theo a -> b.
    void addImp(int a, int b) {
        g[a].push_back(b); rg[b].push_back(a);
    }
    // mệnh đề (a OR b).
    void addOr(int a, int b) {
        addImp(a ^ 1, b); addImp(b ^ 1, a);
    }
    void dfs1(int v) {
        used[v] = 1;
        for (int to : g[v]) if (!used[to]) dfs1(to);
        order.push_back(v);
    }
    void dfs2(int v, int c) {
        comp[v] = c;
        for (int to : rg[v]) if (comp[to] == -1) dfs2(to, c);
    }
    // true nếu thỏa được, đồng thời điền val[0..n-1].
    bool satisfiable() {
        used.assign(2 * n, 0); order.clear();
        for (int v = 0; v < 2 * n; v++) if (!used[v]) dfs1(v);
        comp.assign(2 * n, -1);
        int j = 0;
        for (int i = 2 * n - 1; i >= 0; i--) {
            int v = order[i];
            if (comp[v] == -1) dfs2(v, j++);
        }
        val.assign(n, 0);
        for (int i = 0; i < n; i++) {
            if (comp[2 * i] == comp[2 * i + 1]) return false;
            val[i] = comp[2 * i] < comp[2 * i + 1];
        }
        return true;
    }
};
