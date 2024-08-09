// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/point_add_rectangle_sum

#include "../../template/template.hpp"

#include "../../structure/segment-tree/range-tree.hpp"
#include "../../structure/class/point-add-rectangle-sum.hpp"

int main() {
  int N, Q;
  cin >> N >> Q;
  vector<int> X(N), Y(N), W(N), c(Q), s(Q), t(Q), u(Q), v(Q);
  using monoid = PointAddRectangleSum< int64 >;
  RangeTree< int, monoid > seg{monoid()};
  for(int i = 0; i < N; i++) {
    cin >> X[i] >> Y[i] >> W[i];
    seg.add_point(X[i], Y[i]);
  }
  for(int i = 0; i < Q; i++) {
    cin >> c[i] >> s[i] >> t[i] >> u[i];
    if (c[i]) cin >> v[i];
    else seg.add_point(s[i], t[i]);
  }
  seg.build();
  for(int i = 0; i < N; i++) {
    seg.apply(X[i], Y[i], W[i]);
  }
  for(int i = 0; i < Q; i++) {
    if (c[i]) cout << seg.prod(s[i], t[i], u[i], v[i]) << "\n";
    else seg.apply(s[i], t[i], u[i]);
  }
}
