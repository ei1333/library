#define PROBLEM \
  "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_2_C"
#define ERROR 0.00000001

#include "../../geometry/cross_point_ll.hpp"
#include "../../template/template.hpp"

using namespace geometry;

int main() {
  int T;
  cin >> T;
  while (T--) {
    Line a, b;
    cin >> a >> b;
    cout << cross_point_ll(a, b) << "\n";
  }
}
