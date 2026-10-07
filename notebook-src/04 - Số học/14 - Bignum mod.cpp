int smallMod(string a, int b)
{
    ll res = 0;
    for (int i = 0; i < a.size(); i++)
        (res = 10LL*res + ll(a[i] - '0')) %= b;
    return res;
}
