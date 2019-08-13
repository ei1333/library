#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_2_A"

#include "../../template/template.cpp"
#include "../template.cpp"

#include "../../structure/union-find.cpp"

#include "../kruskal.cpp"

int main() {
  int V, E;
  scanf("%d %d", &V, &E);
  Edges< int > edges;
  for(int i = 0; i < E; i++) {
    int a, b, c;
    scanf("%d %d %d", &a, &b, &c);
    edges.emplace_back(a, b, c);
  }
  printf("%d\n", kruskal(edges, V));
}
