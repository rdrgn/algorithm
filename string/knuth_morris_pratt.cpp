#include <cassert>
#include <iostream>
#include <string>
#include <vector>

// Morris-Pratt (MP) algorithm
// https://snuke.hatenablog.com/entry/2014/12/01/235807
template <class T>
std::vector<int> MorrisPratt(const T& s) {
  std::vector<int> a(s.size() + 1);
  a[0] = -1;
  for (int i = 0, j = -1; i < s.size(); i++) {
    while (j >= 0 && s[i] != s[j]) j = a[j];
    j++;
    a[i + 1] = j;
  }
  return a;
};

// Knuth-Morris-Pratt (KMP) algorithm
// not implemented

// test
int main() {
  std::string s = "aabaabaaa";
  std::vector<int> a{-1, 0, 1, 0, 1, 2, 3, 4, 5, 2};
  auto r = MorrisPratt(s);
  assert(r.size() == a.size());
  for (size_t i = 0; i < a.size(); i++) assert(r[i] == a[i]);
}
