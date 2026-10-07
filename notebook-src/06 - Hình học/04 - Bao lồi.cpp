// Bao lồi (Andrew), O(n log n)
// Trả về các đỉnh theo chiều ngược kim đồng hồ, bắt đầu từ điểm nhỏ nhất
// (x nhỏ nhất, rồi y nhỏ nhất); không chứa điểm nằm trên cạnh, bỏ điểm trùng
// Nếu các điểm thẳng hàng: trả về 2 đầu mút; 1 điểm: trả về điểm đó
vector<Pt> convexHull(vector<Pt> p)
{
    sort(p.begin(), p.end());
    p.erase(unique(p.begin(), p.end()), p.end());
    int n = p.size();
    if (n < 3)
        return p;

    vector<Pt> h(2 * n);
    int k = 0;
    for (int i = 0; i < n; i++) { // chuỗi dưới
        while (k >= 2 && sgn(cross(h[k - 2], h[k - 1], p[i])) <= 0)
            k--;
        h[k++] = p[i];
    }
    for (int i = n - 2, t = k + 1; i >= 0; i--) { // chuỗi trên
        while (k >= t && sgn(cross(h[k - 2], h[k - 1], p[i])) <= 0)
            k--;
        h[k++] = p[i];
    }
    h.resize(k - 1);
    return h;
}
