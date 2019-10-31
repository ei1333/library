int main() {
  int T;
  cin >> T;
  while(T--) {
    int N;
    cin >> N;
    UnWeightedGraph x(N), y(N);
    for(int i = 1; i < N; i++) {
      int a, b;
      cin >> a >> b;
      --a, --b;
      x[a].emplace_back(b);
      x[b].emplace_back(a);
    }
    for(int i = 1; i < N; i++) {
      int a, b;
      cin >> a >> b;
      --a, --b;
      y[a].emplace_back(b);
      y[b].emplace_back(a);
    }
    if(tree_isomorphism(x, y)) cout << "YES\n";
    else cout << "NO\n";
  }
}
