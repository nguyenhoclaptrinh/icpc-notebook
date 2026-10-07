// (a / b) mod MOD = a % MOD * Inv(b, MOD) % MOD (gcd(b, MOD) == 1)
// Nếu gcd(b, MOD) != 1 thì dùng ext_gcd(b, MOD, x, y)
int Inv(int n, int MOD)
{
    return (int)Pow(n, phi(MOD) - 1, MOD);
}
