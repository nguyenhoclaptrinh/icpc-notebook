using namespace std;
// PHÂN CÔNG — chọn k ô sao cho mỗi hàng, mỗi cột tối đa 1 ô, tổng lớn nhất
// Dấu hiệu: "mỗi hàng/cột chọn 1", "tổng lớn nhất". O(m * n * 2^n), cần n <= 20.
// Cách gọi: nhập n, m, k và ma trận a[n][m]; Solve() -> in k và tổng lớn nhất.
const int oo = 2e9;
const int N = 2e1 + 5;

int n, m, k;
int a[N][N];

void Inp()
{
    cin >> n >> m >> k;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> a[i][j];
        }
    }
}

void Solve()
{
    if (k == 0) return void(cout << "0\n0");

    int dp[(1 << n)][m];

    fill(dp[0], dp[0] + m, 0);
    for (int i = 1; i < (1 << n); i++)
        dp[i][0] = -oo;
    for (int x = 0; x < n; x++)
        dp[(1 << x)][0] = a[x][0];
      for (int d = 1; d < m; d++) {
        for (int s = 0; s < (1 << n); s++) {
            dp[s][d] = dp[s][d-1];
            for (int x = 0; x < n; x++) {
                if (s & (1 << x)) {
                dp[s][d] = max(dp[s][d], dp[s ^ (1 << x)][d - 1] +
                  a[x][d]);
                }
            }
        }
    }

    int res = -oo; // khởi tạo -vô cực để đúng cả khi mọi số âm
    for (int s = 0; s < (1 << n); s++)
        if (__builtin_popcount(s) == k)
            res = max(res, dp[s][m - 1]);

    cout << k << '\n' << res;
}
