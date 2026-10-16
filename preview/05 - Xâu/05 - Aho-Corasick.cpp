// AHO-CORASICK — tìm mọi pattern trong text 1 lần duyệt
// Dấu hiệu: nhiều pattern, "mỗi pattern xuất hiện mấy lần / ở đâu".
//   VD: add("he"); add("she"); build(); match("she") -> {(2,0),(2,1)}.
// Bẫy: 'a'..'z' (khác thì đổi alphabet); build() 1 lần sau khi add xong;
//   tổng output = số khớp (có thể lớn).
struct AhoCorasick {
    static const int ALPH = 26;
    struct Node {
        int next[ALPH], link;
        vector<int> out;
        Node() { memset(next, -1, sizeof next); link = 0; }
    };
    vector<Node> t;
    int npats = 0;
    AhoCorasick() { t.emplace_back(); }
    // thêm pattern, trả id pattern (0,1,2...).
    int add(const string &s) {
        int v = 0;
        for (char ch : s) {
            int c = ch - 'a';
            if (t[v].next[c] == -1) { t[v].next[c] = (int)t.size(); t.emplace_back(); }
            v = t[v].next[c];
        }
        t[v].out.push_back(npats);
        return npats++;
    }
    // dựng failure + điền go đầy đủ.
    void build() {
        queue<int> q;
        for (int c = 0; c < ALPH; c++) {
            int v = t[0].next[c];
            if (v != -1) { t[v].link = 0; q.push(v); }
            else t[0].next[c] = 0;
        }
        while (!q.empty()) {
            int v = q.front(); q.pop();
            for (int id : t[t[v].link].out) t[v].out.push_back(id);
            for (int c = 0; c < ALPH; c++) {
                int u = t[v].next[c];
                if (u != -1) { t[u].link = t[t[v].link].next[c]; q.push(u); }
                else t[v].next[c] = t[t[v].link].next[c];
            }
        }
    }
    // duyệt text, trả list (vị trí kết thúc 0-index, id pattern).
    vector<pair<int, int>> match(const string &s) {
        vector<pair<int, int>> res;
        int v = 0;
        for (int i = 0; i < (int)s.size(); i++) {
            v = t[v].next[s[i] - 'a'];
            for (int id : t[v].out) res.push_back({i, id});
        }
        return res;
    }
};
