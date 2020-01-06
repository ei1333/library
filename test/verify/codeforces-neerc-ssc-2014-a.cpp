#define IGNORE

struct UnionFindUndo {
  vector< int > data;
  stack< pair< int, int > > history;

  UnionFindUndo(int sz) {
    data.assign(sz, -1);
  }

  bool unite(int x, int y) {
    x = find(x), y = find(y);
    history.emplace(x, data[x]);
    history.emplace(y, data[y]);
    if(x == y) return (false);
    if(data[x] > data[y]) swap(x, y);
    data[x] += data[y];
    data[y] = x;
    return (true);
  }

  int find(int k) {
    if(data[k] < 0) return (k);
    return (find(data[k]));
  }

  int size(int k) {
    return (-data[find(k)]);
  }

  void undo() {
    data[history.top().first] = history.top().second;
    history.pop();
    data[history.top().first] = history.top().second;
    history.pop();
  }

  void snapshot() {
    while(history.size()) history.pop();
  }

  void rollback() {
    while(history.size()) undo();
  }
};

int main() {
  int N, M, Q;
  cin >> N >> M >> Q;
  vector< int > X(M), Y(M);
  for(int i = 0; i < M; i++) {
    cin >> X[i] >> Y[i];
    --X[i], --Y[i];
  }
  MoRollBack mo(N, Q);
  for(int i = 0; i < Q; i++) {
    int l, r;
    cin >> l >> r;
    mo.add(--l, r);
  }

  UnionFindUndo uf(N + N);
  vector< int > ans(Q);
  int dame_sum = 0, dame_add = 0;
  vector< int > dame;
  auto add = [&](int idx) {
    uf.unite(X[idx], Y[idx] + N);
    uf.unite(X[idx] + N, Y[idx]);
    dame_add += uf.find(X[idx]) == uf.find(Y[idx]);
  };
  auto rem = [&](int idx) {
    ans[idx] = dame_sum + dame_add > 0;
  };
  auto reset = [&]() {
    uf = UnionFindUndo(N + N);
    dame_add = dame_sum = 0;
  };
  auto snapshot = [&]() {
    uf.snapshot();
    dame_sum += dame_add;
    dame_add = 0;
  };
  auto rollback = [&]() {
    uf.rollback();
    dame_add = 0;
  };
  mo.run(add, rem, reset, snapshot, rollback);
  for(auto &p : ans) {
    if(p) cout << "Impossible\n";
    else cout << "Possible\n";
  }
}
