// DIJKSTRA — đường đi ngắn nhất trên đồ thị VÔ HƯỚNG, trọng số KHÔNG ÂM
// Dấu hiệu nhận biết: "đường đi ngắn nhất", "chi phí nhỏ nhất", "có trọng số không âm".
// Cách gọi: nhập numNode, numEdge, S, T; addEdge(u, v, w) 1-index;
//          dijkstra(S, T) -> khoảng cách ngắn nhất (INF nếu không tới được).
// Độ phức tạp: O((N + M) log N).
// Lưu ý: trọng số phải KHÔNG ÂM. Nếu trọng số lớn, tăng INF hoặc dùng long long.
#define INF 0x3f3f3f3f3f3f3f3fLL  // ~1.15e18, đủ lớn cho long long

typedef pair<long long, int> ii;  // (khoảng cách, đỉnh)
typedef priority_queue<ii, vector<ii>, greater<ii>> min_heap;

const int N = 1e5 + 5;

int numNode, numEdge, S, T;
vector<pair<int, int>> adj[N];  // (đỉnh kề, trọng số)
long long dist[N];

// Thêm cạnh vô hướng (nếu đồ thị có hướng, chỉ giữ 1 dòng)
void addEdge(int u, int v, int w)
{
    adj[u].push_back({v, w});
    adj[v].push_back({u, w});
}

void inp()
{
    cin >> numNode >> numEdge >> S >> T;
    int u, v, w;
    while(numEdge-- > 0) {
        cin >> u >> v >> w;
        addEdge(u, v, w);
    }
}

// Trả về khoảng cách ngắn nhất từ s đến t (INF nếu không tới được)
long long dijkstra(int s, int t)
{
    for (int i = 1; i <= numNode; i++) dist[i] = INF;

    min_heap pq;
    pq.push({0, s});
    dist[s] = 0;

    while(!pq.empty()) {
        int u = pq.top().second;
        long long wu = pq.top().first;
        pq.pop();

        if (wu > dist[u]) continue;  // bỏ qua nếu đã có đường ngắn hơn

        for (auto x : adj[u]) {
            int v = x.first;
            int weight = x.second;

            if (dist[v] > dist[u] + weight) {
                dist[v] = dist[u] + weight;
                pq.push({dist[v], v});
            }
        }
    }
    return dist[t];
}
