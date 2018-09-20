#include "2d.hpp"
#include <cassert>
using namespace std;

int main() {
  vector2 v1 = {1.0, 2.0}, v2 = {3.0, 4.0};
  assert(EQ(dot(v1, v2), 11.0));
  assert(EQ(cross(v1, v2), -2.0));
  assert(EQ(angle(v1, v2), atan2(v2.imag(), v2.real()) - atan2(v1.imag(), v1.real())));
}
