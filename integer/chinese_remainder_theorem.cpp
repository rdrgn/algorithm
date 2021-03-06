#include <cassert>
#include <vector>

// Garner algorithm
template <class T, T MOD>
class ChineseRemainderTheorem {
 private:
  using S = typename std::vector<T>::size_type;
  T ExtendedGcd(T a, T b, T &x, T &y) {
    if (b) {
      T d = ExtendedGcd(b, a % b, y, x);
      y -= a / b * x;
      return d;
    } else {
      x = 1;
      y = 0;
      return a;
    }
  }
  T ModuloInverse(T a, T m) {
    T x, y;
    ExtendedGcd(a, m, x, y);
    return (x % m + m) % m;
  }

 public:
  T operator()(const std::vector<T> &a, std::vector<T> m) {
    m.push_back(MOD);
    std::vector<T> coefficients(m.size(), 1);
    std::vector<T> constants(m.size(), 0);
    for (S k = 0; k < a.size(); k++) {
      long long t = ((a[k] - constants[k]) * ModuloInverse(coefficients[k], m[k]) % m[k] + m[k]) % m[k];
      for (S i = k + 1; i < m.size(); i++) {
        constants[i] += t * coefficients[i];
        constants[i] %= m[i];
        coefficients[i] *= m[k];
        coefficients[i] %= m[i];
      }
    }
    return constants.back();
  }
};

// test
int main() {
  ChineseRemainderTheorem<long long, int(1e9 + 7)> crt;
  assert(crt({2, 3, 2}, {3, 5, 7}) == 23);
  assert(crt({0, 3, 4}, {3, 4, 5}) == 39);
}
