// MST — Kruskal: cây khung nhỏ nhất trên đồ thị VÔ HƯỚNG, có trọng số
// Dấu hiệu nhận biết: "cây khung nhỏ nhất", "kết nối tất cả đỉnh với chi phí nhỏ nhất".
// Cách gọi: nhập n, m; addEdge(u, v, w) 1-index; Solve() -> in chỉ số cạnh của MST.
// Độ phức tạp: O(M log M) (sort) + O(M α(N)) (DSU).
// Lưu ý: đồ thị phải LIÊN THÔNG. Nếu không, kết quả sẽ thiếu cạnh.
// Cấu trúc edge: {weight, index, u, v} (first.first = weight, first.second = index,
//                                 second.first = u, second.second = v)
using namespace std;
const int N = 5e5 + 5;

int n, m;
DSU dsu;

// {weight, index, u, v}
pair<pair<int, int>, pair<int, int>> edge[N];

void Inp()
{
    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        // nhập u, v, w
        cin >> edge[i].second.first >>
               edge[i].second.second >>
               edge[i].first.first;
        edge[i].first.second = i;  // lưu chỉ số cạnh
    }
}

void Solve()
{
    dsu.build(n);
    sort(edge + 1, edge + m + 1);  // sắp xếp theo weight, sau đó theo index
    vector<int> res;
    for (int i = 1; i <= m; i++) {
        if (!dsu.unite(edge[i].second.first, edge[i].second.second))
            continue;  // u, v đã cùng thành phần liên thông

        res.push_back(edge[i].first.second);
        if (res.size() == n - 1) break;  // đã đủ n-1 cạnh
    }
    // Kiểm tra đồ thị liên thông
    if (res.size() != n - 1) {
        cout << "Đồ thị không liên thông!\n";
        return;
    }
    for (int &x : res) cout << x << ' ';
}
