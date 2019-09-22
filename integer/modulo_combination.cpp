#include <cassert>
#include <vector>

template <typename T, T MOD>
class ModuloCombination {
 private:
  std::vector<T> factrial, inverse_factrial;
  T Pow(T x, T y) {
    if (y == 0) return 1;
    if (y % 2 == 0) return Pow(x * x % MOD, y / 2);
    return x * Pow(x, y - 1) % MOD;
  }

 public:
  ModuloCombination(T n) : factrial(n + 1), inverse_factrial(n + 1) {
    inverse_factrial[0] = factrial[0] = 1;
    for (T i = 1; i <= n; i++) {
      factrial[i] = factrial[i - 1] * i % MOD;
      inverse_factrial[i] = Pow(factrial[i], MOD - 2);
    }
  }
  T operator()(T n, T k) {
    if (n < 0 || k < 0 || n < k) return 0;
    return factrial[n] * inverse_factrial[k] % MOD * inverse_factrial[n - k] % MOD;
  }
};

// test
int main() {
  ModuloCombination<long long, int(1e9 + 7)> c(300000);
  assert(c(1, 1) == 1);
  assert(c(10, 5) == 252);
  assert(c(300000, 150000) == 782364718);
  assert(c(-1, 1) == 0);
  assert(c(1, -1) == 0);
  assert(c(1, 2) == 0);
  ModuloCombination<long long, 998244353> c_alt(300000);
  assert(c_alt(300000, 150000) == 442086455);
}
