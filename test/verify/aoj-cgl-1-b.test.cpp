// competitive-verifier: PROBLEM http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_1_B
// competitive-verifier: ERROR 0.00000001

#include "../../template/template.hpp"

#include "../../geometry/reflection.hpp"

using namespace geometry;

int main() {
  Line l;
  cin >> l;
  int Q;
  cin >> Q;
  while(Q--) {
    Point p;
    cin >> p;
    cout << reflection(l, p) << "\n";
  }
}
