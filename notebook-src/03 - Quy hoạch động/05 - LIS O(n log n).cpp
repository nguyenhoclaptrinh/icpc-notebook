// LIS — dãy con TĂNG (không nhất thiết liên tục) dài nhất, O(n log n)
// Dấu hiệu nhận biết: "dãy con", "tăng dần", "dài nhất", "xóa ít nhất để được tăng".
// Cách gọi:
//   lisLen(a): độ dài LIS TĂNG CHẶT (a[i] < a[j]).
//     Muốn KHÔNG GIẢM (a[i] <= a[j]): đổi lower_bound -> upper_bound.
//   lisRestore(a): trả về 1 dãy LIS cụ thể (vector giá trị).
// Độ phức tạp: O(n log n) cả hai hàm.
int lisLen(const vector<int> &a) {
    vector<int> d; // d[k] = giá trị kết thúc NHỎ NHẤT của dãy dài k+1
    for (int x : a) {
        auto it = lower_bound(d.begin(), d.end(), x); // tăng chặt
        if (it == d.end()) d.push_back(x);
        else *it = x;
    }
    return (int)d.size();
}

// Khôi phục 1 dãy LIS (tăng chặt). Muốn không giảm: đổi < thành <= ở dưới.
vector<int> lisRestore(const vector<int> &a) {
    int n = (int)a.size();
    vector<int> d; // d[len] = chỉ số phần tử kết thúc tốt nhất
    vector<int> par(n, -1);
    for (int i = 0; i < n; i++) {
        int lo = 0, hi = (int)d.size();
        while (lo < hi) { // lower_bound trên a[d[mid]]
            int mid = (lo + hi) / 2;
            if (a[d[mid]] < a[i]) lo = mid + 1;
            else hi = mid;
        }
        if (lo > 0) par[i] = d[lo - 1];
        if (lo == (int)d.size()) d.push_back(i);
        else d[lo] = i;
    }
    vector<int> res;
    for (int i = d.empty() ? -1 : d.back(); i != -1; i = par[i])
        res.push_back(a[i]);
    reverse(res.begin(), res.end());
    return res;
}
