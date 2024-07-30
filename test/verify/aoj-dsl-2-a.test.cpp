// competitive-verifier: PROBLEM http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_A

#include "../../template/template.hpp"

#include "../../structure/segment-tree/segment-tree.hpp"

int main() {
  int N, Q;
  cin >> N >> Q;
  auto seg = SegmentTree(
      LambdaMonoid([](int a, int b) { return min(a, b); },
                   []() { return INT_MAX; }), N);
  while (Q--) {
    int T, X, Y;
    cin >> T >> X >> Y;
    if (T == 0) seg.set(X, Y);
    else cout << seg.prod(X, Y + 1) << "\n";
  }
}
