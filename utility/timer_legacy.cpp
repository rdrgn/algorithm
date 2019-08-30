#include <time.h>
#include <cassert>
#include <iostream>
using namespace std;

class Timer {
 public:
  Timer() : time_begin(clock()) {}
  int Elapsed() { return (int)1000 * (clock() - time_begin) / CLOCKS_PER_SEC; }

 private:
  clock_t time_begin;
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
