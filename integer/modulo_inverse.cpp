#include <cassert>
#include <utility>

template <class T>
T ModuloInverse(T a, T m) {
  T b = m, x = 1, y = 0;
  while (b) {
    T t = a / b;
    a -= t * b;
    x -= t * y;
    std::swap(a, b);
    std::swap(x, y);
  }
  return (m + x % m) % m;
}

// test
int main() {
  constexpr long long MOD = 1'000'000'007;
  for (long long a = 1; a <= 10'000'000; a++) assert(a * ModuloInverse(a, MOD) % MOD == 1);
}
