int main() {
  int N, M;
  cin >> N >> M;
  Matrix< bool > g(N, vector< bool >(N));
  Matrix< int > h(N, vector< int >(N));
  for(int i = 0; i < M; i++) {
    int x, y, z;
    cin >> x >> y >> z;
    --x, --y;
    g[x][y] = true;
    g[y][x] = true;
    h[x][y] = z;
    h[y][x] = z;
  }
  function< int(vector< int >) > f = [&](vector< int > t) {
    if(t.size() <= 1) return 0;
    int ret = 0;
    for(int i = 0; i < t.size(); i++) {
      int uku = 1 << 30;
      for(int j = 0; j < t.size(); j++) if(i != j) uku = min(uku, h[t[i]][t[j]]);
      ret += uku;
    }
    return ret;
  };
  cout << maximum_clique(g, f) << endl;
}
