// NTT — nhân đa thức mod 998244353, O(n log n)
// Dấu hiệu: đề cho mod này + nhân 2 mảng lớn, C[k]=sum A[i]*B[k-i], O(n^2) TLE.
//   VD: a={1,2}, b={3,4} -> c={3,10,8}.
// Bẫy: CHỈ đúng mod 998244353; a[i],b[i] đã %MOD; n<=1<<23;
//   trunc nhân full rồi cắt.
const int NTT_MOD = 998244353, NTT_G = 3;
// a^e % NTT_MOD.
int ntt_modpow(int a, long long e) {
    long long r = 1, x = a;
    while (e) { if (e & 1) r = r * x % NTT_MOD; x = x * x % NTT_MOD; e >>= 1; }
    return (int)r;
}
// tại chỗ, size là lũy thừa của 2; false: hệ số->giá trị, true: ngược lại.
void ntt(vector<int> & a, bool invert) {
    int n = (int)a.size();
    for (int i = 1, j = 0; i < n; i++) {
        int bit = n >> 1;
        for (; j & bit; bit >>= 1) j ^= bit;
        j ^= bit;
        if (i < j) swap(a[i], a[j]);
    }
    for (int len = 2; len <= n; len <<= 1) {
        int wlen = ntt_modpow(NTT_G, (NTT_MOD - 1) / len);
        if (invert) wlen = ntt_modpow(wlen, NTT_MOD - 2);
        for (int i = 0; i < n; i += len) {
            int w = 1;
            for (int j = 0; j < len / 2; j++) {
                int u = a[i + j];
                int v = (int)((long long)a[i + j + len / 2] * w % NTT_MOD);
                int x = u + v;
                if (x >= NTT_MOD) x -= NTT_MOD;
                a[i + j] = x;
                int y = u - v;
                if (y < 0) y += NTT_MOD;
                a[i + j + len / 2] = y;
                w = (int)((long long)w * wlen % NTT_MOD);
            }
        }
    }
    if (invert) {
        int n_inv = ntt_modpow(n, NTT_MOD - 2);
        for (int & x : a) x = (int)((long long)x * n_inv % NTT_MOD);
    }
}
// c[k]=sum a[i]*b[k-i]; size ra = a.size()+b.size()-1.
vector<int> ntt_multiply(const vector<int> & a, const vector<int> & b) {
    if (a.empty() || b.empty()) return {};
    int n1 = (int)a.size(), n2 = (int)b.size();
    int n = 1;
    while (n < n1 + n2 - 1) n <<= 1;
    vector<int> fa(a.begin(), a.end()), fb(b.begin(), b.end());
    fa.resize(n); fb.resize(n);
    ntt(fa, false); ntt(fb, false);
    for (int i = 0; i < n; i++) fa[i] = (int)((long long)fa[i] * fb[i] % NTT_MOD);
    ntt(fa, true);
    fa.resize(n1 + n2 - 1);
    return fa;
}
// như trên, chỉ giữ lim hệ số đầu.
vector<int> ntt_multiply_trunc(const vector<int> & a, const vector<int> & b, int lim) {
    vector<int> c = ntt_multiply(a, b);
    if (lim > 0 && (int)c.size() > lim) c.resize(lim);
    return c;
}
