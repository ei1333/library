#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_3_B"

#include "../../template/template.cpp"

#include "../../geometry/is_convex_polygon.cpp"

using namespace geometry;

int main() {
  int N;
  cin >> N;
  Polygon p(N);
  for(auto &s : p) cin >> s;
  cout << is_convex_polygon(p) << endl;
}
