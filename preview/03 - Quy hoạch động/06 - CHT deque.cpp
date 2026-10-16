// CHT DEQUE — max(m*x+b), slope thêm đơn điệu, hỏi x đơn điệu, O(1) amortized
// Dấu hiệu: DP max đường thẳng mà slope và x đều đơn điệu (ngược thì Li Chao).
//   VD: add(2,3); query(10)=23.
// Bẫy: max hay min (đảo dấu); slope bằng nhau giữ intercept tốt;
//   x hỏi KHÔNG đơn điệu thì sai.
struct CHT {
    struct Line {
        long long m, b;
        // giá trị tại x (input vừa trong ll).
        long long eval(long long x) const { return m * x + b; }
    };
    deque<Line> dq;
    // true nếu l2 không bao giờ tốt nhất (kiểm tra giao nhau).
    static bool bad(const Line &l1, const Line &l2, const Line &l3) {
        return (__int128)(l3.b - l1.b) * (l1.m - l2.m)
             <= (__int128)(l2.b - l1.b) * (l1.m - l3.m);
    }
    // thêm đường slope không giảm (bản max).
    void add(long long m, long long b) {
        Line nw{m, b};
        if (!dq.empty() && dq.back().m == m) {
            if (b <= dq.back().b) return;
            dq.pop_back();
        }
        while (dq.size() >= 2 && bad(dq[dq.size() - 2], dq[dq.size() - 1], nw))
            dq.pop_back();
        dq.push_back(nw);
    }
    // x hỏi không giảm.
    long long query(long long x) {
        while (dq.size() >= 2 && dq[0].eval(x) <= dq[1].eval(x)) dq.pop_front();
        return dq[0].eval(x);
    }
};
