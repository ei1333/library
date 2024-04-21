// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/k_shortest_walk

#include "../../template/template.hpp"

#include "../../graph/graph-template.hpp"
#include "../../graph/shortest-path/dijkstra.hpp"

#include "../../structure/heap/leftist-heap.hpp"
#include "../../structure/heap/persistent-leftist-heap.hpp"
#include "../../graph/shortest-path/k-shortest-walk.hpp"

int main() {
  int N, M, S, T, K;
  cin >> N >> M >> S >> T >> K;
  Graph< int64 > g(N);
  g.read(M, 0, true, true);
  auto ret = k_shortest_walk(g, S, T, K);
  for(int i = 0; i < K; i++) {
    if(i >= (int)ret.size()) cout << -1 << "\n";
    else cout << ret[i] << "\n";
  }
}
