#define PROBLEM \
  "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_7_E"
#define ERROR 0.000001

#include "../../geometry/cross_point_cc.hpp"
#include "../../template/template.hpp"

using namespace geometry;

int main() {
  Circle x, y;
  cin >> x.p >> x.r >> y.p >> y.r;
  auto ret = cross_point_cc(x, y);
  if (ret.size() == 1) ret.emplace_back(ret[0]);
  if (!compare_x(ret[0], ret[1])) swap(ret[0], ret[1]);
  cout << ret[0] << " " << ret[1] << "\n";
}
