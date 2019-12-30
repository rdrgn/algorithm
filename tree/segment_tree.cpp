#include <algorithm>
#include <functional>
#include <iostream>
#include <vector>

template <class Monoid>
class SegmentTree {
 private:
  using S = typename std::vector<Monoid>::size_type;
  using F = std::function<Monoid(Monoid, Monoid)>;
  S size;
  std::vector<Monoid> nodes;
  const Monoid identity;
  const F operate;

 public:
  SegmentTree(S n, const Monoid& identity, const F& operate) : identity(identity), operate(operate) {
    size = 1;
    while (size < n) size *= 2;
    nodes.assign(2 * size, identity);
  }
  void Update(S i, const Monoid& x) {
    i += (size - 1);
    nodes[i] = x;
    while (i > 0) {
      i = (i - 1) / 2;
      nodes[i] = operate(nodes[2 * i + 1], nodes[2 * i + 2]);
    }
  }
  Monoid Query(S begin, S end, S i = 0, S b = 0, S e = 0) {
    if (e == 0) e = size;
    if (e <= begin || end <= b) return identity;
    if (begin <= b && e <= end) return nodes[i];
    return operate(Query(begin, end, 2 * i + 1, b, (b + e) / 2), Query(begin, end, 2 * i + 2, (b + e) / 2, e));
  }
};

// test
// https://onlinejudge.u-aizu.ac.jp/courses/library/3/DSL/2/DSL_2_A
int main() {
  int n, q;
  std::cin >> n >> q;
  SegmentTree<int> st(n, (1ll << 31) - 1, [](int a, int b) { return std::min(a, b); });
  for (; q > 0; q--) {
    int c, x, y;
    std::cin >> c >> x >> y;
    if (c == 0) {
      st.Update(x, y);
    } else {
      std::cout << st.Query(x, y + 1) << '\n';
    }
  }
  std::cout << std::flush;
}
