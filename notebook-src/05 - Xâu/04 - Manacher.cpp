// Manacher: tìm mọi xâu con đối xứng (palindrome), O(n). s 0-indexed
// d1[i]: số palindrome độ dài lẻ có tâm i (= bán kính lớn nhất,
//        palindrome dài nhất có độ dài 2 * d1[i] - 1)
// d2[i]: số palindrome độ dài chẵn có tâm giữa i - 1 và i
//        (palindrome dài nhất có độ dài 2 * d2[i])
// Tổng số xâu con đối xứng = sum(d1) + sum(d2)
// Cách đọc: palindrome lẻ dài nhất tâm i dài 2*d1[i]-1;
//   palindrome chẵn dài nhất tâm i (giữa i-1 và i) dài 2*d2[i].
//   Kiểm tra đoạn [l, r] đối xứng: lẻ thì tâm m=(l+r)/2 cần d1[m] > (r-l)/2;
//   chẵn thì tâm m=(l+r+1)/2 cần d2[m] >= (r-l+1)/2.
void manacher(string &s, vector<int> &d1, vector<int> &d2)
{
    int n = s.size();
    d1.assign(n, 0);
    d2.assign(n, 0);

    for (int i = 0, l = 0, r = -1; i < n; i++) {
        int k = i > r ? 1 : min(d1[l + r - i], r - i + 1);
        while (i - k >= 0 && i + k < n && s[i - k] == s[i + k])
            k++;
        d1[i] = k--;
        if (i + k > r) {
            l = i - k;
            r = i + k;
        }
    }

    for (int i = 0, l = 0, r = -1; i < n; i++) {
        int k = i > r ? 0 : min(d2[l + r - i + 1], r - i + 1);
        while (i - k - 1 >= 0 && i + k < n && s[i - k - 1] == s[i + k])
            k++;
        d2[i] = k--;
        if (i + k > r) {
            l = i - k - 1;
            r = i + k;
        }
    }
}
