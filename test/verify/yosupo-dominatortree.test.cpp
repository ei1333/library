#define PROBLEM "https://judge.yosupo.jp/problem/dominatortree"

#include "../../template/template.cpp"

#include "../../graph/graph-template.cpp"

#include "../../graph/others/dominator-tree.cpp"

int main() {
  int N, M, S;
  cin >> N >> M >> S;
  DominatorTree<> g(N);
  g.read(M, 0, false, true);
  g.build(S);
  for(int i = 0; i < N; i++) cout << g[i] << " ";
  cout << endl;
}

