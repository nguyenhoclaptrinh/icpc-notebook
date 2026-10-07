// KHỚP CẦU — tìm khớp (articulation point) và cầu (bridge) trên đồ thị VÔ HƯỚNG
// Dấu hiệu nhận biết: "xóa đỉnh/cạnh làm đồ thị thành nhiều thành phần",
//   "điểm trụ", "cạnh cầu", "đồ thị 2 liên thông".
// Cách gọi: nhập n, m; addEdge(u, v) 1-index; solve() -> cout số khớp, số cầu.
// Độ phức tạp: O(n + m). Dùng được với ĐA ĐỒ THỊ (cạnh song song).
// Lưu ý: đồ thị vô hướng, có thể có cạnh song song và tự khuyên.
const int N = 100005;

int n, m;
vector<pair<int,int>> adj[N]; // (đỉnh kề, id cạnh)
bool joint[N], seen[N];
int low[N], num[N], timeDfs, cnt_joint, cnt_bridge;

int edgeCnt = 0;
void addEdge(int u, int v)
{
    int id = edgeCnt++; // id canh duy nhat
    adj[u].push_back({v, id});
    adj[v].push_back({u, id});
}

void inp()
{
    cin >> n >> m; int u, v;
    while(m-- > 0)
        cin >> u >> v,
        addEdge(u, v);
}

void dfs(int u, int preEdge)
{
    low[u] = num[u] = ++timeDfs; seen[u] = 1;
    int child = 0;

    for (auto [v, eid] : adj[u])
    {
        if (eid == preEdge) continue; // bỏ qua chính cạnh vừa đi (xử lý đúng đa đồ thị)
        if (!seen[v])   // gặp cung xuôi
        {
            dfs(v, eid);
            low[u] = min(low[u], low[v]);

            // Cạnh (u, v) là cầu nếu low[v] > num[u]
            // (v không có đường nào đi lên trên u ngoài cạnh (u, v))
            if (low[v] > num[u]) ++cnt_bridge;

            ++child; // tăng số lượng con của u

            // nếu u là gốc cây dfs
            if (preEdge == -1) {
                // và nếu u có nhiều hơn 1 con
                if (child > 1)
                    joint[u] = 1; // -> u là khớp
            }

            // ngược lại nếu u không phải là gốc cây
            // nhưng low[v] >= num[u]
            else if (low[v] >= num[u])
                joint[u] = 1; // -> u vẫn sẽ là khớp
        }
        else // gặp cung ngược
            low[u] = min(low[u], num[v]);
    }
}

void solve()
{
    for (int i = 1; i <= n; i++)
        if (!num[i])
            dfs(i, -1);

    for (int i = 1; i <= n; i++)
        cnt_joint += joint[i];
    cout << cnt_joint << ' ' << cnt_bridge;
}
