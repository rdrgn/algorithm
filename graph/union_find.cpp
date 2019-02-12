#include <cassert>
#include <vector>
using namespace std;

class union_find {
 private:
  vector<int> parent;
  vector<int> rank;
  vector<int> sizes;

 public:
  union_find(int n) : parent(n), rank(n), sizes(n, 1) {
    for (int i = 0; i < n; i++) parent[i] = i;
  }
  void unite(int a, int b) {
    a = find(a);
    b = find(b);
    if (a == b) return;
    if (rank[a] < rank[b]) {
      parent[a] = b;
    } else {
      parent[b] = a;
      if (rank[a] == rank[b]) rank[a]++;
    }
    sizes[find(a)] = sizes[a] + sizes[b];
  }
  int find(int a) { return parent[a] == a ? a : parent[a] = find(parent[a]); }
  int size(int a) { return sizes[find(a)]; }
};

int main() {
  union_find uf(6);
  assert(uf.size(2) == 1);
  uf.unite(0, 2);
  uf.unite(1, 3);
  uf.unite(5, 1);
  assert(uf.find(0) == 0);
  assert(uf.find(1) == 1);
  assert(uf.find(2) == 0);
  assert(uf.find(3) == 1);
  assert(uf.find(4) == 4);
  assert(uf.find(5) == 1);
  assert(uf.size(2) == 2);
  uf.unite(0, 1);
  assert(uf.find(0) == 0);
  assert(uf.find(1) == 0);
  assert(uf.find(2) == 0);
  assert(uf.find(3) == 0);
  assert(uf.find(4) == 4);
  assert(uf.find(5) == 0);
  assert(uf.size(2) == 5);
}
