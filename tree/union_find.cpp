#include <cassert>
#include <vector>

class UnionFind {
 private:
  std::vector<size_t> parents;
  std::vector<size_t> ranks;
  std::vector<size_t> sizes;

 public:
  UnionFind(size_t n) : parents(n), ranks(n), sizes(n, 1) {
    for (size_t i = 0; i < n; i++) parents[i] = i;
  }
  void Unite(size_t a, size_t b) {
    a = Find(a);
    b = Find(b);
    if (a == b) return;
    if (ranks[a] < ranks[b]) {
      parents[a] = b;
    } else {
      parents[b] = a;
      if (ranks[a] == ranks[b]) ranks[a]++;
    }
    sizes[Find(a)] = sizes[a] + sizes[b];
  }
  int Find(size_t a) { return parents[a] == a ? a : parents[a] = Find(parents[a]); }
  int Size(size_t a) { return sizes[Find(a)]; }
};

// test
int main() {
  UnionFind uf(6);
  assert(uf.Size(2) == 1);
  uf.Unite(0, 2);
  uf.Unite(1, 3);
  uf.Unite(5, 1);
  assert(uf.Find(0) == 0);
  assert(uf.Find(1) == 1);
  assert(uf.Find(2) == 0);
  assert(uf.Find(3) == 1);
  assert(uf.Find(4) == 4);
  assert(uf.Find(5) == 1);
  assert(uf.Size(2) == 2);
  uf.Unite(0, 1);
  assert(uf.Find(0) == 0);
  assert(uf.Find(1) == 0);
  assert(uf.Find(2) == 0);
  assert(uf.Find(3) == 0);
  assert(uf.Find(4) == 4);
  assert(uf.Find(5) == 0);
  assert(uf.Size(2) == 5);
}
