#include <vector>

template <typename T, T mod>
class ModuloCombination {
 private:
  std::vector<T> factrial, inverse_factrial;
  T Pow(T x, T y) {
    if (y == 0) return 1;
    if (y % 2 == 0) return Pow(x * x % mod, y / 2);
    return x * Pow(x, y - 1) % mod;
  }

 public:
  ModuloCombination(T n) : factrial(n + 1), inverse_factrial(n + 1) {
    inverse_factrial[0] = factrial[0] = 1;
    for (T i = 1; i <= n; i++) {
      factrial[i] = factrial[i - 1] * i % mod;
      inverse_factrial[i] = Pow(factrial[i], mod - 2);
    }
  }
  T operator()(T n, T k) { return factrial[n] * inverse_factrial[k] % mod * inverse_factrial[n - k] % mod; }
};

// test
#include <cassert>

int main() {
  ModuloCombination<long long, int(1e9 + 7)> c(300000);
  assert(c(1, 1) == 1);
  assert(c(10, 5) == 252);
  assert(c(300000, 150000) == 782364718);
  ModuloCombination<long long, 998244353> c_alt(300000);
  assert(c_alt(300000, 150000) == 442086455);
}
