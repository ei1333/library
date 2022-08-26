#define PROBLEM \
  "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_5_C"

#include "../../graph/tree/doubling-lowest-common-ancestor.hpp"
#include "../../template/template.hpp"

int main() {
  int N, Q;
  cin >> N;
  DoublingLowestCommonAncestor< int > dlca(N);
  for (int i = 0; i < N; i++) {
    int k;
    cin >> k;
    for (int j = 0; j < k; j++) {
      int c;
      cin >> c;
      dlca.add_edge(i, c);
    }
  }
  dlca.build();
  cin >> Q;
  for (int i = 0; i < Q; i++) {
    int u, v;
    cin >> u >> v;
    cout << dlca.lca(u, v) << "\n";
  }
}
