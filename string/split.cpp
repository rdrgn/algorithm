#include <cassert>
#include <regex>
#include <string>
#include <vector>

std::vector<std::string> Split(const std::string& s, const std::regex& separator) {
  std::vector<std::string> r;
  auto it = std::sregex_token_iterator(s.begin(), s.end(), separator, -1);
  auto it_end = std::sregex_token_iterator();
  while (it != it_end) r.push_back(*it++);
  return r;
}

std::string Join(const std::vector<std::string>& v, const std::string& separator) {
  if (v.empty()) return "";
  std::string r = v.front();
  for (auto it = v.begin() + 1; it != v.end(); it++) {
    r += separator;
    r += *it;
  }
  return r;
}

// test
int main() {
  std::string s = "Jan,Feb,Mar,Apr,May,Jun,Jul,Aug,Sep,Oct,Nov,Dec";
  auto r = Join(Split(s, std::regex(",")), " / ");
  assert(r == "Jan / Feb / Mar / Apr / May / Jun / Jul / Aug / Sep / Oct / Nov / Dec");
}
