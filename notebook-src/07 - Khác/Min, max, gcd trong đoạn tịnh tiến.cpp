// MIN/MAX ĐOẠN TRƯỢT — min/max mọi cửa sổ dài len trong O(n), không cần deque
// Cách gọi: có sẵn a[1..n] và mảng lmn/lmx/rmn/rmx; với mỗi i >= len:
//   Min = min(rmn[i-len+1], lmn[i]); Max = max(rmx[i-len+1], lmx[i]).
// Độ phức tạp: O(n). Kỹ thuật khối: tiền/hậu tố trong từng khối dài len.
for (int i = 1; i <= n; i++) {
    lmn[i] = (i % len == 1) ? a[i] : min(lmn[i-1], a[i]);
    lmx[i] = (i % len == 1) ? a[i] : max(lmx[i-1], a[i]);
}

for (int i = n; i >= 1; i--) {
    rmn[i] = (i % len==0 || i==n) ? a[i] : min(rmn[i+1], a[i]);
    rmx[i] = (i % len==0 || i==n) ? a[i] : max(rmx[i+1], a[i]);
}

for (int i = len; i <= n; i++) {
    int Min = min(rmn[i - len + 1], lmn[i]);
        Max = max(rmx[i - len + 1], lmx[i]);
}
