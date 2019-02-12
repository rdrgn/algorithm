#include <cassert>
#include <chrono>
using namespace std;

class timer {
 public:
  timer() : time_begin(now()) {}
  int elapsed() { return chrono::duration_cast<chrono::milliseconds>(now() - time_begin).count(); }

 private:
  chrono::system_clock::time_point time_begin;
  static chrono::system_clock::time_point now() { return chrono::system_clock::now(); }
};

int main() {
  timer t;
  int i = 0;
  while (t.elapsed() < 1000) {
    i++;
  }
  assert(1000 <= t.elapsed());
}
