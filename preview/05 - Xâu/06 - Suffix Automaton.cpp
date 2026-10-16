// SUFFIX AUTOMATON — mọi xâu con của S, O(|S|)
// Dấu hiệu: "đếm xâu con phân biệt", "mỗi xâu con xuất hiện mấy lần".
//   VD: build("ababa"); distinct()=9.
// Bẫy: tối đa 2n state; clone occ=0; đếm occurrence gọi countOcc() trước;
//   'a'..'z' (khác thì dùng map).
struct SuffixAutomaton {
    struct State {
        int next[26], link, len;
        long long occ;
        State() { memset(next, -1, sizeof next); link = -1; len = 0; occ = 0; }
    };
    vector<State> st;
    int last;
    SuffixAutomaton(int maxn = 0) { st.reserve(2 * maxn + 5); st.emplace_back(); last = 0; }
    // thêm ký tự vào cuối xâu đang dựng.
    void extend(char ch) {
        int c = ch - 'a', cur = (int)st.size();
        st.emplace_back();
        st[cur].len = st[last].len + 1;
        st[cur].occ = 1;
        int p = last;
        while (p != -1 && st[p].next[c] == -1) { st[p].next[c] = cur; p = st[p].link; }
        if (p == -1) st[cur].link = 0;
        else {
            int q = st[p].next[c];
            if (st[p].len + 1 == st[q].len) st[cur].link = q;
            else {
                int clone = (int)st.size();
                st.push_back(st[q]);
                st[clone].len = st[p].len + 1;
                st[clone].occ = 0; // clone không phải endpos mới
                while (p != -1 && st[p].next[c] == q) { st[p].next[c] = clone; p = st[p].link; }
                st[q].link = st[cur].link = clone;
            }
        }
        last = cur;
    }
    // số xâu con phân biệt = sum len[v]-len[link[v]].
    long long distinct() {
        long long ans = 0;
        for (size_t i = 1; i < st.size(); i++) ans += st[i].len - st[st[i].link].len;
        return ans;
    }
    // cộng dồn occurrence (endpos size) từ dài về ngắn.
    void countOcc() {
        int maxL = 0;
        for (auto &s : st) maxL = max(maxL, s.len);
        vector<int> cnt(maxL + 1, 0);
        for (auto &s : st) cnt[s.len]++;
        for (int i = 1; i <= maxL; i++) cnt[i] += cnt[i - 1];
        vector<int> order(st.size());
        for (int i = (int)st.size() - 1; i >= 0; i--) order[--cnt[st[i].len]] = i;
        for (int i = (int)st.size() - 1; i > 0; i--) {
            int v = order[i];
            st[st[v].link].occ += st[v].occ;
        }
    }
};
