#include <cassert>
#include <vector>
using namespace std;

// Garner algorithm
class chinese_remainder_theorem {
 private:
  int mod;
  long long gcd(long long a, long long b, long long &x, long long &y) {
    if (b) {
      long long d = gcd(b, a % b, y, x);
      y -= a / b * x;
      return d;
    } else {
      x = 1;
      y = 0;
      return a;
    }
  }
  long long modulo_inverse(long long a, long long m) {
    long long x, y;
    gcd(a, m, x, y);
    return (x % m + m) % m;
  }

 public:
  chinese_remainder_theorem(int mod) : mod(mod) {}
  int operator()(const vector<int> &a, vector<int> m) {
    m.push_back(mod);
    vector<long long> coefficients(m.size(), 1);
    vector<long long> constants(m.size(), 0);
    for (int k = 0; k < a.size(); k++) {
      long long t = ((a[k] - constants[k]) * modulo_inverse(coefficients[k], m[k]) % m[k] + m[k]) % m[k];
      for (int i = k + 1; i < m.size(); i++) {
        constants[i] += t * coefficients[i];
        constants[i] %= m[i];
        coefficients[i] *= m[k];
        coefficients[i] %= m[i];
      }
    }
    return constants.back();
  }
};

int main() {
  chinese_remainder_theorem crt(1e9 + 7);
  assert(crt({2, 3, 2}, {3, 5, 7}) == 23);
  assert(crt({0, 3, 4}, {3, 4, 5}) == 39);
}
