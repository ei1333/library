// competitive-verifier: PROBLEM http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_A

#include "../../template/template.hpp"

#include "../../structure/segment-tree/segment-tree.hpp"

int main() {
  int N, Q;
  scanf("%d %d", &N, &Q);
  auto seg = get_segment_tree(N, [](int a, int b) { return min(a, b); }, INT_MAX);
  while(Q--) {
    int T, X, Y;
    scanf("%d %d %d", &T, &X, &Y);
    if(T == 0) seg.set(X, Y);
    else printf("%d\n", seg.prod(X, Y + 1));
  }
}
