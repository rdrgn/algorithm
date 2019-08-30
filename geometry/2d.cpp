#include "2d.hpp"
#include <cassert>

// test
int main() {
  Vector2 v1 = {1.0, 2.0}, v2 = {3.0, 4.0};
  assert(EQ(Dot(v1, v2), 11.0));
  assert(EQ(Cross(v1, v2), -2.0));
  assert(EQ(Angle(v1, v2), std::atan2(v2.imag(), v2.real()) - std::atan2(v1.imag(), v1.real())));
}
