#define PROBLEM \
  "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_1_A"

#include "../../structure/union-find/union-find.hpp"
#include "../../template/template.hpp"

int main() {
  int N, Q;
  scanf("%d %d", &N, &Q);
  UnionFind uf(N);
  while (Q--) {
    int t, x, y;
    scanf("%d %d %d", &t, &x, &y);
    if (t == 0)
      uf.unite(x, y);
    else
      printf("%d\n", uf.find(x) == uf.find(y));
  }
}
