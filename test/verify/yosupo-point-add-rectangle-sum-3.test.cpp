// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/point_add_rectangle_sum

#include "../../template/template.hpp"

#include "../../other/dynamic-point-add-rectangle-sum.hpp"

#include "../../other/scanner.hpp"
#include "../../other/printer.hpp"

int main() {
  int N, Q;
  Scanner in(stdin);
  Printer out(stdout);
  in.read(N, Q);
  DynamicPointAddRectangleSum< int, int64 > dpars(N + Q);
  for(int i = 0; i < N; i++) {
    int x, y, z;
    in.read(x, y, z);
    dpars.add_point(x, y, z);
  }
  for(int i = 0; i < Q; i++) {
    int t;
    in.read(t);
    if(t == 0) {
      int x, y, z;
      in.read(x, y, z);
      dpars.add_point(x, y, z);
    } else {
      int l, d, r, u;
      in.read(l, d, r, u);
      dpars.add_query(l, d, r, u);
    }
  }
  for(auto &&ans: dpars.calculate_queries()) {
    out.writeln(ans);
  }
}
