#define PROBLEM "https://judge.yosupo.jp/problem/staticrmq"

#include "../../template/template.cpp"

#include "../../structure/others/linear-rmq.cpp"

#include "../../other/scanner.cpp"
#include "../../other/printer.cpp"

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
