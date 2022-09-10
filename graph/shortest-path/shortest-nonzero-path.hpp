/**
 * @brief Shortest Nonzero Path(群ラベル制約付き単一始点最短路)
 */
template< typename T, typename S, typename F >
struct ShortestNonzeroPath {
private:
  constexpr static T INF = numeric_limits< T >::max();
  struct edge {
    int to;
    T cost;
    S label;
  };
  vector< vector< edge > > g;
  F f;
  vector< int > uf;

  int find_uf(int k) {
    if(uf[k] == -1) return k;
    return uf[k] = find_uf(uf[k]);
  }

  void unite_uf(int r, int c) {
    uf[c] = r;
  }

public:
  explicit ShortestNonzeroPath(int n, const F &f) : g(n), f(f) {}

  void add_undirected_edge(int u, int v, const T &cost, const S &label) {
    add_directed_edge(u, v, cost, label);
    add_directed_edge(v, u, cost, label);
  }

  void add_directed_edge(int u, int v, const T &cost, const S &label) {
    g[u].emplace_back((edge) {v, cost, label});
  }

  struct SP {
    vector< T > dist;
    vector< int > depth, parent;
    vector< S > label;
  };

  SP dijkstra(int s) {
    int n = (int) g.size();
    using pi = pair< T, int >;
    vector< T > dist(n, INF);
    vector< int > depth(n, -1), parent(n, -1);
    vector< S > label(n, S());
    priority_queue< pi, vector< pi >, greater<> > que;
    dist[s] = T(0);
    depth[s] = 0;
    que.emplace(0, s);
    while(not que.empty()) {
      T cost;
      int u;
      tie(cost, u) = que.top();
      que.pop();
      if(dist[u] < cost) {
        continue;
      }
      for(auto e : g[u]) {
        if(cost + e.cost < dist[e.to]) {
          dist[e.to] = cost + e.cost;
          depth[e.to] = depth[u] + 1;
          parent[e.to] = u;
          label[e.to] = f(label[u], e.label);
          que.emplace(dist[e.to], e.to);
        }
      }
    }
    return {dist, depth, parent, label};
  }

  vector< T > build(int s) {
    int n = (int) g.size();
    auto sp = dijkstra(s);

    uf.assign(n, -1);
    using pi = tuple< T, int, int >;
    priority_queue< pi, vector< pi >, greater<> > que;
    for(int u = 0; u < n; u++) {
      if(sp.dist[u] != INF) {
        for(int i = 0; i < (int) g[u].size(); i++) {
          auto &e = g[u][i];
          if(u < e.to and f(sp.label[u], e.label) != sp.label[e.to]) {
            que.emplace(sp.dist[u] + sp.dist[e.to] + e.cost, u, i);
          }
        }
      }
    }
    vector< T > dist(n, INF);
    vector< int > bs;
    while(not que.empty()) {
      T cost;
      int u0, i;
      tie(cost, u0, i) = que.top();
      que.pop();
      int v0 = g[u0][i].to;
      int u = find_uf(u0), v = find_uf(v0);
      while(u != v) {
        if(sp.depth[u] > sp.depth[v]) {
          bs.emplace_back(u);
          u = find_uf(sp.parent[u]);
        } else {
          bs.emplace_back(v);
          v = find_uf(sp.parent[v]);
        }
      }
      for(auto &x : bs) {
        unite_uf(u, x);
        dist[x] = cost - sp.dist[x];
        for(int j = 0; j < (int) g[x].size(); j++) {
          auto &e = g[x][j];
          if(f(sp.label[x], e.label) == sp.label[e.to]) {
            que.emplace(dist[x] + sp.dist[e.to] + e.cost, x, j);
          }
        }
      }
      bs.clear();
    }
    for(int i = 0; i < n; i++) {
      if(sp.label[i] != S() and sp.dist[i] < dist[i]) {
        dist[i] = sp.dist[i];
      }
    }
    return dist;
  }
};

template< typename T, typename S, typename F >
ShortestNonzeroPath< T, S, F > get_shortest_nonzero_path(int N, const F &f) {
  return ShortestNonzeroPath< T, S, F >{N, f};
}
