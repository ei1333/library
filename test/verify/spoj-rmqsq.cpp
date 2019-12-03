int main() {
  int N, Q;
  scanf("%d", &N);
  vector< int > vs(N);
  for(int i = 0; i < N; i++) scanf("%d", &vs[i]);
  SparseTable< int > table(vs);
  scanf("%d", &Q);
  while(Q--) {
    int x, y;
    scanf("%d %d", &x, &y);
    printf("%d\n", table.rmq(x, y + 1));
  }
}
