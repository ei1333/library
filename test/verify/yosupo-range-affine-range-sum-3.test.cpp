// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/range_affine_range_sum

#include "../../template/template.hpp"

#include "../../math/combinatorics/mod-int.hpp"

#include "../../other/vector-pool.hpp"

#include "../../structure/bbst/lazy-weight-balanced-tree.hpp"

using mint = ModInt< 998244353 >;

int main() {
  int N, Q;
  cin >> N >> Q;
  using pi = pair< mint, int >;
  using qi = pair< mint, mint >;
  auto f = [](const pi &a, const pi &b) -> pi {
    return {a.first + b.first, a.second + b.second};
  };
  auto g = [](const pi &a, const qi &b) -> pi {
    return {a.first * b.first + mint(a.second) * b.second, a.second};
  };
  auto h = [](const qi &a, const qi &b) -> qi {
    return {a.first * b.first, a.second * b.first + b.second};
  };
  LazyWeightBalancedTree< pi, qi, decltype(f), decltype(g), decltype(h) > rbt(2 * N, f, g, h, pi(0, 0), pi(1, 0));
  vector< pi > A(N);
  for(int i = 0; i < N; i++) {
    mint a;
    cin >> a;
    A[i] = {a, 1};
  }
  auto root = rbt.build(A);
  for(int i = 0; i < Q; i++) {
    int t;
    cin >> t;
    if(t == 0) {
      int l, r;
      mint b, c;
      cin >> l >> r >> b >> c;
      rbt.set_propagate(root, l, r, qi(b, c));
    } else {
      int l, r;
      cin >> l >> r;
      cout << rbt.query(root, l, r).first << "\n";
    }
  }
}
