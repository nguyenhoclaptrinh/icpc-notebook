#define INF 0x3f3f3f3f

typedef pair<int, int> ii;
typedef priority_queue<ii, vector<ii>, greater<ii>> min_heap;

const int N = 1e5 + 1;

int numNode, numEdge, S, T;
vector<ii> adj[N];
int dist[N];

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

// min path to go from s to t
int dijkstra(int s, int t)
{
    for (int i = 1; i <= numNode; i++) dist[i] = INF;

    min_heap pq;
    pq.push({0, s});
    dist[s] = 0;

    while(!pq.empty()) {
        int u  = pq.top().second,
            wu = pq.top().first;
        pq.pop();

        if (wu > dist[u]) continue;

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
