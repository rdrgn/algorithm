#include <vector>

class UnionFind {
 private:
  std::vector<int> parent;
  std::vector<int> rank;
  std::vector<int> sizes;

 public:
  UnionFind(int n) : parent(n), rank(n), sizes(n, 1) {
    for (int i = 0; i < n; i++) parent[i] = i;
  }
  void Unite(int a, int b) {
    a = Find(a);
    b = Find(b);
    if (a == b) return;
    if (rank[a] < rank[b]) {
      parent[a] = b;
    } else {
      parent[b] = a;
      if (rank[a] == rank[b]) rank[a]++;
    }
    sizes[Find(a)] = sizes[a] + sizes[b];
  }
  int Find(int a) { return parent[a] == a ? a : parent[a] = Find(parent[a]); }
  int Size(int a) { return sizes[Find(a)]; }
};

// test
#include <cassert>

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
