// competitive-verifier: PROBLEM https://yukicoder.me/problems/no/1602

#include "../../template/template.hpp"

#include "../../graph/shortest-path/shortest-nonzero-path.hpp"

int main() {
  int N, M, K;
  cin >> N >> M >> K;
  auto f = [](int a, int b) { return a ^ b; };
  auto g = get_shortest_nonzero_path< int64, int >(N, f);
  for(int i = 0; i < M; i++) {
    int a, b, c;
    string x;
    cin >> a >> b >> c >> x;
    --a, --b;
    int d = 0;
    for(int j = 0; j < K; j++) {
      if(x[j] == '1') d |= 1 << j;
    }
    g.add_undirected_edge(a, b, c, d);
  }
  auto ret = g.build(N - 1);
  for(int i = 0; i + 1 < N; i++) {
    if(ret[i] >= infll) cout << -1 << "\n";
    else cout << ret[i] << "\n";
  }
}
