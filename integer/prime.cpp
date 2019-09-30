#include <cassert>
#include <vector>

// https://imulan.hatenablog.jp/entry/2019/09/29/212808
class Prime {
 private:
  std::vector<size_t> mind, primes;

 public:
  Prime(size_t n) : mind(n + 1) {
    mind[0] = mind[1] = 1;
    for (size_t i = 2; i < n; i++) {
      if (mind[i] == 0) {
        primes.push_back(i);
        mind[i] = i;
      }
      for (auto p : primes) {
        if (!(p <= mind[i] && i * p < n)) break;
        mind[i * p] = p;
      }
    }
  }
  bool operator()(size_t a) { return a >= 2 && mind[a] == a; }
};

// test
int main() {
  size_t n = 1e5;

  std::vector<bool> sieve_of_eratosthenes(n + 1, true);
  sieve_of_eratosthenes[0] = sieve_of_eratosthenes[1] = false;
  for (size_t i = 2; i <= n; ++i) {
    if (sieve_of_eratosthenes[i]) {
      for (size_t j = 2 * i; j <= n; j += i) sieve_of_eratosthenes[j] = false;
    }
  }

  Prime is_prime(n);
  for (size_t i = 0; i <= n; ++i) {
    assert(is_prime(i) == sieve_of_eratosthenes[i]);
  }
}
