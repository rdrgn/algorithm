#include <cassert>
#include <regex>
#include <string>
#include <vector>
using namespace std;

vector<string> Split(const string& s, const regex& separator) {
  vector<string> r;
  auto it = sregex_token_iterator(begin(s), end(s), separator, -1);
  auto it_end = sregex_token_iterator();
  while (it != it_end) r.push_back(*it++);
  return r;
}

string Join(const vector<string>& v, const string& separator) {
  if (v.empty()) return "";
  string r = v.front();
  for (auto it = begin(v) + 1; it != end(v); it++) {
    r += separator;
    r += *it;
  }
  return r;
}

// test
int main() {
  string s = "Jan,Feb,Mar,Apr,May,Jun,Jul,Aug,Sep,Oct,Nov,Dec";
  auto r = Join(Split(s, regex(",")), " / ");
  assert(r == "Jan / Feb / Mar / Apr / May / Jun / Jul / Aug / Sep / Oct / Nov / Dec");
}
