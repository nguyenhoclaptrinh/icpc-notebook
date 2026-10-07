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
