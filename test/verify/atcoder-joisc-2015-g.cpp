struct UnionFind {
  vector< int > data;
 
  UnionFind(int sz) {
    data.assign(sz, -1);
  }
 
  bool unite(int x, int y) {
    x = find(x), y = find(y);
    if(x == y) return (false);
    if(data[x] > data[y]) swap(x, y);
    data[x] += data[y];
    data[y] = x;
    return (true);
  }
 
  int find(int k) {
    if(data[k] < 0) return (k);
    return (data[k] = find(data[k]));
  }
 
  int size(int k) {
    return (-data[find(k)]);
  }
};
 
int main() {
  int N, Q;
  cin >> N >> Q;
  auto f = [](int a, int b) { return a + b; };
  auto g = [](int a, int b, int l) { return 0; };
  auto h = [](int a, int b) { return (a | b); };
  auto s = [](int a) { return a; };
  using LCT=LinkCutTree< int >;
  LCT lct(f, g, h, s, 0, 0);
  vector< LCT::Node * > nodev, nodee;
  for(int i = 0; i < N; i++) {
    nodev.emplace_back(lct.make_node(i, 0));
    nodee.emplace_back(lct.make_node(i, 1));
  }
  UnionFind uf(N);
  int cnt = 0;
  for(int i = 0; i < Q; i++) {
    int T, A, B;
    cin >> T >> A >> B;
    --A, --B;
    if(T == 1) {
      if(uf.find(A) != uf.find(B)) {
        lct.evert(nodev[B]);
        lct.link(nodee[cnt], nodev[A]);
        lct.link(nodev[B], nodee[cnt]);
        uf.unite(A, B);
        ++cnt;
      } else {
        lct.evert(nodev[A]);
        lct.expose(nodev[B]);
        lct.set_propagate(nodev[B], 1);
      }
    } else {
      if(uf.find(A) != uf.find(B)) {
        cout << -1 << "\n";
      } else {
        lct.evert(nodev[A]);
        lct.expose(nodev[B]);
        cout << nodev[B]->sum << "\n";
      }
    }
  }
}
