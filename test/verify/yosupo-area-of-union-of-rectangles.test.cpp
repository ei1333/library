// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/area_of_union_of_rectangles

#include "../../template/template.hpp"

#include "../../other/area-of-union-of-rectangles.hpp"

#include "../../other/scanner.hpp"

int main() {
  Scanner in(stdin);
  int n;
  in.read(n);
  AreaOfUnionOfRectangles<int> sum(n);
  for (int i = 0; i < n; i++) {
    int l, d, r, u;
    in.read(l, d, r, u);
    sum.add_rectangle(l, d, r, u);
  }
  cout << sum.calc<int64>() << endl;
}
