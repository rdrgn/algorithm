#include <cassert>
#include "2d.hpp"
using namespace std;

// 点pから直線lへの射影点
vector2 projection(line l, vector2 p) {
  double t = dot(l.second - l.first, p - l.first) / norm(l.second - l.first);
  return l.first + t * (l.second - l.first);
}

// 点pから直線lへの反射点
vector2 reflection(line l, vector2 p) { return 2.0 * projection(l, p) - p; }

int main() {
  line l = {{1.0, 2.0}, {3.0, 4.0}};
  vector2 p = {0.0, 0.0};
  assert(abs(projection(l, p) - vector2{-0.5, 0.5}) < EPS);
  assert(abs(reflection(l, p) - vector2{-1.0, 1.0}) < EPS);
}
