#include <cassert>
#include <cmath>

// a_1 + a_2 + ... + a_n (a_i = a_1 + (n - 1) * d)
template <class T>
T ArithmeticSeries(T a, T d, T n) {
  return n * (2 * a + (n - 1) * d) / 2;
}

// a_1 * a_2 * ... * a_n (a_i = a_1 + r ^ (n - 1))
template <class T>
T GeometricSeries(T a, T r, T n) {
  return r == 1 ? n * a : a * (pow(r, n) - 1) / (r - 1);
}

// test
int main() {
  for (int a = -100; a <= 100; a++) {
    for (int d = -100; d <= 100; d++) {
      for (int n = 0; n <= 100; n++) {
        int s = 0;
        for (int i = 0; i < n; i++) s += a + i * d;
        assert(ArithmeticSeries(a, d, n) == s);
      }
    }
  }

  for (int a = -100; a <= 100; a++) {
    for (int r = -5; r <= 5; r++) {
      for (int n = 0; n <= 5; n++) {
        int s = 0;
        for (int i = 0; i < n; i++) s += a * pow(r, i);
        assert(GeometricSeries(a, r, n) == s);
      }
    }
  }
}
