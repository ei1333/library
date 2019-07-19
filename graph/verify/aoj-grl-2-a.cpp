int main() {
  int V, E;
  scanf("%d %d", &V, &E);
  WeightedGraph< int > g(V);
  for(int i = 0; i < E; i++) {
    int a, b, c;
    scanf("%d %d %d", &a, &b, &c);
    g[a].emplace_back(b, c);
    g[b].emplace_back(a, c);
  }
  printf("%d\n", prim(g));
}
