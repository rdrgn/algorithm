#include <cassert>
#include <vector>

template <typename T>
std::vector<std::vector<T>> MagicSquare(T n) {
  std::vector<std::vector<T>> a(n, std::vector<T>(n));
  if (n < 1 || n == 2) return a;
  if (n == 1) {
    a[0][0] = 1;
  } else if (n % 2 == 1) {
    T i = 0, j = n / 2;
    for (T k = 1; k <= n * n; k++) {
      if (a[i][j]) {
        i = (i + 2) % n;
        j = (n + j - 1) % n;
      }
      a[i][j] = k;
      i = (n + i - 1) % n;
      j = (j + 1) % n;
    }
  } else if (n % 4 == 0) {
    for (T i = 0; i < n; i++) {
      for (T j = 0; j < n; j++) {
        if (i % 4 == j % 4 || (i + j) % 4 == 3) {
          a[i][j] = n * i + j + 1;
        } else {
          a[i][j] = n * n - (n * i + j);
        }
      }
    }
  } else {
    auto b = MagicSquare(n / 2);
    for (auto& bi : b) {
      for (auto& bij : bi) bij = 4 * (bij - 1);
    }
    for (T i = 0; i < n / 2; i++) {
      for (T j = 0; j < n / 2; j++) {
        if (i > n / 4 + 1) {
          a[2 * i][2 * j] = b[i][j] + 1;
          a[2 * i][2 * j + 1] = b[i][j] + 4;
          a[2 * i + 1][2 * j] = b[i][j] + 3;
          a[2 * i + 1][2 * j + 1] = b[i][j] + 2;
        } else if (i == n / 4 + 1 && j != n / 4 || i == n / 4 && j == n / 4) {
          a[2 * i][2 * j] = b[i][j] + 1;
          a[2 * i][2 * j + 1] = b[i][j] + 4;
          a[2 * i + 1][2 * j] = b[i][j] + 2;
          a[2 * i + 1][2 * j + 1] = b[i][j] + 3;
        } else {
          a[2 * i][2 * j] = b[i][j] + 4;
          a[2 * i][2 * j + 1] = b[i][j] + 1;
          a[2 * i + 1][2 * j] = b[i][j] + 2;
          a[2 * i + 1][2 * j + 1] = b[i][j] + 3;
        }
      }
    }
  }
  return a;
}

// test
int main() {
  for (int n = 1; n <= 1000; n++) {
    if (n == 2) continue;
    auto a = MagicSquare(n);
    int t = n * (n * n + 1) / 2;
    for (int i = 0; i < n; i++) {
      int s = 0;
      for (int j = 0; j < n; j++) s += a[i][j];
      assert(s == t);
    }
    for (int j = 0; j < n; j++) {
      int s = 0;
      for (int i = 0; i < n; i++) s += a[i][j];
      assert(s == t);
    }
    {
      int s = 0;
      for (int i = 0; i < n; i++) s += a[i][i];
      assert(s == t);
    }
    {
      int s = 0;
      for (int i = 0; i < n; i++) s += a[i][n - 1 - i];
      assert(s == t);
    }
  }
}
