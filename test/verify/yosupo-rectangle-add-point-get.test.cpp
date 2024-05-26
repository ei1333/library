// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/rectangle_add_point_get

#include "../../template/template.hpp"

#include "../../other/dynamic-rectangle-add-point-get.hpp"

int main() {
  int N, Q;
  cin >> N >> Q;
  DynamicRectangleAddPointGet< int, int64 > sum(N + Q);
  for(int i = 0; i < N; i++) {
    int l, d, r, u, w;
    cin >> l >> d >> r >> u >> w;
    sum.add_rectangle(l, d, r, u, w);
  }
  for(int i = 0; i < Q; i++) {
    int t;
    cin >> t;
    if(t == 0) {
      int l, d, r, u, w;
      cin >> l >> d >> r >> u >> w;
      sum.add_rectangle(l, d, r, u, w);
    } else {
      int x, y;
      cin >> x >> y;
      sum.add_query(x, y);
    }
  }
  for(auto& ans : sum.calculate_queries()) {
    cout << ans << "\n";
  }
}
