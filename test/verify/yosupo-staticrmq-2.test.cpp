// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/staticrmq

#include "../../template/template.hpp"

#include "../../structure/others/disjoint-sparse-table.hpp"

int main() {
  int N, Q;
  cin >> N >> Q;
  vector< int > A(N);
  cin >> A;
  auto f = [](int a, int b) { return min(a, b); };
  auto st = get_disjoint_sparse_table(A, f);
  while(Q--) {
    int l, r;
    cin >> l >> r;
    cout << st.fold(l, r) << "\n";
  }
}
