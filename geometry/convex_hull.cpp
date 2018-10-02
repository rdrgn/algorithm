#include <algorithm>
#include <cassert>
#include <vector>
#include "2d.hpp"
using namespace std;

vector<int> graham_scan(const vector<vector2> &p) {
  int n = p.size();
  vector<int> hull = {0};
  vector2 o = p.front();
  for (int i = 0; i < n; i++) {
    if (p[i].imag() != o.imag() ? p[i].imag() < o.imag() : p[i].real() < o.real()) {
      hull[0] = i;
      o = p[i];
    }
  }
  vector<vector2> d(n);
  for (int i = 0; i < n; i++) d[i] = p[i] - o;
  vector<int> v(n);
  for (int i = 0; i < n; i++) v[i] = i;
  swap(v[hull.front()], v.back());
  sort(begin(v), end(v) - 1, [&d](int a, int b) {
    double r = angle(d[a], d[b]);
    return r != 0 ? r > 0 : abs(d[a]) < abs(d[b]);
  });
  for (auto i : v) {
    while (hull.size() >= 2 && cross(p[*rbegin(hull)] - p[*(rbegin(hull) + 1)], p[i] - p[*(rbegin(hull) + 1)]) <= 0) {
      hull.pop_back();
    }
    hull.push_back(i);
  }
  hull.pop_back();
  return hull;
}

int main() {
  vector<vector2> p1 = {{-1.0, -1.0}, {0.0, -1.0}, {1.0, -1.0}, {-1.0, 0.0}, {0.0, 0.0},
                        {1.0, 0.0},   {-1.0, 1.0}, {0.0, 1.0},  {1.0, 1.0}};
  vector<vector2> p2 = {{0.0, 0.0}, {0.0, 1e9}, {1e9, 0.0}};
  vector<int> h1 = {0, 2, 8, 6}, h2 = {0, 2, 1};
  assert(graham_scan(p1) == h1);
  assert(graham_scan(p2) == h2);
}
