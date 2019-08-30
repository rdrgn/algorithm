#include <algorithm>
#include <cassert>
#include <vector>
#include "2d.hpp"

std::vector<int> GrahamScan(const std::vector<Vector2> &p) {
  int n = p.size();
  std::vector<int> hull = {0};
  Vector2 o = p.front();
  for (int i = 0; i < n; i++) {
    if (p[i].imag() != o.imag() ? p[i].imag() < o.imag() : p[i].real() < o.real()) {
      hull[0] = i;
      o = p[i];
    }
  }
  std::vector<Vector2> d(n);
  for (int i = 0; i < n; i++) d[i] = p[i] - o;
  std::vector<int> v(n);
  for (int i = 0; i < n; i++) v[i] = i;
  std::swap(v[hull.front()], v.back());
  std::sort(std::begin(v), std::end(v) - 1, [&d](int a, int b) {
    double r = Angle(d[a], d[b]);
    return r != 0 ? r > 0 : abs(d[a]) < abs(d[b]);
  });
  for (auto i : v) {
    while (hull.size() >= 2 &&
           Cross(p[*std::rbegin(hull)] - p[*(std::rbegin(hull) + 1)], p[i] - p[*(std::rbegin(hull) + 1)]) <= 0) {
      hull.pop_back();
    }
    hull.push_back(i);
  }
  hull.pop_back();
  return hull;
}

// test
int main() {
  std::vector<Vector2> p1 = {{-1.0, -1.0}, {0.0, -1.0}, {1.0, -1.0}, {-1.0, 0.0}, {0.0, 0.0},
                             {1.0, 0.0},   {-1.0, 1.0}, {0.0, 1.0},  {1.0, 1.0}};
  std::vector<Vector2> p2 = {{0.0, 0.0}, {0.0, 1e9}, {1e9, 0.0}};
  std::vector<int> h1 = {0, 2, 8, 6}, h2 = {0, 2, 1};
  assert(GrahamScan(p1) == h1);
  assert(GrahamScan(p2) == h2);
}
