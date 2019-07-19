int main() {
  int N, Q;
  scanf("%d %d", &N, &Q);
  BinaryIndexedTree< int > bit(N);
  while(Q--) {
    int T, X, Y;
    scanf("%d %d %d", &T, &X, &Y);
    if(T == 0) bit.add(X - 1, Y);
    else printf("%d\n", bit.sum(Y - 1) - bit.sum(X - 2));
  }
}
