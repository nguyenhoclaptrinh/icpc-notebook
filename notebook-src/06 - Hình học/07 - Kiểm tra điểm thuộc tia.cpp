// KIỂM TRA ĐIỂM THUỘC TIA — M có nằm trên tia xuất phát hướng A->B không?
// Cách gọi: pointInLaser(M, A, B) -> true nếu M nằm trên tia A->B. O(1)
// Lưu ý: cần thẳng hàng (cross == 0) VÀ cùng hướng (dot >= 0).
//   Trường hợp A == B: tia chỉ là điểm A -> trả về M == A.
bool pointInLaser(Pt M, Pt A, Pt B)
{
    if (A == B) // tia suy biến: chỉ còn điểm A
        return M == A;
    return sgn(cross(A, B, M)) == 0 && sgn(dot(B - A, M - A)) >= 0;
}
