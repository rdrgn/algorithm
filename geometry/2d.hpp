#include <complex>
using namespace std;

#define EPS (1e-6)
#define EQ(a, b) (abs((a) - (b)) < EPS)

typedef complex<double> vector2;
typedef pair<vector2, vector2> line;

// 内積
double dot(vector2 a, vector2 b) { return real(conj(a) * b); }

// 外積
double cross(vector2 a, vector2 b) { return imag(conj(a) * b); }

// 2直線の直行判定
bool is_orthogonal(line a, line b) { return EQ(dot(a.first - a.second, b.first - b.second), 0.0); }

// 2直線の平行判定
bool is_parallel(line a, line b) { return EQ(cross(a.first - a.second, b.first - b.second), 0.0); }

// 直線lと点pの距離
double distance_l(line l, vector2 p) { return abs(cross(l.second - l.first, p - l.first)) / abs(l.second - l.first); }

// 線分sと点pの距離
double distance_ls(line ls, vector2 p) {
  if (dot(ls.second - ls.first, p - ls.first) < EPS) return abs(p - ls.first);
  if (dot(ls.first - ls.second, p - ls.second) < EPS) return abs(p - ls.second);
  return abs(cross(ls.second - ls.first, p - ls.first)) / abs(ls.second - ls.first);
}

// 線分aと線分bの端点を除いた交差判定
bool is_intersected_ls(line a, line b) {
  return cross(a.second - a.first, b.first - a.first) * cross(a.second - a.first, b.second - a.first) < 0 &&
         cross(b.second - b.first, a.first - b.first) * cross(b.second - b.first, a.second - b.first) < 0;
}

// 直線aと直線bの交点
vector2 intersection_l(line a, line b) {
  vector2 u = a.second - a.first, v = b.second - b.first;
  return a.first + u * cross(v, b.first - a.first) / cross(v, u);
}
