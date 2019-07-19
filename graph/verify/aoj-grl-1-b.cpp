int main() {
  int V, E, R;
  scanf("%d %d %d", &V, &E, &R);
  Edges< int > es;
  for(int i = 0; i < E; i++) {
    int a, b, c;
    scanf("%d %d %d", &a, &b, &c);
    es.emplace_back(a, b, c);
  }
  auto dists = bellman_ford(es, V, R);
  if(dists.empty()) puts("NEGATIVE CYCLE");
  for(auto &dist : dists) {
    if(dist == numeric_limits< int >::max()) puts("INF");
    else printf("%d\n", dist);
  }
}
