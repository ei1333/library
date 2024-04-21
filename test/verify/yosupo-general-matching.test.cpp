// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/general_matching

#include "../../template/template.hpp"

#include "../../graph/flow/gabow-edmonds.hpp"

int main() {
  int N, M;
  cin >> N >> M;
  GabowEdmonds flow(N);
  for(int i = 0; i < M; i++) {
    int a, b;
    cin >> a >> b;
    flow.add_edge(a, b);
  }
  auto ret = flow.max_matching();
  cout << ret.size() << endl;
  for(auto &p : ret) cout << p << endl;
}
