// competitive-verifier: PROBLEM http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=NTL_1_E

#include "../../template/template.hpp"

#include "../../math/number-theory/extgcd.hpp"

int main() {
  int a, b, x, y;
  cin >> a >> b;
  extgcd(a, b, x, y);
  cout << x << " " << y << endl;
}
