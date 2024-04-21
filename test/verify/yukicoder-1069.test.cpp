// competitive-verifier: ERROR 1e-4
// competitive-verifier: PROBLEM https://yukicoder.me/problems/no/1069

#include "../../template/template.hpp"

#include "../../graph/graph-template.hpp"
#include "../../graph/shortest-path/k-shortest-path.hpp"

int main() {
  int N, M, K;
  cin >> N >> M >> K;
  int X, Y;
  cin >> X >> Y;
  --X, --Y;
  vector< int > P(N), Q(N);
  for(int i = 0; i < N; i++) {
    cin >> P[i] >> Q[i];
  }
  Graph< double > g(N);
  vector< int > x(M * 2), y(M * 2);
  for(int i = 0; i < M; i++) {
    int a, b;
    cin >> a >> b;
    --a, --b;
    g.add_directed_edge(a, b, hypot(P[a] - P[b], Q[a] - Q[b]));
    x[i] = a, y[i] = b;
  }
  for(int i = 0; i < M; i++) {
    int a = x[i], b = y[i];
    x[i + M] = b, y[i + M] = a;
    g.add_directed_edge(b, a, hypot(P[a] - P[b], Q[a] - Q[b]));
  }
  auto ans = k_shortest_path(g, X, Y, K);
  for(int i = 0; i < K; i++) {
    if(i < ans.size()) cout << ans[i].first << "\n";
    else cout << -1 << "\n";
  }
}
