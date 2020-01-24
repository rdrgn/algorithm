#include <cassert>
#include <cmath>
#include <iostream>

// 台形制御
// https://tajimarobotics.com/acceleration-limited-feed-profile-2/
template <class T>
struct TrapezoidalControl {
  T displacement;
  T max_velocity;
  T max_acceleration;
  T peak_velocity;
  T time;
  T acceleration_time;
  T deceleration_time;

  TrapezoidalControl(T displacement, T max_velocity, T max_acceleration)
      : displacement(displacement), max_velocity(max_velocity), max_acceleration(max_acceleration) {
    T t1 = max_velocity / max_acceleration;
    T d1 = t1 * max_velocity / 2;
    T t2, d2;
    if (displacement - d1 - d1 < 0) {
      this->peak_velocity = sqrt(max_acceleration * displacement);
      t1 = this->peak_velocity / max_acceleration;
      d1 = t1 * this->peak_velocity / 2;
      t2 = 0;
      d2 = 0;
    } else {
      this->peak_velocity = max_velocity;
      d2 = displacement - d1 - d1;
      t2 = d2 / max_velocity;
    }
    this->time = t1 + t2 + t1;
    this->acceleration_time = t1;
    this->deceleration_time = t1;
  }
};

// test
int main() {
  auto tc = TrapezoidalControl<double>(2.0, 1.0, 1.0);

  std::cout << "displacement: " << tc.displacement << std::endl;
  std::cout << "max_velocity: " << tc.max_velocity << std::endl;
  std::cout << "max_acceleration: " << tc.max_acceleration << std::endl;
  std::cout << "peak_velocity: " << tc.peak_velocity << std::endl;
  std::cout << "time: " << tc.time << std::endl;
  std::cout << "acceleration_time: " << tc.acceleration_time << std::endl;
  std::cout << "deceleration_time: " << tc.deceleration_time << std::endl;

  constexpr double EPS = 1e-9;
  double d1 = tc.peak_velocity * tc.acceleration_time / 2.0;
  double d2 = tc.peak_velocity * (tc.time - tc.acceleration_time - tc.deceleration_time);
  double d3 = tc.peak_velocity * tc.deceleration_time / 2.0;
  assert(std::abs((d1 + d2 + d3) - tc.displacement) < EPS);
}
