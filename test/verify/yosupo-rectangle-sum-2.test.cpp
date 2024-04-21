// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/rectangle_sum

#include "../../template/template.hpp"

#include "../../other/static-point-add-rectangle-sum.hpp"

#include "../../other/scanner.hpp"
#include "../../other/printer.hpp"

int main() {
  int N, Q;
  Scanner in(stdin);
  Printer out(stdout);
  in.read(N, Q);
  StaticPointAddRectangleSum< int, int64 > spars;
  for(int i = 0; i < N; i++) {
    int x, y, z;
    in.read(x, y, z);
    spars.add_point(x, y, z);
  }
  vector< tuple< int, int, int, int > > query;
  query.reserve(Q);
  for(int i = 0; i < Q; i++) {
    int l, d, r, u;
    in.read(l, d, r, u);
    spars.add_query(l, d, r, u);
  }
  for(auto &&ans: spars.calculate_queries()) {
    out.writeln(ans);
  }
}
