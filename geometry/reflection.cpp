#include <cassert>
#include "2d.hpp"

// 点pから直線lへの射影点
Vector2 Projection(Line l, Vector2 p) {
  double t = Dot(l.second - l.first, p - l.first) / std::norm(l.second - l.first);
  return l.first + t * (l.second - l.first);
}

// 点pから直線lへの反射点
Vector2 Reflection(Line l, Vector2 p) { return 2.0 * Projection(l, p) - p; }

// test
int main() {
  Line l = {{1.0, 2.0}, {3.0, 4.0}};
  Vector2 p = {0.0, 0.0};
  assert(std::abs(Projection(l, p) - Vector2{-0.5, 0.5}) < EPS);
  assert(std::abs(Reflection(l, p) - Vector2{-1.0, 1.0}) < EPS);
}
