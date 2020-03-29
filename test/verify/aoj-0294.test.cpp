#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=0294"

#include "../../template/template.cpp"
#include "../../graph/template.cpp"

#include "../../graph/others/dominator-tree.cpp"

int main() {
  int N, M, Q;
  cin >> N >> M;
  DominatorTree<> g(N);
  g.read(M, -1, false, true);
  g.build(0);
  cin >> Q;
  while(Q--) {
    int a;
    cin >> a;
    --a;
    if(g[a] == 0) cout << a + 1 << "\n";
    else cout << g[a] + 1 << "\n";
  }
}
