#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_5_A"

#include "../../template/template.cpp"
#include "../../graph/template.cpp"

#include "../../graph/tree/tree-diameter.cpp"

int main() {
  int N;
  scanf("%d", &N);
  WeightedGraph< int > g(N);
  for(int i = 1; i < N; i++) {
    int x, y, z;
    scanf("%d %d %d", &x, &y, &z);
    g[x].emplace_back(y, z);
    g[y].emplace_back(x, z);
  }
  printf("%d\n", tree_diameter(g));
}
