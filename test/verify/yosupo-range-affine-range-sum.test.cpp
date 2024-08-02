// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/range_affine_range_sum

#include "../../template/template.hpp"

#include "../../math/combinatorics/montgomery-mod-int.hpp"

#include "../../structure/segment-tree/lazy-segment-tree.hpp"

using mint = modint998244353;

int main() {
  int N, Q;
  cin >> N >> Q;
  using pi = pair< mint, int >;
  using qi = pair< mint, mint >;
  auto f = [](const pi &a, const pi &b) -> pi {
    return {a.first + b.first, a.second + b.second};
  };
  auto e = []() -> pi { return {0, 0}; };
  auto g = [](const pi &a, const qi &b) -> pi {
    return {a.first * b.first + mint(a.second) * b.second, a.second};
  };
  auto h = [](const qi &a, const qi &b) -> qi {
    return {a.first * b.first, a.second * b.first + b.second};
  };
  auto id = []() -> qi { return {1, 0}; };
  vector< pi > vs(N);
  for(int i = 0; i < N; i++) {
    mint a;
    cin >> a;
    vs[i] = {a, 1};
  }
  LazySegmentTree seg(LambdaActedMonoid(f, e, g, h, id), vs);
  for(int i = 0; i < Q; i++) {
    int t;
    cin >> t;
    if(t == 0) {
      int l, r;
      mint b, c;
      cin >> l >> r >> b >> c;
      seg.apply(l, r, qi(b, c));
    } else {
      int l, r;
      cin >> l >> r;
      cout << seg.prod(l, r).first << "\n";
    }
  }
}
