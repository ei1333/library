// competitive-verifier: PROBLEM http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_7_H
// competitive-verifier: ERROR 0.00001

#include "../../template/template.hpp"

#include "../../geometry/common_area_cp.hpp"

using namespace geometry;

int main() {
  int N;
  Real R;
  cin >> N >> R;
  Circle c(Point(0, 0), R);
  Polygon p(N);
  for(auto &s : p) cin >> s;
  cout << common_area_cp(c, p) << endl;
}
