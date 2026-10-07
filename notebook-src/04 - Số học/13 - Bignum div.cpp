// CHIA SỐ LỚN — thương của số nguyên lớn (dạng chuỗi) chia cho số int
// Cách gọi: longDivision(number, divisor) -> chuỗi thương (làm tròn xuống).
// Độ phức tạp: O(n). Lưu ý: divisor > 0; số âm tự xử lý dấu trước khi gọi.
string longDivision(string number, int divisor)
{
    string ans;

    // Guard: divisor > number -> kết quả 0
    if (divisor == 0) return "0"; // tránh chia 0
    if ((int)number.size() == 1 && number[0] - '0' < divisor) return "0";

    // Find prefix of number that is larger than divisor.
    int idx = 0;
    ll temp = number[idx] - '0';
    while (temp < divisor && idx + 1 < (int)number.size())
        temp = temp * 10 + (number[++idx] - '0');

    // Repeatedly divide divisor with temp.
    // After every division, update temp to include one more digit.
    while (number.size() > idx) {
        // Store result in answer i.e. temp / divisor
        ans += (temp / divisor) + '0';

        // Take next digit of number
        temp = (temp % divisor) * 10 + (number[++idx] - '0');
    }

    // If divisor is greater than number
    if (ans.length() == 0)
        return "0";

    // else return ans
    return ans;
}
