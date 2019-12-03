int main() {
  int N, M;
  cin >> N >> M;
  Matrix< bool > g(N, vector< bool >(N));
  for(int i = 0; i < M; i++) {
    int x, y;
    cin >> x >> y;
    --x, --y;
    g[x][y] = true;
    g[y][x] = true;
  }
  function< int(vector< int >) > f = [](vector< int > t) { return t.size(); };
  cout << maximum_clique(g, f) << endl;
}
