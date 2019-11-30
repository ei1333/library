#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=NTL_1_E"

#include "../../template/template.cpp"

#include "../../math/number-theory/extgcd.cpp"

int main() {
  int a, b, x, y;
  cin >> a >> b;
  extgcd(a, b, x, y);
  cout << x << " " << y << endl;
}
