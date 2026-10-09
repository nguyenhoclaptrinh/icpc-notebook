# Changelog

## [v1.0] - 2026-10-09
So với baseline `f2bedd5`.

### Added
- Template tổng + 6 thuật toán mới: Sparse Table, LIS (+ khôi phục dãy),
  Linear basis XOR, Topological sort, CRT, Hopcroft-Karp.
- Vòng tìm kiếm trong Hash xâu; kiểm tra liên thông trong Kruskal;
  guard sàng (`R<2`), Pollard (`n<2`), `nCr` (biên `r`), Bignum div (`divisor==0`).
- Fibonacci fast doubling (`fib` gộp trong file Luỹ thừa nhanh).

### Fixed
- KMP: `i - 2*m + 1` → `i - 2*m`. Z: naive O(n²) → O(n); `z_matching`: `i - m - 1`;
  `num_substr` viết lại bằng đảo chuỗi.
- Sàng: `isPrime[i]` → `isPrime[j]`, `i*i` tràn int, vòng lặp thiếu kiểu `int`.
- Tổ hợp: `buildComb` dựng thiếu `fact[n]`; `MOD` → `MODC` (trùng tên hằng template).
- Nhân nhanh: 2 hàm trùng tên `Mult` (không biên dịch được) → `MultLog`/`MultO1`.
- MST: bỏ đọc thừa số `p`. Khớp/cầu: viết lại bằng id cạnh, điều kiện cầu
  `low[v]==num[v]` → `low[v]>num[u]`, gốc cây `u==pre` → `preEdge==-1`.
- Bignum `dif`: thiếu đệm 0, nhánh `(-x)+y` sai. Trie multiset: `sum` lên `long long`.
- Hình học 05/06/07: kiểu chưa định nghĩa → viết lại trên `Pt`; tia thiếu kiểm tra thẳng hàng.
- Trùng tên/định nghĩa: `string_matching`, `struct Pt`, `egcd` → gộp/xóa.
- Digit DP trừ số 0 khi `K==0`; Bitmask `res=-oo`; Dijkstra lên `long long`.
- Code sinh: `${paper}` thay thiếu 1 chỗ; tiêu đề cắt sai ở tên file có dấu chấm.

### Changed
- Chuẩn hoá comment tiếng Việt toàn notebook + VD bài áp dụng cho nhóm khó.
- Code sinh: log LaTeX realtime + in đuôi log khi lỗi.

### Removed
- Demo `main` Nhân ma trận; các dòng `#include` (ngầm hiểu `bits`, giữ `ext/pb_ds`).
