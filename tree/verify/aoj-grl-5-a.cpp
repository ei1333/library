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
