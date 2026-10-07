// Extended Euclid: tìm X, Y sao cho A*X + B*Y = gcd(A, B)
// Nghịch đảo mod: nếu gcd(b, MOD) == 1 thì X là B^-1 mod MOD
//      ll x, y; ext_gcd(b, MOD, x, y);
//      ll inv = ((x % MOD) + MOD) % MOD;
//      (a / b) % MOD = (a % MOD) * inv % MOD
// Giải Diophantine a*x + b*y = c (có nghiệm khi gcd(a, b) chia hết c)
void ext_gcd(ll A, ll B, ll &X, ll &Y)
{
    long long x2, y2,
              x1, y1,
              x,  y,
              r2, r1,
              q,  r;

    x2 = 1; y2 = 0;
    x1 = 0; y1 = 1;
    for (r2 = A, r1 = B; r1 != 0; r2 = r1, r1 = r, x2 = x1, y2 = y1, x1 =
      x, y1 = y) {
        q = r2 / r1;
        r = r2 % r1;
        x = x2 - (q * x1);
        y = y2 - (q * y1);
    }
    X = x2; Y = y2;
}
