#include <bits/stdc++.h>
using namespace std;
using ll = long long;
// matrix type
using type = ll;
struct Matrix
{
    vector<vector<type>> data;
    int row() const {return data.size();}
    int col() const {return data[0].size();}
    auto & operator [](int i) {return data[i];}
    const auto & operator [](int i) const {return data[i];}
    Matrix() = default;
    Matrix(int r, int c) : data(r, vector<type> (c)) {}
    Matrix(const vector<vector<type>> &d) : data(d)  {}
    friend ostream & operator << (ostream &out, const Matrix &d)
    {
        for (auto x : d.data) {
            for (auto y : x) out << y << ' ';
            out << '\n';
        }
        return out;
    }
    static Matrix identity(long long n)
    {
        Matrix a = Matrix(n, n);
        while (n--) a[n][n] = 1;
        return a;
    }
    Matrix operator * (const Matrix &b)
    {
        Matrix a = *this;
        assert(a.col() == b.row());
        Matrix c(a.row(), b.col());
        for (int i = 0; i < a.row(); ++i)
            for (int j = 0; j < b.col(); ++j)
                for (int k = 0; k < a.col(); ++k)
                    c[i][j] += a[i][k] * b[k][j];
        return c;
    }
    Matrix pow(long long exp)
    {
        assert(row() == col());
        Matrix base = *this, ans = identity(row());
        for (; exp > 0; exp >>= 1, base = base * base)
            if (exp & 1) ans = ans * base;
        return ans;
    }
};
int main()
{
    Matrix a({
        {1, 2},
        {3, 4}
    });
    Matrix b({
        {0, 10, 100},
        {1,  1,  10}
    });
    cout << a * b << '\n';
    // 2 12 120
    // 4 34 340
    cout << a.pow(3) << '\n';
    // 37 54
    // 81 118
    b = a;
    cout << b << '\n';
    // 1 2
    // 3 4
    b = Matrix::identity(3);
    cout << b << '\n';
    // 1 0 0
    // 0 1 0
    // 0 0 1
    b = Matrix(2, 3);
    cout << b << '\n';
    // 0 0 0
    // 0 0 0
    Matrix c(3, 2);
    cout << c << '\n';
    // 0 0
    // 0 0
    // 0 0
}
