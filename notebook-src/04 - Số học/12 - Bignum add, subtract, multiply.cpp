// SỐ NGUYÊN LỚN — cộng/trừ/nhân số nguyên lớn không âm (dạng chuỗi)
// Cách gọi: Inp() nhập a, b; Solve() in tổng, hiệu, tích. O(n*m) khi nhân.
// Lưu ý: chỉ dùng khi đề bắt buộc (ICPC hiếm khi cần); số vừa thì dùng int64.
struct bigint{char si = '+'; string val;};

bigint a, b;

void Inp()
{
    string x, y;
    cin >> a.val; a.si = '+';
    cin >> b.val; b.si = '+';
}

void equalSize(bigint &a, bigint &b)
{
    bool SWAP = false;
    if (a.val.size() > b.val.size()) {swap(a, b); SWAP = true;}
    string tmp = "";
    for (int i = 0; i < b.val.size() - a.val.size(); i++)
        tmp = tmp + '0';
    a.val = tmp + a.val;
    if (SWAP) swap(a, b);
}

bigint Plus(bigint x, bigint y)
{
    if (x.val == "0") return y;
    if (y.val == "0") return x;

    if (x.val.size() != y.val.size()) equalSize(x, y);

    bigint res; res.val = "";
    int tmp, carry = 0;
    for (int i = x.val.size() - 1; i >= 0; i--)
    {
        tmp = x.val[i] + y.val[i] - 96 + carry;
        res.val = char(tmp % 10 + 48) + res.val;
        carry = tmp / 10;
    }
    if (carry) res.val = '1' + res.val;
    return res;
}

bigint dif(bigint x, bigint y)
{
    if (x.si == '+' && y.si == '-') return Plus(x, y);
    if (x.si == '-' && y.si == '+')
    {
        x.si = '+'; // (-|x|) + |y| = |y| - |x|
        return dif(y, x);
    }
    if (x.si == '-' && y.si == '-') // cả 2 âm: (-x) - (-y) = y - x
    {
        bigint a = x, b = y;
        a.si = b.si = '+';
        return dif(b, a);
    }

    if (x.val.size() != y.val.size()) equalSize(x, y); // đệm 0 để trừ từng chữ số
    bool check = false;
    if (x.val.size() < y.val.size() || (x.val.size() == y.val.size() && x.val < y.val))
        swap(x, y), check = true; // so sánh theo độ dài trước, rồi mới so sánh chuỗi
    bigint res; res.val = "";
    int tmp, carry = 0;
    for (int i = x.val.size() - 1; i >= 0; i--)
    {
        tmp = (x.val[i] - '0') - (y.val[i] - '0') - carry;
        if (tmp < 0)
        {
            tmp += 10;
            carry = 1;
        }
        else
            carry = 0;
        res.val = char(tmp + '0') + res.val;
    }
    if (check) res.si = '-';
    else       res.si = '+';
    return res;
}

bigint BigMultSmall(string x, int y)
{
    bigint res; res.val = "";
    int tmp, carry = 0;
    for (int i = x.size() - 1; i >= 0; i--)
    {
        tmp = int(x[i] - 48) * y + carry;
        res.val = char(tmp % 10 + 48) + res.val;
        carry = tmp / 10;
    }
    if (carry) res.val = char(carry + 48) + res.val;
    return res;
}

bigint mul(bigint x, bigint y)
{
    vector<bigint> rem; rem.reserve(x.val.size() + y.val.size());

    string zero = "";
    bigint tmp; tmp.val = "";
    int tmpY;
    for (int i = y.val.size() - 1; i >= 0; i--)
    {
        tmpY = int(y.val[i] - 48);
        if (tmpY == 0)
        {
            tmp.val = "0";
            tmp.si  = '+';
            zero = zero + '0';
            continue;
        }
        tmp = BigMultSmall(x.val, tmpY);
        tmp.val += zero;
        zero = zero + '0';
        rem.push_back(tmp);
    }
    bigint res; res.val = "0"; res.si = '+';
    for (int i = 0; i < rem.size(); i++)
        res = Plus(res, rem[i]);
    return res;
}

void Out(bigint x)
{
    while(x.val[0] == '0' && x.val.size() > 1) x.val.erase(0, 1);
    if (x.si == '-' && x.val[0] != '0') cout << '-';
    cout << x.val << '\n';
}

void Solve()
{
    equalSize(a, b);
    Out(Plus(a, b));
    Out(dif(a, b));
    Out(mul(a, b));
}
