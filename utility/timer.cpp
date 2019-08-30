#include <cassert>
#include <chrono>
using namespace std;

class Timer {
 public:
  Timer() : time_begin(Now()) {}
  int Elapsed() { return chrono::duration_cast<chrono::milliseconds>(Now() - time_begin).count(); }

 private:
  chrono::system_clock::time_point time_begin;
  static chrono::system_clock::time_point Now() { return chrono::system_clock::now(); }
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
