#define PROBLEM \
  "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_1_A"
#define ERROR 0.00000001

#include "../../geometry/projection.hpp"
#include "../../template/template.hpp"

using namespace geometry;

int main() {
  Line l;
  cin >> l;
  int Q;
  cin >> Q;
  while (Q--) {
    Point p;
    cin >> p;
    cout << projection(l, p) << "\n";
  }
}
