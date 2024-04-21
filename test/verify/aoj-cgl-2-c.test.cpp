// competitive-verifier: PROBLEM http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_2_C
// competitive-verifier: ERROR 0.00000001

#include "../../template/template.hpp"

#include "../../geometry/cross_point_ll.hpp"

using namespace geometry;

int main() {
  int T;
  cin >> T;
  while(T--) {
    Line a, b;
    cin >> a >> b;
    cout << cross_point_ll(a, b) << "\n";
  }
}
