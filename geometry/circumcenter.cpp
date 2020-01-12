#include <cassert>
#include <cmath>
#include <complex>
#include <iomanip>
#include <iostream>
#include <vector>

#define EPS (1e-6)
#define EQ(a, b) (std::abs((a) - (b)) < EPS)
using Vector2 = std::complex<double>;
double Dot(Vector2 a, Vector2 b) { return std::real(std::conj(a) * b); }
double Cross(Vector2 a, Vector2 b) { return std::imag(std::conj(a) * b); }

// 外心
// https://ja.wikipedia.org/wiki/%E5%A4%96%E6%8E%A5%E5%86%86
Vector2 Circumcenter(Vector2 a, Vector2 b, Vector2 c) {
  using T = Vector2::value_type;
  T ab2 = Dot(b - a, b - a), bc2 = Dot(c - b, c - b), ca2 = Dot(a - c, a - c);
  T x = bc2 * (ca2 + ab2 - bc2), y = ca2 * (ab2 + bc2 - ca2), z = ab2 * (bc2 + ca2 - ab2);
  return (x * a + y * b + z * c) / (x + y + z);
}

// test
// https://atcoder.jp/contests/abc151/tasks/abc151_f
int main() {
  int n;
  std::cin >> n;
  std::vector<Vector2> v(n);
  for (auto &e : v) {
    int x, y;
    std::cin >> x >> y;
    e.real(x);
    e.imag(y);
  }

  double r = 1e9;
  for (int i = 0; i < n; i++) {
    for (int j = i + 1; j < n; j++) {
      {
        auto p = (v[i] + v[j]) / 2.0;
        double t = 0;
        for (auto e : v) t = std::max(t, std::abs(e - p));
        r = std::min(r, t);
      }
      for (int k = j + 1; k < n; k++) {
        if (EQ(Cross(v[j] - v[i], v[k] - v[i]), 0.0)) continue;
        auto p = Circumcenter(v[i], v[j], v[k]);
        double t = 0;
        for (auto e : v) t = std::max(t, std::abs(e - p));
        r = std::min(r, t);
      }
    }
  }
  std::cout << std::fixed << std::setprecision(7);
  std::cout << r << std::endl;
}
