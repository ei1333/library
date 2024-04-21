// competitive-verifier: PROBLEM http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_4_A

#include "../../template/template.hpp"

#include "../../geometry/convex_hull.hpp"

using namespace geometry;

int main() {
  int N;
  cin >> N;
  Polygon p(N);
  for(auto &s : p) cin >> s;
  p = convex_hull(p, false);
  N = (int) p.size();
  cout << N << "\n";
  int idx = 0;
  for(int i = 1; i < N; i++) {
    if(compare_y(p[i], p[idx])) {
      idx = i;
    }
  }
  for(int i = 0; i < N; i++) {
    cout << fixed << setprecision(0) << p[(idx + i) % N] << "\n";
  }
}
