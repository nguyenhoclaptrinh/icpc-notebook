// HASH CẶP SỐ — mã hóa (x, y) thành 1 số 64-bit để dùng với unordered_set/map
// Cách gọi: hashPair(x, y); cần ull, ép về unsigned để đúng với số âm.
ull hashPair(int x, int y)
{
    return (ull)(unsigned)x << 32 | (unsigned)y;
}
