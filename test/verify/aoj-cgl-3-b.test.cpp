// competitive-verifier: PROBLEM http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_3_B

#include "../../template/template.hpp"

#include "../../geometry/is_convex_polygon.hpp"

using namespace geometry;

int main() {
  int N;
  cin >> N;
  Polygon p(N);
  for(auto &s : p) cin >> s;
  cout << is_convex_polygon(p) << endl;
}
