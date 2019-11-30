#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_1_A"

#include "../../template/template.cpp"
#include "../../graph/template.cpp"

#include "../../structure/heap/fibonacchi-heap.cpp"

#include "../../graph/shortest-path/dijkstra-fibonacchi-heap.cpp"

int main() {
  int V, E, R;
  scanf("%d %d %d", &V, &E, &R);
  WeightedGraph< int > g(V);
  for(int i = 0; i < E; i++) {
    int a, b, c;
    scanf("%d %d %d", &a, &b, &c);
    g[a].emplace_back(b, c);
  }
  for(auto &dist : dijkstra_fibonacchi_heap(g, R)) {
    if(dist == numeric_limits< int >::max()) puts("INF");
    else printf("%d\n", dist);
  }
}
