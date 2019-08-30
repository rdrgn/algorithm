#define _USE_MATH_DEFINES
#include <cmath>
#include <complex>

#define EPS (1e-6)
#define EQ(a, b) (std::abs((a) - (b)) < EPS)

using Vector2 = std::complex<double>;
using Line = std::pair<Vector2, Vector2>;

// 内積 |a||b|cosΘ
double Dot(Vector2 a, Vector2 b) { return std::real(std::conj(a) * b); }

// 外積 |a||b|sinΘ
double Cross(Vector2 a, Vector2 b) { return std::imag(std::conj(a) * b); }

// 2ベクトル間の角度・回転方向 [-π, π]
double Angle(Vector2 a, Vector2 b) { return std::atan2(Cross(a, b), Dot(a, b)); }

// 2直線の直行判定
bool IsOrthogonal(Line a, Line b) { return EQ(Dot(a.first - a.second, b.first - b.second), 0.0); }

// 2直線の平行判定
bool IsParallel(Line a, Line b) { return EQ(Cross(a.first - a.second, b.first - b.second), 0.0); }

// 直線lと点pの距離
double DistanceL(Line l, Vector2 p) {
  return abs(Cross(l.second - l.first, p - l.first)) / std::abs(l.second - l.first);
}

// 線分sと点pの距離
double DistanceLS(Line ls, Vector2 p) {
  if (Dot(ls.second - ls.first, p - ls.first) < EPS) return std::abs(p - ls.first);
  if (Dot(ls.first - ls.second, p - ls.second) < EPS) return std::abs(p - ls.second);
  return abs(Cross(ls.second - ls.first, p - ls.first)) / std::abs(ls.second - ls.first);
}

// 線分aと線分bの端点を除いた交差判定
bool IsIntersectedLS(Line a, Line b) {
  return Cross(a.second - a.first, b.first - a.first) * Cross(a.second - a.first, b.second - a.first) < 0 &&
         Cross(b.second - b.first, a.first - b.first) * Cross(b.second - b.first, a.second - b.first) < 0;
}

// 直線aと直線bの交点
Vector2 IntersectionL(Line a, Line b) {
  Vector2 u = a.second - a.first, v = b.second - b.first;
  return a.first + u * Cross(v, b.first - a.first) / Cross(v, u);
}
