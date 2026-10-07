line writeLine(point P, point Q)
{
    ll A = P.y.fi - Q.y.fi;
    ll B = Q.x.fi - P.x.fi;
    ll C = -(A*P.x.fi + B*P.y.fi);
    return {A, B, C};
}
