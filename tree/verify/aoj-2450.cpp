using int64 = long long;
const int64 INF = 1LL << 55;
 
struct State {
  int64 ans, all, left, right;
 
  State() : ans(-INF), all(0), left(-INF), right(-INF) {}
 
  State(int64 val, int length) {
    all = val * length;
    ans = left = right = (val > 0 ? all : val);
  }
 
  State operator+(const State &s) const {
    State ret;
    ret.ans = max({ans, s.ans, right + s.left});
    ret.all = all + s.all;
    ret.left = max(left, all + s.left);
    ret.right = max(s.right, right + s.all);
    return (ret);
  }
};
 
 
struct SegmentTree {
  vector< State > seg;
  vector< int64 > lazy;
  int sz;
 
  SegmentTree(int n) {
    sz = 1;
    while(sz < n) sz <<= 1;
    seg.assign(2 * sz - 1, State());
    lazy.assign(2 * sz - 1, INF);
  }
 
  void push(int k, int l, int r) {
    if(lazy[k] == INF) return;
    seg[k] = State(lazy[k], r - l);
    if(k < sz - 1) {
      lazy[2 * k + 1] = lazy[k];
      lazy[2 * k + 2] = lazy[k];
    }
    lazy[k] = INF;
  }
 
  void update(int a, int b, int x, int k, int l, int r) {
    push(k, l, r);
    if(a >= r || b <= l) {
      return;
    }
    if(a <= l && r <= b) {
      lazy[k] = x;
      push(k, l, r);
      return;
    }
    update(a, b, x, 2 * k + 1, l, (l + r) >> 1);
    update(a, b, x, 2 * k + 2, (l + r) >> 1, r);
    seg[k] = seg[2 * k + 1] + seg[2 * k + 2];
  }
 
  State query(int a, int b, int k, int l, int r) {
    push(k, l, r);
    if(a >= r || b <= l) return (State());
    if(a <= l && r <= b) return (seg[k]);
    return (query(a, b, 2 * k + 1, l, (l + r) >> 1) +
            query(a, b, 2 * k + 2, (l + r) >> 1, r));
  }
 
  void update(int a, int b, int x) {
    update(a, b, x, 0, 0, sz);
  }
 
  State query(int a, int b) {
    return (query(a, b, 0, 0, sz));
  }
 
  void set(int k, int v) {
    seg[k + sz - 1] = State(v, 1);
  }
 
  void build() {
    for(int k = sz - 2; k >= 0; k--) {
      seg[k] = seg[2 * k + 1] + seg[2 * k + 2];
    }
  }
};
 
 
int main() {
  int N, Q, S[200000];
  scanf("%d %d", &N, &Q);
  for(int i = 0; i < N; i++) {
    scanf("%d", &S[i]);
  }
  UnWeightedGraph g(N);
  HeavyLightDecomposition< UnWeightedGraph > tree(g);
  for(int i = 0; i < N - 1; i++) {
    int u, v;
    scanf("%d %d", &u, &v);
    --u, --v;
    g[u].emplace_back(v);
    g[v].emplace_back(u);
  }
  tree.build();
  SegmentTree seg(N);
  for(int i = 0; i < N; i++) seg.set(i, S[tree.rev[i]]);
  seg.build();
  while(Q--) {
    int T, A, B, C;
    scanf("%d %d %d %d", &T, &A, &B, &C);
    --A, --B;
    if(T == 1) {
      tree.add(A, B, [&](int a, int b) { seg.update(a, b, C); });
    } else {
      /* l と r をマージせずに返すように実装を変更している */
      auto beet = tree.query(A, B, State(), [&](int a, int b) { return seg.query(a, b); }, [](const State &a, const State &b) { return a + b; });
      swap(beet.first.left, beet.first.right);
      printf("%lld\n", (beet.first + beet.second).ans);
    }
  }
}
