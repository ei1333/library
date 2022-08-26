#define PROBLEM \
  "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_2_B"

#include "../../geometry/is_intersect_ss.hpp"
#include "../../template/template.hpp"

using namespace geometry;

int main() {
  int T;
  cin >> T;
  while (T--) {
    Segment a, b;
    cin >> a >> b;
    cout << is_intersect_ss(a, b) << "\n";
  }
}
