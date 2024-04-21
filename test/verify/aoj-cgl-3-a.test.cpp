// competitive-verifier: PROBLEM http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_3_A

#include "../../template/template.hpp"

#include "../../geometry/area.hpp"

using namespace geometry;

int main() {
  int N;
  cin >> N;
  Polygon p(N);
  for(auto &s : p) cin >> s;
  cout << fixed << setprecision(1) << area(p) << "\n";
}
