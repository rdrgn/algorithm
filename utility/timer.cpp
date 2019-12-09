#include <cassert>
#include <chrono>

class Timer {
 public:
  Timer() : time_begin(Now()) {}
  int Elapsed() { return std::chrono::duration_cast<std::chrono::milliseconds>(Now() - time_begin).count(); }

 private:
  std::chrono::system_clock::time_point time_begin;
  static std::chrono::system_clock::time_point Now() { return std::chrono::system_clock::now(); }
};

// test
int main() {
  Timer t;
  int i = 0;
  while (t.Elapsed() < 1000) {
    i++;
  }
  assert(1000 <= t.Elapsed());
}
