int main() {
  int V, E, R;
  scanf("%d %d %d", &V, &E, &R);
  Edges< int > edges;
  for(int i = 0; i < E; i++) {
    int a, b, c;
    scanf("%d %d %d", &a, &b, &c);
    edges.emplace_back(a, b, c);
  }
  printf("%d\n", MinimumSpanningTreeArborescence< int >(edges, V).build(R));
}
