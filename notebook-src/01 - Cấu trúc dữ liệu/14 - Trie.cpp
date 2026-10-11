// Trie xâu thường ('a'..'z') — từ điển, tiền tố, autocomplete
// Dấu hiệu: "tiền tố", "đếm xâu bắt đầu bằng p", "từ điển".
//   VD: insert("ab") rồi find("a")==false, find_suffix("a")==true.
// Độ phức tạp: O(|s|) mỗi op. Tổng node <= tổng độ dài xâu.
// Lưu ý: s chỉ 'a'..'z' (khác -> OOB); cnt = số từ KẾT THÚC tại node;
//   find_suffix thực chất check TIỀN TỐ (tên hàm dễ nhầm).
const int TRIE_SZ = 26;
struct TrieNode
{
    TrieNode *child[TRIE_SZ];
    int cnt;

    TrieNode()
    {
        for (int i = 0; i < TRIE_SZ; i++) child[i] = NULL;
        cnt = 0;
    }

    // thêm s vào trie.
    void insert(const string &s)
    {
        int n = s.length();
        TrieNode* p = this;
        for (int i = 0; i < n; i++) {
            int nxt = s[i] - 'a';
            if (p->child[nxt] == NULL) p->child[nxt] = new TrieNode();
            p = p->child[nxt];
        }
        ++(p->cnt);
    }

    // true nếu s tồn tại nguyên từ.
    bool find(const string &s)
    {
        int n = s.length();
        TrieNode* p = this;
        for (int i = 0; i < n; i++) {
            int nxt = s[i] - 'a';
            if (p->child[nxt] == NULL) return false;
            p = p->child[nxt];
        }
        return (p->cnt) > 0;
    }

    // true nếu s là tiền tố của từ nào đó.
    bool find_suffix(const string &s)
    {
        int n = s.length();
        TrieNode* p = this;
        for (int i = 0; i < n; i++) {
            int nxt = s[i] - 'a';
            if (p->child[nxt] == NULL) return false;
            p = p->child[nxt];
        }
        return true;
    }
};
