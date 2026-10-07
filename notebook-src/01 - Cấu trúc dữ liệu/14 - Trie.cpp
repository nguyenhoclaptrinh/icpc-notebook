// t.insert(s):      thêm s vào trie
// t.find(s):        kiểm tra s có tồn tại trong trie không
// t.find_suffix(s): kiểm tra s có là hậu tố của một xâu trong trie
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
