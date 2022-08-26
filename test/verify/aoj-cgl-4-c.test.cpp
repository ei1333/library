#define PROBLEM \
  "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_4_C"
#define ERROR 0.00001

#include "../../geometry/area.hpp"
#include "../../geometry/convex_polygon_cut.hpp"
#include "../../template/template.hpp"

using namespace geometry;

int main() {
  int n;
  cin >> n;
  Polygon poly(n);
  for (auto &p: poly) {
    cin >> p;
  }
  int q;
  cin >> q;
  while (q--) {
    Line l;
    cin >> l;
    cout << area(convex_polygon_cut(poly, l)) << "\n";
  }
}
