// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/point_add_rectangle_sum

#include "../../template/template.hpp"

#include "../../structure/others/abstract-2d-binary-indexed-tree-compressed.hpp"

#include "../../other/scanner.hpp"
#include "../../other/printer.hpp"

int main() {
  Scanner in(stdin);
  Printer out(stdout);
  int N, Q;
  in.read(N, Q);
  vector< int > X(N), Y(N), W(N);
  vector< pair< int, int > > ps(N);
  for(int i = 0; i < N; i++) {
    in.read(X[i], Y[i], W[i]);
    ps[i] = {X[i], Y[i]};
  }
  vector< int > A(Q), B(Q), C(Q), D(Q), E(Q);
  for(int i = 0; i < Q; i++) {
    in.read(A[i], B[i], C[i], D[i]);
    if(A[i] == 0) ps.emplace_back(B[i], C[i]);
    else in.read(E[i]);
  }
  sort(begin(ps), end(ps));
  ps.erase(unique(begin(ps), end(ps)), end(ps));
  vector< int > H(ps.size());
  for(int i = 0; i < N; i++) {
    X[i] = lower_bound(begin(ps), end(ps), make_pair(X[i], Y[i])) - begin(ps);
  }
  for(int i = 0; i < Q; i++) {
    if(A[i] == 0) {
      B[i] = lower_bound(begin(ps), end(ps), make_pair(B[i], C[i])) - begin(ps);
    } else {
      B[i] = lower_bound(begin(ps), end(ps), make_pair(B[i], -inf)) - begin(ps);
      D[i] = lower_bound(begin(ps), end(ps), make_pair(D[i], -inf)) - begin(ps);
    }
  }
  for(int i = 0; i < (int) ps.size(); i++) {
    H[i] = ps[i].second;
  }
  auto f = [](int64 a, int64 b) { return a + b; };
  auto bit = get_abstract_2d_binary_indexed_tree_compressed(H, f, 0LL);
  for(int i = 0; i < N; i++) {
    bit.apply(X[i], W[i]);
  }
  for(int i = 0; i < Q; i++) {
    if(A[i] == 0) {
      bit.apply(B[i], D[i]);
    } else {
      out.writeln(bit.prod(D[i], E[i]) - bit.prod(D[i], C[i]) - bit.prod(B[i], E[i]) + bit.prod(B[i], C[i]));
    }
  }
}
