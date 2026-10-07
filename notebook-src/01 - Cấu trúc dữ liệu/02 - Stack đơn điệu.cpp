// Tất cả đều O(n), a 1-indexed: a[1..n]. Đổi dấu so sánh để tìm nhỏ hơn
// nextGreater(a)[i]: j > i nhỏ nhất mà a[j] >= a[i] (n + 1 nếu không có)
// prevGreater(a)[i]: j < i lớn nhất mà a[j] > a[i] (0 nếu không có)
//   (một bên >=, một bên > để khi kết hợp không sót/trùng phần tử bằng nhau)
// largestRect(a):    HCN lớn nhất trong histogram có chiều cao a[i]
//                    (a[i] >= 0, mỗi cột rộng 1)
vector<int> nextGreater(vector<int> &a)
{
    int n = (int)a.size() - 1;
    vector<int> nxt(n + 1, n + 1), st;
    for (int i = 1; i <= n; i++) {
        while (!st.empty() && a[st.back()] < a[i]) {
            nxt[st.back()] = i;
            st.pop_back();
        }
        st.push_back(i);
    }
    return nxt;
}

vector<int> prevGreater(vector<int> &a)
{
    int n = (int)a.size() - 1;
    vector<int> prv(n + 1, 0), st;
    for (int i = 1; i <= n; i++) {
        while (!st.empty() && a[st.back()] <= a[i])
            st.pop_back();
        prv[i] = st.empty() ? 0 : st.back();
        st.push_back(i);
    }
    return prv;
}

ll largestRect(vector<int> &a)
{
    int n = (int)a.size() - 1;
    ll best = 0;
    vector<int> st;
    for (int i = 1; i <= n + 1; i++) {
        int cur = i <= n ? a[i] : 0;
        while (!st.empty() && a[st.back()] >= cur) {
            int j = st.back();
            st.pop_back();
            int l = st.empty() ? 0 : st.back();
            best = max(best, (ll)a[j] * (i - l - 1));
        }
        st.push_back(i);
    }
    return best;
}
