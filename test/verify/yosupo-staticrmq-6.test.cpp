#define PROBLEM "https://judge.yosupo.jp/problem/staticrmq"

#include "../../template/template.cpp"

#include "../../other/offline-rmq.cpp"

#include "../../other/scanner.cpp"
#include "../../other/printer.cpp"


int main() {
  Scanner in(stdin);
  Printer out(stdout);
  int N, Q;
  in.read(N, Q);
  vector< int > A(N);
  in.read(A);
  vector< pair< int, int > > qs(Q);
  for(auto&[l, r]: qs) in.read(l, r);
  auto ans = offline_rmq(qs, [&](int a, int b) { return A[a] < A[b]; });
  for(int i = 0; i < Q; i++) out.writeln(A[ans[i]]);
}
