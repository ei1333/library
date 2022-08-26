#define PROBLEM \
  "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=NTL_1_E"

#include "../../math/number-theory/extgcd.hpp"
#include "../../template/template.hpp"

int main() {
  int a, b, x, y;
  cin >> a >> b;
  extgcd(a, b, x, y);
  cout << x << " " << y << endl;
}
