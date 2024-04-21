// competitive-verifier: PROBLEM http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_3_C

#include "../../template/template.hpp"

#include "../../geometry/contains.hpp"

using namespace geometry;

int main() {
  int N;
  cin >> N;
  Polygon p(N);
  for(int i = 0; i < N; i++) {
    cin >> p[i];
  }
  int Q;
  cin >> Q;
  while(Q--) {
    Point q;
    cin >> q;
    cout << contains(p, q) << "\n";
  }
}
