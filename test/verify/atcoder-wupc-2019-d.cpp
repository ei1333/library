int main() {
  int N, M;
  vector< int > g[100000];
  cin >> N >> M;
  for(int i = 0; i < M; i++) {
    int a, b;
    cin >> a >> b;
    --a, --b;
    g[b].emplace_back(a);
  }
  for(int i = 0; i < N; i++) {
    g[i].emplace_back(i);
  }
  int in[100000] = {};
  int ok = 0;
  SqrtDecomposition< int > tap(N, 1);
  for(int i = 0; i < N; i++) tap.set(i, 1);
  int ptr = 0, ret = inf, l;
  for(int i = 0; i < N; i++) {
    while(ptr < N && tap.query_low(0, N) < N) {
      tap.add(0, N);
      for(auto &to : g[ptr]) tap.sub(to, to + 1);
      ++ptr;
    }
    if(tap.query_low(0, N) == N) {
      if(ptr - i < ret) {
        ret = ptr - i;
        l = i;
      }
    }
    tap.sub(0, N);
    for(auto &to : g[i]) tap.add(to, to + 1);
  }
  if(ret == inf) cout << -1 << endl;
  else cout << l + 1 << " " << l + 1 + ret - 1 << endl;
}
