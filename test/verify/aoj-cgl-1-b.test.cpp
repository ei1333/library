#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_1_B"
#define ERROR 0.00000001

#include "../../template/template.cpp"

#include "../../geometry/reflection.cpp"

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
