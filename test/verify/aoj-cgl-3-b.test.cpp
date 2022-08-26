#define PROBLEM \
  "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_3_B"

#include "../../geometry/is_convex_polygon.hpp"
#include "../../template/template.hpp"

using namespace geometry;

int main() {
  int N;
  cin >> N;
  Polygon p(N);
  for (auto &s: p) cin >> s;
  cout << is_convex_polygon(p) << endl;
}
