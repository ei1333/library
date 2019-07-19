using int64 = long long;
 
int64 add(int64 x, int64 y) { return x + y; }
 
int64 mul(int64 x, int y) { return x * y; }
 
int main() {
  int N, Q;
  scanf("%d %d", &N, &Q);
  vector< int64 > x(N);
  for(int i = 0; i < N; i++) {
    scanf("%lld", &x[i]);
  }
  const int LIM = 10000000;
  PersistentRedBlackTree< int64, int64, add, add, add, mul > beet(LIM, 0, 0);
  auto root = beet.build(x);
  int a, b, c, d;
 
  while(Q--) {
    scanf("%d", &a);
    if(a == 1) {
      scanf("%d %d %d", &a, &b, &c);
      beet.set_propagate(root, --a, b, c);
    } else if(a == 2) {
      scanf("%d %d %d %d", &a, &b, &c, &d);
      auto S = beet.split(root, b);
      auto T = beet.split(S.first, --a);
      auto U = beet.split(root, d);
      auto V = beet.split(U.first, --c);
      root = beet.merge(T.first, beet.merge(V.second, S.second));
    } else {
      scanf("%d %d", &a, &b);
      auto S = beet.split(root, b);
      auto T = beet.split(S.first, --a);
      printf("%lld\n", beet.sum(T.second));
    }
    if(beet.pool.ptr < 1000) root = beet.rebuild(root);
  }
}
