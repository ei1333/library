#define PROBLEM \
  "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_7_D"
#define ERROR 0.000001

#include "../../geometry/cross_point_cl.hpp"
#include "../../template/template.hpp"

using namespace geometry;

int main() {
  Circle c;
  cin >> c.p >> c.r;
  int Q;
  cin >> Q;
  while (Q--) {
    Line l;
    cin >> l;
    auto ret = cross_point_cl(c, l);
    if (ret.size() == 1) ret.emplace_back(ret[0]);
    if (!compare_x(ret[0], ret[1])) swap(ret[0], ret[1]);
    cout << ret[0] << " " << ret[1] << "\n";
  }
}
