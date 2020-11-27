#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_2_D"
#define ERROR 0.00000001

#include "../../template/template.cpp"

#include "../../geometry/distance_ss.cpp"

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
