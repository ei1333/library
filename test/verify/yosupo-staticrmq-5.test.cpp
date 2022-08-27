#define PROBLEM "https://judge.yosupo.jp/problem/staticrmq"

#include "../../other/printer.hpp"
#include "../../other/scanner.hpp"
#include "../../structure/others/linear-rmq.hpp"
#include "../../template/template.hpp"

int main() {
  Scanner in(stdin);
  Printer out(stdout);
  int N, Q;
  in.read(N, Q);
  vector< int > A(N);
  in.read(A);
  auto f   = [&](int a, int b) { return A[a] < A[b]; };
  auto seg = get_linear_rmq(N, f);
  while (Q--) {
    int l, r;
    in.read(l, r);
    out.writeln(A[seg.fold(l, r)]);
  }
}
