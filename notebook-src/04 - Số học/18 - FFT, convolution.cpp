// FFT — nhân đa thức/số nguyên không mod, O(n log n)
// Dấu hiệu: tích chập C[k]=sum A[i]*B[k-i], đáp án KHÔNG mod prime;
//   mỗi hệ số kết quả < 9e15 (vừa mantissa double).
//   VD: a={1,2}, b={3,4} -> {3,10,8}.
// Bẫy: làm tròn llround sau biến ngược; số lớn hơn thì tách hệ số;
//   cần mod 998244353 thì dùng NTT cho chính xác.
using cd = complex<double>;
const double FFT_PI = acos(-1);

// tại chỗ, size là lũy thừa của 2; false: hệ số->giá trị, true: ngược lại + chia n.
void fft(vector<cd> & a, bool invert) {
    int n = (int)a.size();
    for (int i = 1, j = 0; i < n; i++) {
        int bit = n >> 1;
        for (; j & bit; bit >>= 1) j ^= bit;
        j ^= bit;
        if (i < j) swap(a[i], a[j]);
    }
    for (int len = 2; len <= n; len <<= 1) {
        double ang = 2 * FFT_PI / len * (invert ? -1 : 1);
        cd wlen(cos(ang), sin(ang));
        for (int i = 0; i < n; i += len) {
            cd w(1);
            for (int j = 0; j < len / 2; j++) {
                cd u = a[i + j], v = a[i + j + len / 2] * w;
                a[i + j] = u + v;
                a[i + j + len / 2] = u - v;
                w *= wlen;
            }
        }
    }
    if (invert)
        for (cd & x : a) x /= n;
}

// tích chập làm tròn số nguyên; input vừa trong int, output vừa trong ll.
vector<long long> fft_multiply(const vector<int> & a, const vector<int> & b) {
    if (a.empty() || b.empty()) return {};
    int n1 = (int)a.size(), n2 = (int)b.size(), n = 1;
    while (n < n1 + n2 - 1) n <<= 1;
    vector<cd> fa(n), fb(n);
    for (int i = 0; i < n1; i++) fa[i] = a[i];
    for (int i = 0; i < n2; i++) fb[i] = b[i];
    fft(fa, false); fft(fb, false);
    for (int i = 0; i < n; i++) fa[i] *= fb[i];
    fft(fa, true);
    vector<long long> c(n1 + n2 - 1);
    for (int i = 0; i < n1 + n2 - 1; i++) c[i] = llround(fa[i].real());
    return c;
}
