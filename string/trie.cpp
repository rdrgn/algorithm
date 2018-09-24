#include <cassert>
#include <climits>
#include <set>
#include <string>
using namespace std;

class trie {
 private:
  bool value;
  trie *children[1 << CHAR_BIT];

 public:
  trie() { fill(children, children + (1 << CHAR_BIT), nullptr); }
  void insert(const string &s) { return this->insert(s.data()); }
  void insert(const char *s) {
    if (*s == '\0') {
      value = true;
    } else {
      if (this->children[*s] == nullptr) this->children[*s] = new trie();
      this->children[*s]->insert(s + 1);
    }
  }
  int count(const string &s) { return this->count(s.data()); }
  int count(const char *s) {
    if (*s == '\0' && value) return 1;
    if (this->children[*s] == nullptr) return 0;
    return this->children[*s]->count(s + 1);
  }
};

int main() {
  trie t;
  set<string> s = {"A", "to", "tea", "ted", "ten", "i", "in", "inn"};
  for (auto e : s) {
    assert(t.count(e) == 0);
    t.insert(e);
    assert(t.count(e) == 1);
  }
  assert(t.count("te") == 0);
}
