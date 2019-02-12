#include <time.h>
#include <cassert>
#include <iostream>
using namespace std;

class timer {
 public:
  timer() : time_begin(clock()) {}
  int elapsed() { return (int)1000 * (clock() - time_begin) / CLOCKS_PER_SEC; }

 private:
  clock_t time_begin;
};

int main() {
  timer t;
  int i = 0;
  while (t.elapsed() < 1000) {
    i++;
  }
  assert(1000 <= t.elapsed());
}
