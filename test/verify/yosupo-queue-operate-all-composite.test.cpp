// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/queue_operate_all_composite

#include "../../template/template.hpp"

#include "../../math/combinatorics/montgomery-mod-int.hpp"

#include "../../structure/others/queue-operate-aggregation.hpp"
#include "../../structure/class/affine.hpp"

using mint = modint998244353;

int main() {
  int Q;
  cin >> Q;
  using pi = Affine< mint >;
  auto f = [](const pi &a, const pi &b) -> pi {
    return pi::op(a, b);
  };
  auto que = get_queue_operate_aggregation<pi>(f);
  while (Q--) {
    int t;
    cin >> t;
    if (t == 0) {
      mint a, b;
      cin >> a >> b;
      que.push(pi(a, b));
    } else if(t == 1) {
      que.pop();
    } else {
      mint x;
      cin >> x;
      if (que.empty()) {
        cout << x << "\n";
      } else {
        auto s = que.all_prod();
        cout << s.eval(x) << "\n";
      }
    }
  }
}
