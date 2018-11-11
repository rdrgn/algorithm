#include <cassert>
#include <chrono>
using namespace std;

class timer {
 public:
  timer() : enabled(false), time_elapsed() {}
  void start() {
    if (!enabled) time_begin = now();
  }
  void stop() {
    if (!enabled) return;
    time_elapsed += now() - time_begin;
    enabled = false;
  }
  int elapsed() {
    auto t = time_elapsed;
    if (enabled) t += now() - time_begin;
    return chrono::duration_cast<chrono::milliseconds>(t).count();
  }

 private:
  bool enabled;
  chrono::system_clock::time_point time_begin;
  chrono::system_clock::duration time_elapsed;
  static chrono::system_clock::time_point now() { chrono::system_clock::now(); }
};

int main() {
  timer t;
  assert(t.elapsed() == 0);
  t.start();
  int a = t.elapsed();
  assert(a <= t.elapsed());
  t.stop();
  assert(t.elapsed() == t.elapsed());
  t.start();
  int b = t.elapsed();
  assert(b <= t.elapsed());
}
