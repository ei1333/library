template< typename G >
struct DoublingLowestCommonAncestor {
  const int LOG;
  vector< int > dep;
  const G &g;
  vector< vector< int > > table;
 
  DoublingLowestCommonAncestor(const G &g) : g(g), dep(g.size()), LOG(32 - __builtin_clz(g.size())) {
    table.assign(LOG, vector< int >(g.size(), -1));
  }
 
  void dfs(int idx, int par, int d) {
    table[0][idx] = par;
    dep[idx] = d;
    for(auto &to : g[idx]) {
      if(to != par) dfs(to, idx, d + 1);
    }
  }
 
  void build() {
    dfs(0, -1, 0);
    for(int k = 0; k + 1 < LOG; k++) {
      for(int i = 0; i < table[k].size(); i++) {
        if(table[k][i] == -1) table[k + 1][i] = -1;
        else table[k + 1][i] = table[k][table[k][i]];
      }
    }
  }
 
  int query(int u, int v) {
    if(dep[u] > dep[v]) swap(u, v);
    for(int i = LOG - 1; i >= 0; i--) {
      if(((dep[v] - dep[u]) >> i) & 1) v = table[i][v];
    }
    if(u == v) return u;
    for(int i = LOG - 1; i >= 0; i--) {
      if(table[i][u] != table[i][v]) {
        u = table[i][u];
        v = table[i][v];
      }
    }
    return table[0][u];
  }
};
 
int main() {
  int N, M;
  scanf("%d %d", &N, &M);
  UnWeightedGraph g(N);
  for(int i = 0; i < M; i++) {
    int x, y;
    scanf("%d %d", &x, &y);
    --x, --y;
    g[x].emplace_back(y);
    g[y].emplace_back(x);
  }
  TwoEdgeConnectedComponents< UnWeightedGraph > bcc(g);
  UnWeightedGraph t;
  bcc.build(t);
  DoublingLowestCommonAncestor< UnWeightedGraph > lca(t);
  lca.build();
  int Q;
  scanf("%d", &Q);
  auto getdist = [&](int x, int y) {
    return lca.dep[x] + lca.dep[y] - 2 * lca.dep[lca.query(x, y)];
  };
  while(Q--) {
    int a, b, c;
    scanf("%d %d %d", &a, &b, &c);
    a = bcc[--a], b = bcc[--b], c = bcc[--c];
    if(getdist(a, c) == getdist(a, b) + getdist(b, c)) puts("OK");
    else puts("NG");
  }
}
