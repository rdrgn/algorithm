#include <cassert>
#include <climits>
#include <set>
#include <string>

class Trie {
 private:
  bool value;
  Trie *children[1 << CHAR_BIT];

 public:
  Trie() { std::fill(children, children + (1 << CHAR_BIT), nullptr); }
  void Insert(const std::string &s) { return this->Insert(s.data()); }
  void Insert(const char *s) {
    if (*s == '\0') {
      value = true;
    } else {
      if (this->children[*s] == nullptr) this->children[*s] = new Trie();
      this->children[*s]->Insert(s + 1);
    }
  }
  int Count(const std::string &s) { return this->Count(s.data()); }
  int Count(const char *s) {
    if (*s == '\0' && value) return 1;
    if (this->children[*s] == nullptr) return 0;
    return this->children[*s]->Count(s + 1);
  }
};

// test
int main() {
  Trie t;
  std::set<std::string> s = {"A", "to", "tea", "ted", "ten", "i", "in", "inn"};
  for (auto e : s) {
    assert(t.Count(e) == 0);
    t.Insert(e);
    assert(t.Count(e) == 1);
  }
  assert(t.Count("te") == 0);
}
