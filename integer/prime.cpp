#include <cassert>
#include <vector>

// https://imulan.hatenablog.jp/entry/2019/09/29/212808
template <class T>
class Prime {
 private:
  using S = typename std::vector<T>::size_type;
  std::vector<T> mind, primes;

 public:
  Prime(T n) : mind(n + 1) {
    mind[0] = mind[1] = 1;
    for (T i = 2; i < n; i++) {
      if (mind[i] == 0) primes.push_back(mind[i] = i);
      for (auto p : primes) {
        if (!(p <= mind[i] && i * p < n)) break;
        mind[i * p] = p;
      }
    }
  }
  bool operator()(T a) const { return a >= 2 && mind[a] == a; }
  T operator[](S i) const { return primes[i]; }
  S count() const { return primes.size(); }
};

// test
int main() {
  int n = 10'000'000;

  std::vector<int> primes;
  std::vector<bool> sieve_of_eratosthenes(n + 1, true);
  sieve_of_eratosthenes[0] = sieve_of_eratosthenes[1] = false;
  for (size_t i = 2; i <= n; ++i) {
    if (sieve_of_eratosthenes[i]) {
      primes.push_back(i);
      for (size_t j = 2 * i; j <= n; j += i) sieve_of_eratosthenes[j] = false;
    }
  }

  Prime<int> prime(n);
  assert(prime.count() == primes.size());
  for (size_t i = 0; i < prime.count(); i++) assert(prime[i] == primes[i]);
  for (size_t i = 0; i <= n; ++i) assert(prime(i) == sieve_of_eratosthenes[i]);
}
