// competitive-verifier: PROBLEM http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_7_E
// competitive-verifier: ERROR 0.000001

#include "../../template/template.hpp"

#include "../../geometry/cross_point_cc.hpp"

using namespace geometry;

int main() {
  Circle x, y;
  cin >> x.p >> x.r >> y.p >> y.r;
  auto ret = cross_point_cc(x, y);
  if(ret.size() == 1) ret.emplace_back(ret[0]);
  if(!compare_x(ret[0], ret[1])) swap(ret[0], ret[1]);
  cout << ret[0] << " " << ret[1] << "\n";
}
