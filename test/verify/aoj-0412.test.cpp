// competitive-verifier: PROBLEM http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=0412

#include "../../template/template.hpp"

#include "../../geometry/convex_polygon_contains.hpp"

using namespace geometry;

int main() {
  int N, Q;
  cin >> N;
  Polygon g(N);
  for(int i = 0; i < N; i++) {
    double x, y;
    cin >> x >> y;
    g[i] = Point(x, y);
  }
  cin >> Q;
  while(Q--) {
    double x, y;
    cin >> x >> y;
    Point p(x - x / 10000, y - y / 10000);
    if(convex_polygon_contains(g, p)) cout << 1 << "\n";
    else cout << 0 << "\n";
  }
}
