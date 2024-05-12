// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/static_rectangle_add_rectangle_sum

#include "../../template/template.hpp"

#include "../../other/static-rectangle-add-rectangle-sum.hpp"

#include "../../math/combinatorics/montgomery-mod-int.hpp"

using mint = modint998244353;

int main() {
  int N, Q;
  cin >> N >> Q;
  StaticRectangleAddRectangleSum< int, mint > mat;
  for(int i = 0; i < N; i++) {
    int l, d, r, u, w;
    cin >> l >> d >> r >> u >> w;
    mat.add_rectangle(l, d, r, u, w);
  }
  for(int i = 0; i < Q; i++) {
    int l, d, r, u;
    cin >> l >> d >> r >> u;
    mat.add_query(l, d, r, u);
  }
  for(auto& p : mat.calculate_queries()) {
    cout << p.val() << "\n";
  }
}
