int main() {
  int N, Q;
  scanf("%d", &N);
  UnWeightedGraph g(N);
  for(int i = 0; i < N; i++) {
    int k;
    scanf("%d", &k);
    while(k--) {
      int c;
      scanf("%d", &c);
      g[i].push_back(c);
    }
  }
  DoublingLowestCommonAncestor< UnWeightedGraph > lca(g);
  lca.build();
  scanf("%d", &Q);
  while(Q--) {
    int x, y;
    scanf("%d %d", &x, &y);
    printf("%d\n", lca.query(x, y));
  }
}
