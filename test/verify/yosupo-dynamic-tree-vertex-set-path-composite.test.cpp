// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/dynamic_tree_vertex_set_path_composite

#include "../../template/template.hpp"

#include "../../structure/lct/link-cut-tree.hpp"

#include "../../math/combinatorics/mod-int.hpp"

using mint = ModInt< 998244353 >;

int main() {
  int N, Q;
  cin >> N >> Q;

  using pi = pair< mint, mint >;
  using pii = pair< pi, pi >;
  auto f = [](const pi &x, const pi &y) { return pi(x.first * y.first, x.second * y.first + y.second); };
  auto ff = [&](const pii &a, const pii &b) { return pii(f(a.first, b.first), f(b.second, a.second)); };
  auto flip = [&](const pii &a) { return pii(a.second, a.first); };
  auto lct = get_link_cut_tree< pii >(ff, flip);

  vector< decltype(lct)::NP > vs(N);
  for(int i = 0; i < N; i++) {
    mint x, y;
    cin >> x >> y;
    vs[i] = lct.alloc(pii(pi(x, y), pi(x, y)));
  }
  for(int i = 1; i < N; i++) {
    int a, b;
    cin >> a >> b;
    lct.evert(vs[a]);
    lct.link(vs[a], vs[b]);
  }

  while(Q--) {
    int T;
    cin >> T;
    if(T == 0) {
      int U, V, W, X;
      cin >> U >> V >> W >> X;
      lct.evert(vs[U]);
      lct.cut(vs[V]);
      lct.evert(vs[W]);
      lct.link(vs[W], vs[X]);
    } else if(T == 1) {
      int P;
      mint a, b;
      cin >> P >> a >> b;
      lct.set_key(vs[P], pii(pi(a, b), pi(a, b)));
    } else {
      int U, V;
      mint X;
      cin >> U >> V >> X;
      auto ret = lct.query(vs[U], vs[V]).first;
      cout << ret.first * X + ret.second << "\n";
    }
  }
}
