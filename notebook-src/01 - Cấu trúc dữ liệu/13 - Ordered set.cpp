using namespace std;

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace __gnu_pbds;

typedef tree <int, null_type, less <int>, rb_tree_tag,
  tree_order_statistics_node_update> ordered_set;
ordered_set o_set;

int main()
{
    // O(log(n)) thêm, xoá phần tử
    o_set.insert(4); o_set.insert(1);
    o_set.insert(0); o_set.insert(9);
    o_set.insert(4); o_set.insert(5);
    o_set.insert(8);

    for (auto it = o_set.begin(); it != o_set.end(); it++)
        cout << *it << " ";
    cout << "\n\n";

    int k;
    // số nhỏ thứ k = 4;       // O(log(n))
    k = 4; cout << *(o_set.find_by_order(k-1)) << "\n\n";
    // số lượng số < k (= 5);  // O(log(n))
    k = 5; cout << o_set.order_of_key(k)       << "\n\n";

    // số lượng số x thuộc [l, r] = [1; r + 1) - [1; l) O(2*log(n))
    int l = 4, r = 9;
    cout << o_set.order_of_key(r+1) - o_set.order_of_key(l) << "\n\n";

    cout << "o_set.size: " << o_set.size() << "\n\n";
    cout << "o_set.erase(" << k << ")\n\n"; o_set.erase(k);
    cout << "o_set.size: " << o_set.size() << "\n\n";

    for (auto it = o_set.begin(); it != o_set.end(); it++)
        cout << *it << " ";
}
