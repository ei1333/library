// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/staticrmq

#include "../../template/template.hpp"

#include "../../structure/others/sparse-table.hpp"

int main() {
  int N, Q;
  cin >> N >> Q;
  vector< int > A(N);
  cin >> A;
  auto st = get_sparse_table(A, [](int a, int b) { return min(a, b); });
  while(Q--) {
    int l, r;
    cin >> l >> r;
    cout << st.fold(l, r) << "\n";
  }
}
