// competitive-verifier: PROBLEM http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_2_D
// competitive-verifier: ERROR 0.00000001

#include "../../template/template.hpp"

#include "../../geometry/distance_ss.hpp"

using namespace geometry;

int main() {
  int T;
  cin >> T;
  while(T--) {
    Segment a, b;
    cin >> a >> b;
    cout << distance_ss(a, b) << "\n";
  }
}
