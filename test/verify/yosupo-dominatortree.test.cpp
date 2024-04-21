// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/dominatortree

#include "../../template/template.hpp"

#include "../../graph/others/dominator-tree.hpp"

int main() {
  int N, M, S;
  cin >> N >> M >> S;
  DominatorTree<> g(N);
  g.read(M, 0, false, true);
  g.build(S);
  for(int i = 0; i < N; i++) cout << g[i] << " ";
  cout << endl;
}

