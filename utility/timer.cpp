#include <cassert>
#include <chrono>
#include <iostream>
using namespace std;

class timer {
 public:
  timer() : time_begin(timer::now()) {}
  int elapsed() { return chrono::duration_cast<chrono::milliseconds>(timer::now() - time_begin).count(); }

 private:
  chrono::system_clock::time_point time_begin;
  static chrono::system_clock::time_point now() { chrono::system_clock::now(); }
};

int main() {
  timer t;
  int a, b;
  a = t.elapsed();
  do {
    b = t.elapsed();
  } while (b < 1000);
  assert(a < b);
}
