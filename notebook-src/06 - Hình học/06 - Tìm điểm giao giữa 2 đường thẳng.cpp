point intersect(line l1, line l2)
{
    ll a1 = l1.a, b1 = l1.b, c1 = l1.c,
       a2 = l2.a, b2 = l2.b, c2 = l2.c;
    ll D  = a1*b2 - a2*b1,
       Dx = c2*b1 - c1*b2,
       Dy = a2*c1 - a1*c2;

    if (D == Dx && Dx == Dy && Dy == 0)
        return {{(ll)  N + 1, 1LL}, {(ll)  N + 1, 1LL}};

    if (D == 0 && (Dx || Dy))
        return {{(ll) -N - 1, 1LL}, {(ll) -N - 1, 1LL}};

    point M = {{Dx, D}, {Dy, D}};

    return M;
}
