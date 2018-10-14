#include <cassert>
#include <vector>
using namespace std;

class modulo_combination {
 private:
  vector<int> factrial, inverse;
  int mod;
  int pow(int x, int y) {
    if (y == 0) return 1;
    if (y % 2 == 0) return pow((long long)x * x % mod, y / 2);
    return (long long)x * pow(x, y - 1) % mod;
  }

 public:
  modulo_combination(int n, int mod) : factrial(n + 1), inverse(n + 1), mod(mod) {
    inverse[0] = factrial[0] = 1;
    for (int i = 1; i <= n; i++) {
      factrial[i] = (long long)factrial[i - 1] * i % mod;
      inverse[i] = pow(factrial[i], mod - 2);
    }
  }
  int operator()(int n, int k) { return (long long)factrial[n] * inverse[k] % mod * inverse[n - k] % mod; }
};

int main() {
  modulo_combination c(300000, 1000000007);
  assert(c(1, 1) == 1);
  assert(c(10, 5) == 252);
  assert(c(300000, 150000) == 782364718);
  modulo_combination c_alt(300000, 998244353);
  assert(c_alt(300000, 150000) == 442086455);
}
