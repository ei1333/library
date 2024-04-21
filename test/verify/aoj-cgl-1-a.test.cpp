// competitive-verifier: PROBLEM http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_1_A
// competitive-verifier: ERROR 0.00000001

#include "../../template/template.hpp"

#include "../../geometry/projection.hpp"

using namespace geometry;

int main() {
  Line l;
  cin >> l;
  int Q;
  cin >> Q;
  while(Q--) {
    Point p;
    cin >> p;
    cout << projection(l, p) << "\n";
  }
}
