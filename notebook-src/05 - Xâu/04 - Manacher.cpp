// MANACHER — mọi palindrome con, O(N), s 0-indexed
// Dấu hiệu: "đếm palindrome", "palindrome dài nhất", "[l,r] đối xứng?".
//   VD: "ababa" -> d1={1,2,3,2,1}, dài nhất 5, tổng 9; d2 tâm chẵn.
//   check [l,r]: lẻ d1[(l+r)/2]>(r-l)/2; chẵn d2[(l+r+1)/2]>=(r-l+1)/2.
// Độ phức tạp: O(N). Tổng sum(d1)+sum(d2) dùng long long.
// Điền d1 (tâm lẻ, dài nhất 2*d1[i]-1), d2 (tâm giữa i-1,i, dài 2*d2[i]).
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
