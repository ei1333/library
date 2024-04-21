// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/staticrmq

#include "../../template/template.hpp"

#include "../../structure/others/linear-rmq.hpp"

#include "../../other/scanner.hpp"
#include "../../other/printer.hpp"

int main() {
  Scanner in(stdin);
  Printer out(stdout);
  int N, Q;
  in.read(N, Q);
  vector< int > A(N);
  in.read(A);
  auto f = [&](int a, int b) { return A[a] < A[b]; };
  auto seg = get_linear_rmq(N, f);
  while(Q--) {
    int l, r;
    in.read(l, r);
    out.writeln(A[seg.fold(l, r)]);
  }
}
