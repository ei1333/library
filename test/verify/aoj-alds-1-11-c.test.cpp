// competitive-verifier: PROBLEM http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ALDS1_11_C

#include "../../template/template.hpp"

#include "../../graph/shortest-path/bfs.hpp"


int main() {
  int N;
  cin >> N;
  Graph<> g(N);
  for(int i = 0; i < N; i++) {
    int U, K;
    cin >> U >> K;
    --U;
    for(int j = 0; j < K; j++) {
      int x;
      cin >> x;
      --x;
      g.add_directed_edge(U, x);
    }
  }
  auto d = bfs(g, 0);
  for(int i = 0; i < N; i++) {
    cout << i + 1 << " ";
    if(d[i] == numeric_limits< int >::max()) cout << -1 << "\n";
    else cout << d[i] << "\n";
  }
}

