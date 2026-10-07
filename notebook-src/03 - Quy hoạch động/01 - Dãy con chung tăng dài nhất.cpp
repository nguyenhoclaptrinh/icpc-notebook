// LCIS — dãy con chung TĂNG dài nhất của a[1..n] và b[1..m], O(n*m)
// Cách gọi: f[1..m] = {0}; Solve() -> in độ dài LCIS tăng chặt.
// Lưu ý: cần mảng a, b, f và n, m khai báo sẵn; muốn KHÔNG GIẢM: đổi > thành >=.
void Solve()
{
    for (int i = 1; i <= n; i++) {
        int Max = 0;
        for (int j = 1; j <= m; j++) {
            if (a[i] == b[j]) f[j] = max(f[j], Max + 1);
            if (a[i] > b[j])   Max = max(f[j], Max);
        }
    }
    cout << *max_element(f + 1, f + m + 1);
}
