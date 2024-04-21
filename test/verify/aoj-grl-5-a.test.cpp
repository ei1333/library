// competitive-verifier: PROBLEM http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_5_A

#include "../../template/template.hpp"

#include "../../graph/tree/tree-diameter.hpp"

int main() {
  int N;
  cin >> N;
  TreeDiameter< int > g(N);
  g.read(N - 1, 0, true);
  cout << g.build() << endl;
}
