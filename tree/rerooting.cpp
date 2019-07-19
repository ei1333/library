template< typename Data, typename T >
struct ReRooting {
 
  struct Node {
    int to, rev;
    Data data;
  };
 
  using F1 = function< T(T, T) >;
  using F2 = function< T(T, Data) >;
 
  vector< vector< Node > > g;
  vector< vector< T > > ldp, rdp;
  vector< int > lptr, rptr;
  const F1 f1;
  const F2 f2;
  const T ident;
 
  ReRooting(int n, const F1 &f1, const F2 &f2, const T &ident) :
      g(n), ldp(n), rdp(n), lptr(n), rptr(n), f1(f1), f2(f2), ident(ident) {}
 
  void add_edge(int u, int v, const Data &d) {
    g[u].emplace_back((Node) {v, (int) g[v].size(), d});
    g[v].emplace_back((Node) {u, (int) g[u].size() - 1, d});
  }
 
  void add_edge_bi(int u, int v, const Data &d, const Data &e) {
    g[u].emplace_back((Node) {v, (int) g[v].size(), d});
    g[v].emplace_back((Node) {u, (int) g[u].size() - 1, e});
  }
 
 
  T dfs(int idx, int par) {
 
    while(lptr[idx] != par && lptr[idx] < g[idx].size()) {
      auto &e = g[idx][lptr[idx]];
      ldp[idx][lptr[idx] + 1] = f1(ldp[idx][lptr[idx]], f2(dfs(e.to, e.rev), e.data));
      ++lptr[idx];
    }
    while(rptr[idx] != par && rptr[idx] >= 0) {
      auto &e = g[idx][rptr[idx]];
      rdp[idx][rptr[idx]] = f1(rdp[idx][rptr[idx] + 1], f2(dfs(e.to, e.rev), e.data));
      --rptr[idx];
    }
    if(par < 0) return rdp[idx][0];
    return f1(ldp[idx][par], rdp[idx][par + 1]);
  }
 
  vector< T > solve() {
    for(int i = 0; i < g.size(); i++) {
      ldp[i].assign(g[i].size() + 1, ident);
      rdp[i].assign(g[i].size() + 1, ident);
      lptr[i] = 0;
      rptr[i] = (int) g[i].size() - 1;
    }
    vector< T > ret;
    for(int i = 0; i < g.size(); i++) {
      ret.push_back(dfs(i, -1));
    }
    return ret;
  }
};
