#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_2_A"
#define ERROR 0.00000001

#include "../../template/template.cpp"

#include "../../geometry/projection.cpp"

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
