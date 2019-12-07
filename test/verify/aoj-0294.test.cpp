#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=0294"

#include "../../template/template.cpp"
#include "../../graph/template.cpp"

#include "../../graph/others/dominator-tree.cpp"

int main() {
  int N, M, Q;
  cin >> N >> M;
  UnWeightedGraph g(N);
  for(int i = 0; i < M; i++) {
    int a, b;
    cin >> a >> b;
    --a, --b;
    g[a].emplace_back(b);
  }
  DominatorTree< UnWeightedGraph > dom(g);
  dom.build(0);
  cin >> Q;
  while(Q--) {
    int a;
    cin >> a;
    --a;
    if(dom[a] == 0) cout << a + 1 << endl;
    else cout << dom[a] + 1 << endl;
  }
}
