// competitive-verifier: PROBLEM http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_1_C

#include "../../template/template.hpp"

#include "../../geometry/ccw.hpp"

using namespace geometry;

int main() {
  Point p1, p2;
  cin >> p1 >> p2;
  int Q;
  cin >> Q;
  while(Q--) {
    Point p3;
    cin >> p3;
    auto t = ccw(p1, p2, p3);
    if(t == 1) cout << "COUNTER_CLOCKWISE\n";
    else if(t == -1) cout << "CLOCKWISE\n";
    else if(t == 2) cout << "ONLINE_BACK\n";
    else if(t == -2) cout << "ONLINE_FRONT\n";
    else cout << "ON_SEGMENT\n";
  }
}
