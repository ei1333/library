#define PROBLEM \
  "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=0233"

#include "../../math/number-theory/convert-base.hpp"
#include "../../template/template.hpp"

int main() {
  for (;;) {
    int X;
    cin >> X;
    if (X == 0) break;
    auto ret = convert_base(X, -10);
    for (auto &p: ret) cout << p;
    cout << endl;
  }
}
