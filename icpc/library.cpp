ICPC Library @ tapu
--------------------------------------------------
|                      tree                      |
--------------------------------------------------

##################################################
############### tree-diameter.cpp ################
##################################################

template< typename T >
pair< T, int > dfs(const WeightedGraph< T > &g, int idx, int par) {
  pair< T, int > ret(0, idx);
  for(auto &e : g[idx]) {
    if(e.to == par) continue;
    auto cost = dfs(g, e.to, idx);
    cost.first += e.cost;
    ret = max(ret, cost);
  }
  return ret;
}

template< typename T >
T tree_diameter(const WeightedGraph< T > &g) {
  auto p = dfs(g, 0, -1);
  auto q = dfs(g, p.second, -1);
  return (q.first);
}


##################################################
###### doubling-lowest-common-ancestor.cpp #######
##################################################

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


##################################################
############## tree-isomorphism.cpp ##############
##################################################

template< typename G >
bool tree_isomorphism(const G &a, const G &b) {
  if(a.size() != b.size()) return false;

  const int N = (int) a.size();
  using pvi = pair< vector< int >, vector< int > >;

  auto get_uku = [&](const G &t, int e) {
    stack< pair< int, int > > st;
    st.emplace(e, -1);
    vector< int > dep(N, -1), par(N);
    while(!st.empty()) {
      auto p = st.top();
      if(dep[p.first] == -1) {
        dep[p.first] = p.second == -1 ? 0 : dep[p.second] + 1;
        for(auto &to : t[p.first]) if(to != p.second) st.emplace(to, p.first);
      } else {
        par[p.first] = p.second;
        st.pop();
      }
    }
    return make_pair(dep, par);
  };

  auto solve = [&](const pvi &latte, const pvi &malta) {

    int d = *max_element(begin(latte.first), end(latte.first));
    if(d != *max_element(begin(malta.first), end(malta.first))) return false;

    vector< vector< int > > latte_d(d + 1), malta_d(d + 1), latte_key(N), malta_key(N);

    for(int i = 0; i < N; i++) latte_d[latte.first[i]].emplace_back(i);
    for(int i = 0; i < N; i++) malta_d[malta.first[i]].emplace_back(i);

    for(int i = d; i >= 0; i--) {
      map< vector< int >, int > ord;
      for(auto &idx : latte_d[i]) {
        sort(begin(latte_key[idx]), end(latte_key[idx]));
        ord[latte_key[idx]]++;
      }
      for(auto &idx : malta_d[i]) {
        sort(begin(malta_key[idx]), end(malta_key[idx]));
        if(--ord[malta_key[idx]] < 0) return false;
      }
      if(i == 0) return ord.size() == 1;

      int ptr = 0;
      for(auto &p : ord) {
        if(p.second != 0) return false;
        p.second = ptr++;
      }
      for(auto &idx : latte_d[i]) {
        latte_key[latte.second[idx]].emplace_back(ord[latte_key[idx]]);
      }
      for(auto &idx : malta_d[i]) {
        malta_key[malta.second[idx]].emplace_back(ord[malta_key[idx]]);
      }
    }
    assert(0);
  };
  auto p = centroid(a), q = centroid(b);
  if(p.size() != q.size()) return false;
  auto a1 = get_uku(a, p[0]);
  auto b1 = get_uku(b, q[0]);
  if(solve(a1, b1)) return true;
  if(p.size() == 1) return false;
  auto a2 = get_uku(a, p[1]);
  return solve(a2, b1);
}


##################################################
######### heavy-light-decomposition.cpp ##########
##################################################

template< typename G >
struct HeavyLightDecomposition {
  G &g;
  vector< int > sz, in, out, head, rev, par;

  HeavyLightDecomposition(G &g) :
      g(g), sz(g.size()), in(g.size()), out(g.size()), head(g.size()), rev(g.size()), par(g.size()) {}

  void dfs_sz(int idx, int p) {
    par[idx] = p;
    sz[idx] = 1;
    if(g[idx].size() && g[idx][0] == p) swap(g[idx][0], g[idx].back());
    for(auto &to : g[idx]) {
      if(to == p) continue;
      dfs_sz(to, idx);
      sz[idx] += sz[to];
      if(sz[g[idx][0]] < sz[to]) swap(g[idx][0], to);
    }
  }

  void dfs_hld(int idx, int par, int &times) {
    in[idx] = times++;
    rev[in[idx]] = idx;
    for(auto &to : g[idx]) {
      if(to == par) continue;
      head[to] = (g[idx][0] == to ? head[idx] : to);
      dfs_hld(to, idx, times);
    }
    out[idx] = times;
  }

  void build() {
    dfs_sz(0, -1);
    int t = 0;
    dfs_hld(0, -1, t);
  }

  int la(int v, int k) {
    while(1) {
      int u = head[v];
      if(in[v] - k >= in[u]) return rev[in[v] - k];
      k -= in[v] - in[u] + 1;
      v = par[u];
    }
  }

  int lca(int u, int v) {
    for(;; v = par[head[v]]) {
      if(in[u] > in[v]) swap(u, v);
      if(head[u] == head[v]) return u;
    }
  }

  template< typename T, typename Q, typename F >
  T query(int u, int v, const T &ti, const Q &q, const F &f, bool edge = false) {
    T l = ti, r = ti;
    for(;; v = par[head[v]]) {
      if(in[u] > in[v]) swap(u, v), swap(l, r);
      if(head[u] == head[v]) break;
      l = f(q(in[head[v]], in[v] + 1), l);
    }
    return f(f(q(in[u] + edge, in[v] + 1), l), r);
//  return {f(q(in[u] + edge, in[v] + 1), l), r};
  }

  template< typename Q >
  void add(int u, int v, const Q &q, bool edge = false) {
    for(;; v = par[head[v]]) {
      if(in[u] > in[v]) swap(u, v);
      if(head[u] == head[v]) break;
      q(in[head[v]], in[v] + 1);
    }
    q(in[u] + edge, in[v] + 1);
  }
};


##################################################
################# rerooting.cpp ##################
##################################################

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


##################################################
############ convert-rooted-tree.cpp #############
##################################################

template< typename G >
G convert_rooted_tree(const G &g, int r = 0) {
  int N = (int) g.size();
  G rg(N);
  vector< int > v(N);
  v[r] = 1;
  queue< int > que;
  que.emplace(r);
  while(!que.empty()) {
    auto p = que.front();
    que.pop();
    for(auto &to : g[p]) {
      if(v[to] == 0) {
        v[to] = 1;
        que.emplace(to);
        rg[p].emplace_back(to);
      }
    }
  }
  return rg;
}


##################################################
########### centroid-decomposition.cpp ###########
##################################################

template< typename G >
struct CentroidDecomposition {
  const G &g;
  vector< int > sub;
  vector< vector< int > > belong;
  vector< bool > v;

  CentroidDecomposition(const G &g) : g(g), sub(g.size()), v(g.size()), belong(g.size()) {}

  inline int build_dfs(int idx, int par) {
    sub[idx] = 1;
    for(auto &to : g[idx]) {
      if(to == par || v[to]) continue;
      sub[idx] += build_dfs(to, idx);
    }
    return sub[idx];
  }

  inline int search_centroid(int idx, int par, const int mid) {
    for(auto &to : g[idx]) {
      if(to == par || v[to]) continue;
      if(sub[to] > mid) return search_centroid(to, idx, mid);
    }
    return idx;
  }

  inline void belong_dfs(int idx, int par, int centroid) {
    belong[idx].emplace_back(centroid);
    for(auto &to : g[idx]) {
      if(to == par || v[to]) continue;
      belong_dfs(to, idx, centroid);
    }
  }

  inline int build(UnWeightedGraph &t, int idx) {
    int centroid = search_centroid(idx, -1, build_dfs(idx, -1) / 2);
    v[centroid] = true;
    belong_dfs(centroid, -1, centroid);
    for(auto &to : g[centroid]) {
      if(!v[to]) t[centroid].emplace_back(build(t, to));
    }
    v[centroid] = false;
    return centroid;
  }

  inline int build(UnWeightedGraph &t) {
    t.resize(g.size());
    return build(t, 0);
  }
};


##################################################
################## centroid.cpp ##################
##################################################

template< typename G >
vector< int > centroid(const G &g) {
  const int N = (int) g.size();

  stack< pair< int, int > > st;
  st.emplace(0, -1);
  vector< int > sz(N), par(N);
  while(!st.empty()) {
    auto p = st.top();
    if(sz[p.first] == 0) {
      sz[p.first] = 1;
      for(auto &to : g[p.first]) if(to != p.second) st.emplace(to, p.first);
    } else {
      for(auto &to : g[p.first]) if(to != p.second) sz[p.first] += sz[to];
      par[p.first] = p.second;
      st.pop();
    }
  }

  vector< int > ret;
  int size = N;
  for(int i = 0; i < N; i++) {
    int val = N - sz[i];
    for(auto &to : g[i]) if(to != par[i]) val = max(val, sz[to]);
    if(val < size) size = val, ret.clear();
    if(val == size) ret.emplace_back(i);
  }

  return ret;
}


--------------------------------------------------
|                     graph                      |
--------------------------------------------------

##################################################
################## boruvka.cpp ###################
##################################################

template< typename T, typename F >
T boruvka(int N, F f) {
  vector< int > rev(N), belong(N);
  UnionFind uf(N);
  T ret = T();
  while(uf.size(0) != N) {
    int ptr = 0;
    for(int i = 0; i < N; i++) {
      if(uf.find(i) == i) {
        belong[i] = ptr++;
        rev[belong[i]] = i;
      }
    }
    for(int i = 0; i < N; i++) {
      belong[i] = belong[uf.find(i)];
    }
    auto v = f(ptr, belong);
    bool update = false;
    for(int i = 0; i < ptr; i++) {
      if(~v[i].second && uf.unite(rev[i], rev[v[i].second])) {
        ret += v[i].first;
        update = true;
      }
    }
    if(!update) return -1; // notice!!
  }
  return ret;
}


##################################################
################## dijkstra.cpp ##################
##################################################

template< typename T >
vector< T > dijkstra(WeightedGraph< T > &g, int s) {
  const auto INF = numeric_limits< T >::max();
  vector< T > dist(g.size(), INF);

  using Pi = pair< T, int >;
  priority_queue< Pi, vector< Pi >, greater< Pi > > que;
  dist[s] = 0;
  que.emplace(dist[s], s);
  while(!que.empty()) {
    T cost;
    int idx;
    tie(cost, idx) = que.top();
    que.pop();
    if(dist[idx] < cost) continue;
    for(auto &e : g[idx]) {
      auto next_cost = cost + e.cost;
      if(dist[e.to] <= next_cost) continue;
      dist[e.to] = next_cost;
      que.emplace(dist[e.to], e.to);
    }
  }
  return dist;
}


##################################################
################## template.cpp ##################
##################################################

template< typename T >
struct edge {
  int src, to;
  T cost;

  edge(int to, T cost) : src(-1), to(to), cost(cost) {}

  edge(int src, int to, T cost) : src(src), to(to), cost(cost) {}

  edge &operator=(const int &x) {
    to = x;
    return *this;
  }

  operator int() const { return to; }
};

template< typename T >
using Edges = vector< edge< T > >;
template< typename T >
using WeightedGraph = vector< Edges< T > >;
using UnWeightedGraph = vector< vector< int > >;
template< typename T >
using Matrix = vector< vector< T > >;


##################################################
############# bipartite-matching.cpp #############
##################################################

struct BipartiteMatching {
  vector< vector< int > > graph;
  vector< int > match, alive, used;
  int timestamp;

  BipartiteMatching(int n) : graph(n), alive(n, 1), used(n, 0), match(n, -1), timestamp(0) {}

  void add_edge(int u, int v) {
    graph[u].push_back(v);
    graph[v].push_back(u);
  }

  bool dfs(int idx) {
    used[idx] = timestamp;
    for(auto &to : graph[idx]) {
      int to_match = match[to];
      if(alive[to] == 0) continue;
      if(to_match == -1 || (used[to_match] != timestamp && dfs(to_match))) {
        match[idx] = to;
        match[to] = idx;
        return true;
      }
    }
    return false;
  }

  int bipartite_matching() {
    int ret = 0;
    for(int i = 0; i < graph.size(); i++) {
      if(alive[i] == 0) continue;
      if(match[i] == -1) {
        ++timestamp;
        ret += dfs(i);
      }
    }
    return ret;
  }

  void output() {
    for(int i = 0; i < graph.size(); i++) {
      if(i < match[i]) {
        cout << i << "-" << match[i] << endl;
      }
    }
  }
};



##################################################
############### warshall-floyd.cpp ###############
##################################################

template< typename T >
void warshall_floyd(Matrix< T > &g, T INF) {
  for(int k = 0; k < g.size(); k++) {
    for(int i = 0; i < g.size(); i++) {
      for(int j = 0; j < g.size(); j++) {
        if(g[i][k] == INF || g[k][j] == INF) continue;
        g[i][j] = min(g[i][j], g[i][k] + g[k][j]);
      }
    }
  }
}


##################################################
############### gabow-edmonds.cpp ################
##################################################

// https://qiita.com/Kutimoti_T/items/5b579773e0a24d650bdf
struct GabowEdmonds {

  struct edge {
    int to, idx;
  };

  vector< vector< edge > > g;
  vector< pair< int, int > > edges;
  vector< int > mate, label, first;
  queue< int > que;

  GabowEdmonds(int n) : g(n + 1), mate(n + 1), label(n + 1, -1), first(n + 1) {}

  void add_edge(int u, int v) {
    ++u, ++v;
    g[u].push_back((edge) {v, (int) (edges.size() + g.size())});
    g[v].push_back((edge) {u, (int) (edges.size() + g.size())});
    edges.emplace_back(u, v);
  }

  int find(int x) {
    if(label[first[x]] < 0) return first[x];
    first[x] = find(first[x]);
    return first[x];
  }

  void rematch(int v, int w) {
    int t = mate[v];
    mate[v] = w;
    if(mate[t] != v) return;
    if(label[v] < g.size()) {
      mate[t] = label[v];
      rematch(label[v], t);
    } else {
      int x = edges[label[v] - g.size()].first;
      int y = edges[label[v] - g.size()].second;
      rematch(x, y);
      rematch(y, x);
    }
  }

  void assign_label(int x, int y, int num) {
    int r = find(x);
    int s = find(y);
    int join = 0;
    if(r == s) return;
    label[r] = -num;
    label[s] = -num;
    while(true) {
      if(s != 0) swap(r, s);
      r = find(label[mate[r]]);
      if(label[r] == -num) {
        join = r;
        break;
      }
      label[r] = -num;
    }
    int v = first[x];
    while(v != join) {
      que.push(v);
      label[v] = num;
      first[v] = join;
      v = first[label[mate[v]]];
    }
    v = first[y];
    while(v != join) {
      que.push(v);
      label[v] = num;
      first[v] = join;
      v = first[label[mate[v]]];
    }
  }

  bool augment_check(int u) {
    que = queue< int >();
    first[u] = 0;
    label[u] = 0;
    que.push(u);
    while(!que.empty()) {
      int x = que.front();
      que.pop();
      for(auto e : g[x]) {
        int y = e.to;
        if(mate[y] == 0 && y != u) {
          mate[y] = x;
          rematch(x, y);
          return true;
        } else if(label[y] >= 0) {
          assign_label(x, y, e.idx);
        } else if(label[mate[y]] < 0) {
          label[mate[y]] = x;
          first[mate[y]] = y;
          que.push(mate[y]);
        }
      }
    }
    return false;
  }

  vector< pair< int, int > > max_matching() {
    for(int i = 1; i < g.size(); i++) {
      if(mate[i] != 0) continue;
      if(augment_check(i)) label.assign(g.size(), -1);
    }
    vector< pair< int, int > > ret;
    for(int i = 1; i < g.size(); i++) {
      if(i < mate[i]) ret.emplace_back(i - 1, mate[i] - 1);
    }
    return ret;
  }
};


##################################################
############ maxflow-lower-bound.cpp #############
##################################################

template< typename flow_t, template< typename > class F >
struct MaxFlowLowerBound {
  F< flow_t > flow;
  vector< flow_t > in, up;
  typename F< flow_t >::edge *latte, *malta;
  int X, Y, V;
  flow_t sum;

  MaxFlowLowerBound(int V) : V(V), flow(V + 2), X(V), Y(V + 1), sum(0), in(V) {}

  void add_edge(int from, int to, flow_t low, flow_t high) {
    assert(from != to);
    flow.add_edge(from, to, high - low, up.size());
    in[from] -= low;
    in[to] += low;
    up.emplace_back(high);
  }

  void build() {
    for(int i = 0; i < V; i++) {
      if(in[i] > 0) {
        flow.add_edge(X, i, in[i]);
        sum += in[i];
      } else if(in[i] < 0) {
        flow.add_edge(i, Y, -in[i]);
      }
    }
  }

  bool can_flow(int s, int t) {
    assert(s != t);
    flow.add_edge(t, s, flow.INF);
    latte = &flow.graph[t].back();
    malta = &flow.graph[s].back();
    return can_flow();
  }

  bool can_flow() {
    build();
    auto ret = flow.max_flow(X, Y);
    return ret >= sum;
  }

  flow_t max_flow(int s, int t) {
    if(can_flow(s, t)) {
      return flow.max_flow(s, t);
    } else {
      return -1;
    }
  }

  flow_t min_flow(int s, int t) {
    if(can_flow(s, t)) {
      auto ret = flow.INF - latte->cap;
      latte->cap = malta->cap = 0;
      return ret - flow.max_flow(t, s);
    } else {
      return -1;
    }
  }

  void output(int M) {
    vector< flow_t > ans(M);
    for(int i = 0; i < flow.graph.size(); i++) {
      for(auto &e : flow.graph[i]) {
        if(!e.isrev && ~e.idx) ans[e.idx] = up[e.idx] - e.cap;
      }
    }
    for(auto &p : ans) cout << p << endl;
  }
};


##################################################
################ primal-dual.cpp #################
##################################################

template< typename flow_t, typename cost_t >
struct PrimalDual {
  const cost_t INF;

  struct edge {
    int to;
    flow_t cap;
    cost_t cost;
    int rev;
    bool isrev;
  };
  vector< vector< edge > > graph;
  vector< cost_t > potential, min_cost;
  vector< int > prevv, preve;

  PrimalDual(int V) : graph(V), INF(numeric_limits< cost_t >::max()) {}

  void add_edge(int from, int to, flow_t cap, cost_t cost) {
    graph[from].emplace_back((edge) {to, cap, cost, (int) graph[to].size(), false});
    graph[to].emplace_back((edge) {from, 0, -cost, (int) graph[from].size() - 1, true});
  }

  cost_t min_cost_flow(int s, int t, flow_t f) {
    int V = (int) graph.size();
    cost_t ret = 0;
    using Pi = pair< cost_t, int >;
    priority_queue< Pi, vector< Pi >, greater< Pi > > que;
    potential.assign(V, 0);
    preve.assign(V, -1);
    prevv.assign(V, -1);

    while(f > 0) {
      min_cost.assign(V, INF);
      que.emplace(0, s);
      min_cost[s] = 0;
      while(!que.empty()) {
        Pi p = que.top();
        que.pop();
        if(min_cost[p.second] < p.first) continue;
        for(int i = 0; i < graph[p.second].size(); i++) {
          edge &e = graph[p.second][i];
          cost_t nextCost = min_cost[p.second] + e.cost + potential[p.second] - potential[e.to];
          if(e.cap > 0 && min_cost[e.to] > nextCost) {
            min_cost[e.to] = nextCost;
            prevv[e.to] = p.second, preve[e.to] = i;
            que.emplace(min_cost[e.to], e.to);
          }
        }
      }
      if(min_cost[t] == INF) return -1;
      for(int v = 0; v < V; v++) potential[v] += min_cost[v];
      flow_t addflow = f;
      for(int v = t; v != s; v = prevv[v]) {
        addflow = min(addflow, graph[prevv[v]][preve[v]].cap);
      }
      f -= addflow;
      ret += addflow * potential[t];
      for(int v = t; v != s; v = prevv[v]) {
        edge &e = graph[prevv[v]][preve[v]];
        e.cap -= addflow;
        graph[v][e.rev].cap += addflow;
      }
    }
    return ret;
  }

  void output() {
    for(int i = 0; i < graph.size(); i++) {
      for(auto &e : graph[i]) {
        if(e.isrev) continue;
        auto &rev_e = graph[e.to][e.rev];
        cout << i << "->" << e.to << " (flow: " << rev_e.cap << "/" << rev_e.cap + e.cap << ")" << endl;
      }
    }
  }
};


##################################################
################ bellman-ford.cpp ################
##################################################

template< typename T >
vector< T > bellman_ford(Edges< T > &edges, int V, int s) {
  const auto INF = numeric_limits< T >::max();
  vector< T > dist(V, INF);
  dist[s] = 0;
  for(int i = 0; i < V - 1; i++) {
    for(auto &e : edges) {
      if(dist[e.src] == INF) continue;
      dist[e.to] = min(dist[e.to], dist[e.src] + e.cost);
    }
  }
  for(auto &e : edges) {
    if(dist[e.src] == INF) continue;
    if(dist[e.src] + e.cost < dist[e.to]) return vector< T >();
  }
  return dist;
}



##################################################
################# hungarian.cpp ##################
##################################################

template< typename T >
T hungarian(Matrix< T > &A) {
  const T infty = numeric_limits< T >::max();
  const int N = (int) A.size();
  const int M = (int) A[0].size();
  vector< int > P(M), way(M);
  vector< T > U(N, 0), V(M, 0), minV;
  vector< bool > used;

  for(int i = 1; i < N; i++) {
    P[0] = i;
    minV.assign(M, infty);
    used.assign(M, false);
    int j0 = 0;
    while(P[j0] != 0) {
      int i0 = P[j0], j1 = 0;
      used[j0] = true;
      T delta = infty;
      for(int j = 1; j < M; j++) {
        if(used[j]) continue;
        T curr = A[i0][j] - U[i0] - V[j];
        if(curr < minV[j]) minV[j] = curr, way[j] = j0;
        if(minV[j] < delta) delta = minV[j], j1 = j;
      }
      for(int j = 0; j < M; j++) {
        if(used[j]) U[P[j]] += delta, V[j] -= delta;
        else minV[j] -= delta;
      }
      j0 = j1;
    }
    do {
      P[j0] = P[way[j0]];
      j0 = way[j0];
    } while(j0 != 0);
  }
  return -V[0];
}


##################################################
########## maximum-independent-set.cpp ###########
##################################################

template< typename T >
vector< int > maximum_independent_set(const Matrix< T > &g, int trial = 1000000) {

  int N = (int) g.size();
  vector< uint64_t > bit(N);

  assert(N <= 64);
  for(int i = 0; i < N; i++) {
    for(int j = 0; j < N; j++) {
      if(i != j) {
        assert(g[i][j] == g[j][i]);
        if(g[i][j]) bit[i] |= uint64_t(1) << j;
      }
    }
  }

  vector< int > ord(N);
  iota(begin(ord), end(ord), 0);
  mt19937 mt(chrono::steady_clock::now().time_since_epoch().count());
  int ret = 0;
  uint64_t ver;
  for(int i = 0; i < trial; i++) {
    shuffle(begin(ord), end(ord), mt);
    uint64_t used = 0;
    int add = 0;
    for(int j : ord) {
      if(used & bit[j]) continue;
      used |= uint64_t(1) << j;
      ++add;
    }
    if(ret < add) {
      ret = add;
      ver = used;
    }
  }
  vector< int > ans;
  for(int i = 0; i < N; i++) {
    if((ver >> i) & 1) ans.emplace_back(i);
  }
  return ans;
}


##################################################
################ push-relabel.cpp ################
##################################################

template< typename flow_t >
struct PushRelabel {
  const flow_t INF;

  struct edge {
    int to;
    flow_t cap;
    int rev;
    bool isrev;
    int idx;
  };
  vector< vector< edge > > graph;
  vector< flow_t > ex;
  int relabels, high;
  vector< int > cnt, h;
  vector< vector< int > > hs;

  PushRelabel(int V) : graph(V), INF(numeric_limits< flow_t >::max()), hs(V + 1), high(0) {}


  void add_edge(int from, int to, flow_t cap, int idx = -1) {
    graph[from].emplace_back((edge) {to, cap, (int) graph[to].size(), false, idx});
    graph[to].emplace_back((edge) {from, 0, (int) graph[from].size() - 1, true, idx});
  }

  void update_height(int idx, int nxt_height) {
    ++relabels;
    if(h[idx] != graph.size() + 1) {
      --cnt[h[idx]];
    }
    h[idx] = nxt_height;
    if(h[idx] != graph.size() + 1) {
      high = nxt_height;
      ++cnt[nxt_height];
      if(ex[idx] > 0) hs[nxt_height].emplace_back(idx);
    }
  }

  void global_relabel(int idx) {
    for(int i = 0; i <= high; i++) hs[i].clear();
    relabels = 0;
    high = 0;
    h.assign(graph.size(), graph.size() + 1);
    cnt.assign(graph.size(), 0);
    queue< int > que;
    que.emplace(idx);
    h[idx] = 0;
    while(que.size()) {
      int p = que.front();
      que.pop();
      for(auto &e : graph[p]) {
        if(h[e.to] == graph.size() + 1 && graph[e.to][e.rev].cap > 0) {
          que.emplace(e.to);
          high = h[p] + 1;
          update_height(e.to, high);
        }
      }
    }
  }


  void push(int idx, edge &e) {
    if(h[e.to] == graph.size() + 1) return;
    if(ex[e.to] == 0) {
      hs[h[e.to]].emplace_back(e.to);
    }
    flow_t df = min(ex[idx], e.cap);
    e.cap -= df;
    graph[e.to][e.rev].cap += df;
    ex[idx] -= df;
    ex[e.to] += df;
  }

  void discharge(int idx) {
    int next_height = (int) graph.size() + 1;
    for(auto &&e : graph[idx]) {
      if(e.cap > 0) {
        if(h[idx] == h[e.to] + 1) {
          push(idx, e);
          if(ex[idx] <= 0) return;
        } else {
          next_height = min(next_height, h[e.to] + 1);
        }
      }
    }
    if(cnt[h[idx]] > 1) {
      update_height(idx, next_height);
    } else {
      for(; high >= h[idx]; hs[high--].clear()) {
        for(int j : hs[high]) update_height(j, graph.size() + 1);
      }
    }
  }

  flow_t max_flow(int s, int t) {
    ex.assign(graph.size(), 0);
    ex[s] = INF;
    ex[t] = -INF;
    global_relabel(t);
    for(auto &e : graph[s]) push(s, e);
    for(; high >= 0; high--) {
      while(!hs[high].empty()) {
        int idx = hs[high].back();
        hs[high].pop_back();
        discharge(idx);
        if(relabels >= graph.size() * 4) global_relabel(t);
      }
    }
    return ex[t] + INF;
  }

  void output() {
    for(int i = 0; i < graph.size(); i++) {
      for(auto &e : graph[i]) {
        if(e.isrev) continue;
        auto &rev_e = graph[e.to][e.rev];
        cout << i << "->" << e.to << " (flow: " << rev_e.cap << "/" << e.cap + rev_e.cap << ")" << endl;
      }
    }
  }
};


##################################################
################## kruskal.cpp ###################
##################################################

template< typename T >
T kruskal(Edges< T > &edges, int V) {
  sort(begin(edges), end(edges), [](const edge< T > &a, const edge< T > &b) {
    return (a.cost < b.cost);
  });
  UnionFind tree(V);
  T ret = 0;
  for(auto &e : edges) {
    if(tree.unite(e.src, e.to)) ret += e.cost;
  }
  return (ret);
}


##################################################
############### ford-fulkerson.cpp ###############
##################################################

template< typename flow_t >
struct FordFulkerson {
  struct edge {
    int to;
    flow_t cap;
    int rev;
    bool isrev;
    int idx;
  };

  vector< vector< edge > > graph;
  vector< int > used;
  const flow_t INF;
  int timestamp;

  FordFulkerson(int n) : INF(numeric_limits< flow_t >::max()), timestamp(0) {
    graph.resize(n);
    used.assign(n, -1);
  }

  void add_edge(int from, int to, flow_t cap, int idx = -1) {
    graph[from].emplace_back((edge) {to, cap, (int) graph[to].size(), false, idx});
    graph[to].emplace_back((edge) {from, 0, (int) graph[from].size() - 1, true, idx});
  }

  flow_t dfs(int idx, const int t, flow_t flow) {
    if(idx == t) return flow;
    used[idx] = timestamp;
    for(auto &e : graph[idx]) {
      if(e.cap > 0 && used[e.to] != timestamp) {
        flow_t d = dfs(e.to, t, min(flow, e.cap));
        if(d > 0) {
          e.cap -= d;
          graph[e.to][e.rev].cap += d;
          return d;
        }
      }
    }
    return 0;
  }

  flow_t max_flow(int s, int t) {
    flow_t flow = 0;
    for(flow_t f; (f = dfs(s, t, INF)) > 0; timestamp++) {
      flow += f;
    }
    return flow;
  }

  void output() {
    for(int i = 0; i < graph.size(); i++) {
      for(auto &e : graph[i]) {
        if(e.isrev) continue;
        auto &rev_e = graph[e.to][e.rev];
        cout << i << "->" << e.to << " (flow: " << rev_e.cap << "/" << e.cap + rev_e.cap << ")" << endl;
      }
    }
  }
};


##################################################
########## offline-dag-reachability.cpp ##########
##################################################

template< typename G >
vector< int > offline_dag_reachability(const G &g, vector< pair< int, int > > &qs) {
  const int N = (int) g.size();
  const int Q = (int) qs.size();
  auto ord = topological_sort(g);
  vector< int > ans(Q);
  for(int l = 0; l < Q; l += 64) {
    int r = min(Q, l + 64);
    vector< int64_t > dp(N);
    for(int k = l; k < r; k++) {
      dp[qs[k].first] |= int64_t(1) << (k - l);
    }
    for(auto &idx : ord) {
      for(auto &to : g[idx]) dp[to] |= dp[idx];
    }
    for(int k = l; k < r; k++) {
      ans[k] = (dp[qs[k].second] >> (k - l)) & 1;
    }
  }
  return ans;
}


##################################################
############## chromatic-number.cpp ##############
##################################################

int chromatic_number(const Matrix< bool > &g) {
  int N = (int) g.size();
  vector< int > es(N);
  for(int i = 0; i < g.size(); i++) {
    for(int j = 0; j < g.size(); j++) {
      es[i] |= g[i][j] << j;
    }
  }
  int ret = N;
  for(int d : {7, 11, 21}) {
    int mod = 1e9 + d;
    vector< int > ind(1 << N), aux(1 << N, 1);
    ind[0] = 1;
    for(int S = 1; S < 1 << N; S++) {
      int u = __builtin_ctz(S);
      ind[S] = ind[S ^ (1 << u)] + ind[(S ^ (1 << u)) & ~es[u]];
    }
    for(int i = 1; i < ret; i++) {
      int64_t all = 0;
      for(int j = 0; j < 1 << N; j++) {
        int S = j ^(j >> 1);
        aux[S] = (1LL * aux[S] * ind[S]) % mod;
        all += j & 1 ? aux[S] : mod - aux[S];
      }
      if(all % mod) ret = i;
    }
  }
  return ret;
}



##################################################
################## grid-bfs.cpp ##################
##################################################

vector< vector< int > > grid_bfs(vector< string > &s, char start, const string &wall = "#") {
  const int vx[] = {0, 1, 0, -1}, vy[] = {1, 0, -1, 0};
  vector< vector< int > > min_cost(s.size(), vector< int >(s[0].size(), -1));
  queue< pair< int, int > > que;
  for(int i = 0; i < s.size(); i++) {
    for(int j = 0; j < s[i].size(); j++) {
      if(s[i][j] == start) {
        que.emplace(i, j);
        min_cost[i][j] = 0;
      }
    }
  }
  while(!que.empty()) {
    auto p = que.front();
    que.pop();
    for(int i = 0; i < 4; i++) {
      int ny = p.first + vy[i], nx = p.second + vx[i];
      if(nx < 0 || ny < 0 || nx >= s[0].size() || ny >= s.size()) continue;
      if(min_cost[ny][nx] != -1) continue;
      if(wall.find(s[ny][nx]) != string::npos) continue;
      min_cost[ny][nx] = min_cost[p.first][p.second] + 1;
      que.emplace(ny, nx);
    }
  }
  return min_cost;
}


##################################################
####### two-edge-connected-components.cpp ########
##################################################

template< typename G >
struct TwoEdgeConnectedComponents : LowLink< G > {
  using LL = LowLink< G >;
  vector< int > comp;
 
  TwoEdgeConnectedComponents(const G &g) : LL(g) {}
 
  int operator[](const int &k) {
    return comp[k];
  }
 
  void dfs(int idx, int par, int &k) {
    if(~par && this->ord[par] >= this->low[idx]) comp[idx] = comp[par];
    else comp[idx] = k++;
    for(auto &to : this->g[idx]) {
      if(comp[to] == -1) dfs(to, idx, k);
    }
  }
 
  void build(UnWeightedGraph &t) {
    LL::build();
    comp.assign(this->g.size(), -1);
    int k = 0;
    for(int i = 0; i < comp.size(); i++) {
      if(comp[i] == -1) dfs(i, -1, k);
    }
    t.resize(k);
    for(auto &e : this->bridge) {
      int x = comp[e.first], y = comp[e.second];
      t[x].push_back(y);
      t[y].push_back(x);
    }
  }
};


##################################################
########### dinic-capacity-scaling.cpp ###########
##################################################

template< typename flow_t >
struct DinicCapacityScaling {

  const flow_t INF;

  struct edge {
    int to;
    flow_t cap;
    int rev;
    bool isrev;
  };

  vector< vector< edge > > graph;
  vector< int > min_cost, iter;
  flow_t max_cap;

  DinicCapacityScaling(int V) : INF(numeric_limits< flow_t >::max()), graph(V), max_cap(0) {}

  void add_edge(int from, int to, flow_t cap) {
    max_cap = max(max_cap, cap);
    graph[from].emplace_back((edge) {to, cap, (int) graph[to].size(), false});
    graph[to].emplace_back((edge) {from, 0, (int) graph[from].size() - 1, true});
  }

  bool bfs(int s, int t, const flow_t &base) {
    min_cost.assign(graph.size(), -1);
    queue< int > que;
    min_cost[s] = 0;
    que.push(s);
    while(!que.empty() && min_cost[t] == -1) {
      int p = que.front();
      que.pop();
      for(auto &e : graph[p]) {
        if(e.cap >= base && min_cost[e.to] == -1) {
          min_cost[e.to] = min_cost[p] + 1;
          que.push(e.to);
        }
      }
    }
    return min_cost[t] != -1;
  }

  flow_t dfs(int idx, const int t, const flow_t base, flow_t flow) {
    if(idx == t) return flow;
    flow_t sum = 0;
    for(int &i = iter[idx]; i < graph[idx].size(); i++) {
      edge &e = graph[idx][i];
      if(e.cap >= base && min_cost[idx] < min_cost[e.to]) {
        flow_t d = dfs(e.to, t, base, min(flow - sum, e.cap));
        if(d > 0) {
          e.cap -= d;
          graph[e.to][e.rev].cap += d;
          sum += d;
          if(flow - sum < base) break;
        }
      }
    }
    return sum;
  }

  flow_t max_flow(int s, int t) {
    if(max_cap == flow_t(0)) return flow_t(0);
    flow_t flow = 0;
    for(int i = 63 - __builtin_clzll(max_cap); i >= 0; i--) {
      flow_t now = flow_t(1) << i;
      while(bfs(s, t, now)) {
        iter.assign(graph.size(), 0);
        flow += dfs(s, t, now, INF);
      }
    }
    return flow;
  }

  void output() {
    for(int i = 0; i < graph.size(); i++) {
      for(auto &e : graph[i]) {
        if(e.isrev) continue;
        auto &rev_e = graph[e.to][e.rev];
        cout << i << "->" << e.to << " (flow: " << rev_e.cap << "/" << e.cap + rev_e.cap << ")" << endl;
      }
    }
  }
};



##################################################
########## bi-connected-components.cpp ###########
##################################################

template< typename G >
struct BiConnectedComponents : LowLink< G > {
  using LL = LowLink< G >;
 
  vector< int > used;
  vector< vector< pair< int, int > > > bc;
  vector< pair< int, int > > tmp;
 
  BiConnectedComponents(const G &g) : LL(g) {}
 
  void dfs(int idx, int par) {
    used[idx] = true;
    for(auto &to : this->g[idx]) {
      if(to == par) continue;
      if(!used[to] || this->ord[to] < this->ord[idx]) {
        tmp.emplace_back(minmax(idx, to));
      }
      if(!used[to]) {
        dfs(to, idx);
        if(this->low[to] >= this->ord[idx]) {
          bc.emplace_back();
          for(;;) {
            auto e = tmp.back();
            bc.back().emplace_back(e);
            tmp.pop_back();
            if(e.first == min(idx, to) && e.second == max(idx, to)) {
              break;
            }
          }
        }
      }
    }
  }
 
  void build() override {
    LL::build();
    used.assign(this->g.size(), 0);
    for(int i = 0; i < used.size(); i++) {
      if(!used[i]) dfs(i, -1);
    }
  }
};


##################################################
####### strongly-connected-components.cpp ########
##################################################

template< typename G >
struct StronglyConnectedComponents {
  const G &g;
  UnWeightedGraph gg, rg;
  vector< int > comp, order, used;

  StronglyConnectedComponents(G &g) : g(g), gg(g.size()), rg(g.size()), comp(g.size(), -1), used(g.size()) {
    for(int i = 0; i < g.size(); i++) {
      for(auto e : g[i]) {
        gg[i].emplace_back((int) e);
        rg[(int) e].emplace_back(i);
      }
    }
  }

  int operator[](int k) {
    return comp[k];
  }

  void dfs(int idx) {
    if(used[idx]) return;
    used[idx] = true;
    for(int to : gg[idx]) dfs(to);
    order.push_back(idx);
  }

  void rdfs(int idx, int cnt) {
    if(comp[idx] != -1) return;
    comp[idx] = cnt;
    for(int to : rg[idx]) rdfs(to, cnt);
  }

  void build(UnWeightedGraph &t) {
    for(int i = 0; i < gg.size(); i++) dfs(i);
    reverse(begin(order), end(order));
    int ptr = 0;
    for(int i : order) if(comp[i] == -1) rdfs(i, ptr), ptr++;

    t.resize(ptr);
    for(int i = 0; i < g.size(); i++) {
      for(auto &to : g[i]) {
        int x = comp[i], y = comp[to];
        if(x == y) continue;
        t[x].push_back(y);
      }
    }
  }
};


##################################################
############### dominator-tree.cpp ###############
##################################################

template< typename G >
struct DominatorTree {

  struct UnionFind {
    const vector< int > &semi;
    vector< int > par, m;

    UnionFind(const vector< int > &semi) : semi(semi), par(semi.size()), m(semi.size()) {
      iota(begin(par), end(par), 0);
      iota(begin(m), end(m), 0);
    }

    int find(int v) {
      if(par[v] == v) return v;
      int r = find(par[v]);
      if(semi[m[v]] > semi[m[par[v]]]) m[v] = m[par[v]];
      return par[v] = r;
    }

    int eval(int v) {
      find(v);
      return m[v];
    }

    void link(int p, int c) {
      par[c] = p;
    }
  };

  const G &g;
  vector< vector< int > > rg;
  vector< int > ord, par;
  vector< int > idom, semi;
  UnionFind uf;

  DominatorTree(G &g) : g(g), rg(g.size()), par(g.size()), idom(g.size(), -1), semi(g.size(), -1), uf(semi) {
    ord.reserve(g.size());
  }


  void dfs(int idx) {
    semi[idx] = (int) ord.size();
    ord.emplace_back(idx);
    for(auto &to : g[idx]) {
      if(~semi[to]) continue;
      dfs(to);
      par[to] = idx;
    }
  }

  void build(int root) {
    const int N = (int) g.size();
    dfs(root);
    for(int i = 0; i < N; i++) {
      for(auto &to : g[i]) {
        if(~semi[i]) rg[to].emplace_back(i);
      }
    }

    vector< vector< int > > bucket(N);
    vector< int > U(N);
    for(int i = (int) ord.size() - 1; i >= 0; i--) {
      int x = ord[i];
      for(int v : rg[x]) {
        v = uf.eval(v);
        if(semi[x] > semi[v]) semi[x] = semi[v];
      }
      bucket[ord[semi[x]]].emplace_back(x);
      for(int v : bucket[par[x]]) U[v] = uf.eval(v);
      bucket[par[x]].clear();
      uf.link(par[x], x);
    }
    for(int i = 1; i < ord.size(); i++) {
      int x = ord[i], u = U[x];
      idom[x] = semi[x] == semi[u] ? semi[x] : idom[u];
    }
    for(int i = 1; i < ord.size(); i++) {
      int x = ord[i];
      idom[x] = ord[idom[x]];
    }
    idom[root] = root;
  }

  int operator[](const int &k) {
    return idom[k];
  }
};


##################################################
#################### prim.cpp ####################
##################################################

template< typename T >
T prim(WeightedGraph< T > &g) {
  using Pi = pair< T, int >;
 
  T total = 0;
  vector< bool > used(g.size(), false);
  priority_queue< Pi, vector< Pi >, greater< Pi > > que;
  que.emplace(0, 0);
  while(!que.empty()) {
    auto p = que.top();
    que.pop();
    if(used[p.second]) continue;
    used[p.second] = true;
    total += p.first;
    for(auto &e : g[p.second]) {
      que.emplace(e.cost, e.to);
    }
  }
  return total;
}


##################################################
############### eulerian-trail.cpp ###############
##################################################

template< typename T >
vector< edge< T > > eulerian_path(Edges< T > es, int s, bool directed) {
  int V = 0;
  for(auto &e : es) V = max(V, max(e.to, e.src) + 1);
  vector< vector< pair< edge< T >, int > > > g(V);
  for(auto &e : es) {
    int sz_to = (int) g[e.to].size();
    g[e.src].emplace_back(e, sz_to);
    if(!directed) {
      int sz_src = (int) g[e.src].size() - 1;
      swap(e.src, e.to);
      g[e.src].emplace_back(e, sz_src);
    }
  }
  vector< edge< T > > ord;
  stack< pair< int, edge< T > > > st;
  st.emplace(s, edge< T >(-1, -1));
  while(st.size()) {
    int idx = st.top().first;
    if(g[idx].empty()) {
      ord.emplace_back(st.top().second);
      st.pop();
    } else {
      auto e = g[idx].back();
      g[idx].pop_back();
      if(e.second == -1) continue;
      if(!directed) g[e.first.to][e.second].second = -1;
      st.emplace(e.first.to, e.first);
    }
  }
  ord.pop_back();
  reverse(begin(ord), end(ord));
  if(ord.size() != es.size()) return {};
  return ord;
}


##################################################
################### dinic.cpp ####################
##################################################

template< typename flow_t >
struct Dinic {
  const flow_t INF;

  struct edge {
    int to;
    flow_t cap;
    int rev;
    bool isrev;
    int idx;
  };

  vector< vector< edge > > graph;
  vector< int > min_cost, iter;

  Dinic(int V) : INF(numeric_limits< flow_t >::max()), graph(V) {}

  void add_edge(int from, int to, flow_t cap, int idx = -1) {
    graph[from].emplace_back((edge) {to, cap, (int) graph[to].size(), false, idx});
    graph[to].emplace_back((edge) {from, 0, (int) graph[from].size() - 1, true, idx});
  }

  bool bfs(int s, int t) {
    min_cost.assign(graph.size(), -1);
    queue< int > que;
    min_cost[s] = 0;
    que.push(s);
    while(!que.empty() && min_cost[t] == -1) {
      int p = que.front();
      que.pop();
      for(auto &e : graph[p]) {
        if(e.cap > 0 && min_cost[e.to] == -1) {
          min_cost[e.to] = min_cost[p] + 1;
          que.push(e.to);
        }
      }
    }
    return min_cost[t] != -1;
  }

  flow_t dfs(int idx, const int t, flow_t flow) {
    if(idx == t) return flow;
    for(int &i = iter[idx]; i < graph[idx].size(); i++) {
      edge &e = graph[idx][i];
      if(e.cap > 0 && min_cost[idx] < min_cost[e.to]) {
        flow_t d = dfs(e.to, t, min(flow, e.cap));
        if(d > 0) {
          e.cap -= d;
          graph[e.to][e.rev].cap += d;
          return d;
        }
      }
    }
    return 0;
  }

  flow_t max_flow(int s, int t) {
    flow_t flow = 0;
    while(bfs(s, t)) {
      iter.assign(graph.size(), 0);
      flow_t f = 0;
      while((f = dfs(s, t, INF)) > 0) flow += f;
    }
    return flow;
  }

  void output() {
    for(int i = 0; i < graph.size(); i++) {
      for(auto &e : graph[i]) {
        if(e.isrev) continue;
        auto &rev_e = graph[e.to][e.rev];
        cout << i << "->" << e.to << " (flow: " << rev_e.cap << "/" << e.cap + rev_e.cap << ")" << endl;
      }
    }
  }
};


##################################################
############## topological-sort.cpp ##############
##################################################

template< typename G >
vector< int > topological_sort(const G &g) {
  const int N = (int) g.size();
  vector< int > deg(N);
  for(int i = 0; i < N; i++) {
    for(auto &to : g[i]) ++deg[to];
  }
  stack< int > st;
  for(int i = 0; i < N; i++) {
    if(deg[i] == 0) st.emplace(i);
  }
  vector< int > ord;
  while(!st.empty()) {
    auto p = st.top();
    st.pop();
    ord.emplace_back(p);
    for(auto &to : g[p]) {
      if(--deg[to] == 0) st.emplace(to);
    }
  }
  return ord;
}


##################################################
############### chu-liu-edmond.cpp ###############
##################################################

template< typename T >
struct MinimumSpanningTreeArborescence
{
  using Pi = pair< T, int >;
  using Heap = SkewHeap< Pi, int >;
  using Node = typename Heap::Node;
  const Edges< T > &es;
  const int V;
  T INF;
 
  MinimumSpanningTreeArborescence(const Edges< T > &es, int V) :
      INF(numeric_limits< T >::max()), es(es), V(V) {}
 
  T build(int start)
  {
    auto g = [](const Pi &a, const T &b) { return Pi(a.first + b, a.second); };
    auto h = [](const T &a, const T &b) { return a + b; };
    Heap heap(g, h);
    vector< Node * > heaps(V, heap.makeheap());
    for(auto &e : es) heap.push(heaps[e.to], {e.cost, e.src});
    UnionFind uf(V);
    vector< int > used(V, -1);
    used[start] = start;
 
    T ret = 0;
    for(int s = 0; s < V; s++) {
      stack< int > path;
      for(int u = s; used[u] < 0;) {
        path.push(u);
        used[u] = s;
        if(heap.empty(heaps[u])) return -1;
        auto p = heap.top(heaps[u]);
        ret += p.first;
        heap.add(heaps[u], -p.first);
        heap.pop(heaps[u]);
        int v = uf.find(p.second);
        if(used[v] == s) {
          int w;
          Node *nextheap = heap.makeheap();
          do {
            w = path.top();
            path.pop();
            nextheap = heap.merge(nextheap, heaps[w]);
          } while(uf.unite(v, w));
          heaps[uf.find(v)] = nextheap;
          used[uf.find(v)] = -1;
        }
        u = uf.find(v);
      }
    }
    return ret;
  }
};


##################################################
####### shortest-path-faster-algorithm.cpp #######
##################################################

template< typename T >
vector< T > shortest_path_faster_algorithm(WeightedGraph< T > &g, int s) {
  const auto INF = numeric_limits< T >::max();
  vector< T > dist(g.size(), INF);
  vector< int > pending(g.size(), 0), times(g.size(), 0);
  queue< int > que;

  que.emplace(s);
  pending[s] = true;
  ++times[s];
  dist[s] = 0;

  while(!que.empty()) {
    int p = que.front();
    que.pop();
    pending[p] = false;
    for(auto &e : g[p]) {
      T next_cost = dist[p] + e.cost;
      if(next_cost >= dist[e.to]) continue;
      dist[e.to] = next_cost;
      if(!pending[e.to]) {
        if(++times[e.to] >= g.size()) return vector< T >();
        pending[e.to] = true;
        que.emplace(e.to);
      }
    }
  }
  return dist;
}


##################################################
############### hopcroft-karp.cpp ################
##################################################

struct HopcroftKarp {
  vector< vector< int > > graph;
  vector< int > dist, match;
  vector< bool > used, vv;

  HopcroftKarp(int n, int m) : graph(n), match(m, -1), used(n) {}

  void add_edge(int u, int v) {
    graph[u].push_back(v);
  }

  void bfs() {
    dist.assign(graph.size(), -1);
    queue< int > que;
    for(int i = 0; i < graph.size(); i++) {
      if(!used[i]) {
        que.emplace(i);
        dist[i] = 0;
      }
    }

    while(!que.empty()) {
      int a = que.front();
      que.pop();
      for(auto &b : graph[a]) {
        int c = match[b];
        if(c >= 0 && dist[c] == -1) {
          dist[c] = dist[a] + 1;
          que.emplace(c);
        }
      }
    }
  }

  bool dfs(int a) {
    vv[a] = true;
    for(auto &b : graph[a]) {
      int c = match[b];
      if(c < 0 || (!vv[c] && dist[c] == dist[a] + 1 && dfs(c))) {
        match[b] = a;
        used[a] = true;
        return (true);
      }
    }
    return (false);
  }

  int bipartite_matching() {
    int ret = 0;
    while(true) {
      bfs();
      vv.assign(graph.size(), false);
      int flow = 0;
      for(int i = 0; i < graph.size(); i++) {
        if(!used[i] && dfs(i)) ++flow;
      }
      if(flow == 0) return (ret);
      ret += flow;
    }
  }

  void output() {
    for(int i = 0; i < match.size(); i++) {
      if(~match[i]) {
        cout << match[i] << "-" << i << endl;
      }
    }
  }
};


##################################################
################## lowlink.cpp ###################
##################################################

template< typename G >
struct LowLink {
  const G &g;
  vector< int > used, ord, low;
  vector< int > articulation;
  vector< pair< int, int > > bridge;
 
  LowLink(const G &g) : g(g) {}
 
  int dfs(int idx, int k, int par) {
    used[idx] = true;
    ord[idx] = k++;
    low[idx] = ord[idx];
    bool is_articulation = false;
    int cnt = 0;
    for(auto &to : g[idx]) {
      if(!used[to]) {
        ++cnt;
        k = dfs(to, k, idx);
        low[idx] = min(low[idx], low[to]);
        is_articulation |= ~par && low[to] >= ord[idx];
        if(ord[idx] < low[to]) bridge.emplace_back(minmax(idx, (int) to));
      } else if(to != par) {
        low[idx] = min(low[idx], ord[to]);
      }
    }
    is_articulation |= par == -1 && cnt > 1;
    if(is_articulation) articulation.push_back(idx);
    return k;
  }
 
  virtual void build() {
    used.assign(g.size(), 0);
    ord.assign(g.size(), 0);
    low.assign(g.size(), 0);
    int k = 0;
    for(int i = 0; i < g.size(); i++) {
      if(!used[i]) k = dfs(i, k, -1);
    }
  }
};


##################################################
############### maximum-clique.cpp ###############
##################################################

template< typename T >
T maximum_clique(Matrix< bool > g, function< T(vector< int >) > f) {

  int N = (int) g.size(), M = 0;
  vector< int > deg(N), v(N);
  for(int i = 0; i < N; i++) {
    for(int j = 0; j < i; j++) {
      assert(g[i][j] == g[j][i]);
      if(g[i][j]) {
        ++deg[i];
        ++M;
      }
    }
  }
  T t = 0;
  int lim = (int) sqrt(2 * M);

  for(int i = 0; i < N; i++) {
    vector< int > notice;
    for(int j = 0; j < N; j++) {
      if(!v[j] && deg[j] < lim) {
        for(int k = 0; k < N; k++) {
          if(j == k) continue;
          if(g[j][k]) notice.emplace_back(k);
        }
        notice.emplace_back(j);
        break;
      }
    }
    if(notice.empty()) break;
    int neighbor = (int) notice.size() - 1;
    vector< int > bit(neighbor);
    for(int j = 0; j < neighbor; j++) {
      for(int k = 0; k < j; k++) {
        if(!g[notice[j]][notice[k]]) {
          bit[j] |= 1 << k;
          bit[k] |= 1 << j;
        }
      }
    }
    for(int j = 0; j < (1 << neighbor); j++) {
      bool ok = true;
      for(int k = 0; k < neighbor; k++) {
        if((j >> k) & 1) ok &= (j & bit[k]) == 0;
      }
      if(ok) {
        vector< int > stock{notice.back()};
        for(int k = 0; k < neighbor; k++) {
          if((j >> k) & 1) stock.emplace_back(notice[k]);
        }
        t = max(t, f(stock));
      }
    }
    v[notice.back()] = true;
    for(int j = 0; j < N; j++) {
      if(g[j][notice.back()]) {
        --deg[j];
        g[notice.back()][j] = g[j][notice.back()] = false;
      }
    }
  }

  vector< int > notice;
  for(int j = 0; j < N; j++) {
    if(!v[j]) notice.emplace_back(j);
  }
  int neighbor = (int) notice.size();
  vector< int > bit(neighbor);
  for(int j = 0; j < neighbor; j++) {
    for(int k = 0; k < j; k++) {
      if(!g[notice[j]][notice[k]]) {
        bit[j] |= 1 << k;
        bit[k] |= 1 << j;
      }
    }
  }
  for(int j = 0; j < (1 << neighbor); j++) {
    bool ok = true;
    for(int k = 0; k < neighbor; k++) {
      if((j >> k) & 1) ok &= (j & bit[k]) == 0;
    }
    if(ok) {
      vector< int > stock;
      for(int k = 0; k < neighbor; k++) {
        if((j >> k) & 1) stock.emplace_back(notice[k]);
      }
      t = max(t, f(stock));
    }
  }
  return t;
}



--------------------------------------------------
|                     other                      |
--------------------------------------------------

##################################################
##################### mo.cpp #####################
##################################################

struct Mo {
  using ADD = function< void(int) >;
  using DEL = function< void(int) >;
  using REM = function< void(int) >;

  int width;
  vector< int > left, right, order;
  vector< bool > v;

  Mo(int N, int Q) : width((int) sqrt(N)), order(Q), v(N) {
    iota(begin(order), end(order), 0);
  }

  void add(int l, int r) { /* [l, r) */
    left.emplace_back(l);
    right.emplace_back(r);
  }

  int run(const ADD &add, const DEL &del, const REM &rem) {
    assert(left.size() == order.size());
    sort(begin(order), end(order), [&](int a, int b) {
      int ablock = left[a] / width, bblock = left[b] / width;
      if(ablock != bblock) return ablock < bblock;
      if(ablock & 1) return right[a] < right[b];
      return right[a] > right[b];
    });
    int nl = 0, nr = 0;
    auto push = [&](int idx) {
      v[idx].flip();
      if(v[idx]) add(idx);
      else del(idx);
    };
    for(auto idx : order) {
      while(nl > left[idx]) push(--nl);
      while(nr < right[idx]) push(nr++);
      while(nl < left[idx]) push(nl++);
      while(nr > right[idx]) push(--nr);
      rem(idx);
    }
  }
};


##################################################
#################### dice.cpp ####################
##################################################

struct Dice
{
  // int x, y;
  int l, r, f, b, d, u;

  void RollN()
  {
    //  --y;
    int buff = d;
    d = f;
    f = u;
    u = b;
    b = buff;
  }

  void RollS()
  {
    // ++y;
    int buff = d;
    d = b;
    b = u;
    u = f;
    f = buff;
  }

  void RollL() // ----->
  {
    int buff = f;
    f = l;
    l = b;
    b = r;
    r = buff;
  }

  void RollR() // <------
  {
    int buff = f;
    f = r;
    r = b;
    b = l;
    l = buff;
  }

  void RollE() // .o -> o.
  {
    // --x;
    int buff = d;
    d = l;
    l = u;
    u = r;
    r = buff;
  }


  void RollW() // o. -> .o
  {
    //  ++x;
    int buff = d;
    d = r;
    r = u;
    u = l;
    l = buff;
  }


  vector< Dice > makeDice()
  {
    vector< Dice > ret;
    for(int i = 0; i < 6; i++) {
      Dice d(*this);
      if(i == 1) d.RollN();
      if(i == 2) d.RollS();
      if(i == 3) d.RollS(), d.RollS();
      if(i == 4) d.RollL();
      if(i == 5) d.RollR();
      for(int j = 0; j < 4; j++) {
        ret.emplace_back(d);
        d.RollE();
      }
    }
    return (ret);
  }
};


##################################################
################### timer.cpp ####################
##################################################

struct Timer {
  chrono::high_resolution_clock::time_point st;

  Timer() { reset(); }

  void reset() {
    st = chrono::high_resolution_clock::now();
  }

  chrono::milliseconds::rep elapsed() {
    auto ed = chrono::high_resolution_clock::now();
    return chrono::duration_cast< chrono::milliseconds >(ed - st).count();
  }
};


##################################################
################# fast-input.cpp #################
##################################################

template< int sz >
struct FastInput {
  char buf[sz + 1];
  char *o;

  FastInput() { init(); }

  void init() {
    o = buf;
    buf[fread(buf, sizeof(char), sizeof(char) * sz, stdin)] = '\0';
  }

  int64_t read() {
    int64_t ret = 0, sign = 1;
    while(*o && *o <= 32) ++o;
    if(*o == '-') sign *= -1, ++o;
    while(*o >= '0' && *o <= '9') {
      ret *= 10;
      ret += *o++ - '0';
    }
    return ret * sign;
  }
};


##################################################
######## offline-dynamic-connectivity.cpp ########
##################################################

struct OfflineDynamicConnectivity {
  using edge = pair< int, int >;

  UnionFindUndo uf;
  int V, Q, segsz;
  vector< vector< edge > > seg;
  int comp;

  vector< pair< pair< int, int >, edge > > pend;
  map< edge, int > cnt, appear;

  OfflineDynamicConnectivity(int V, int Q) : uf(V), V(V), Q(Q), comp(V) {
    segsz = 1;
    while(segsz < Q) segsz <<= 1;
    seg.resize(2 * segsz - 1);
  }

  void insert(int idx, int s, int t) {
    auto e = minmax(s, t);
    if(cnt[e]++ == 0) appear[e] = idx;
  }

  void erase(int idx, int s, int t) {
    auto e = minmax(s, t);
    if(--cnt[e] == 0) pend.emplace_back(make_pair(appear[e], idx), e);
  }

  void add(int a, int b, const edge &e, int k, int l, int r) {
    if(r <= a || b <= l) return;
    if(a <= l && r <= b) {
      seg[k].emplace_back(e);
      return;
    }
    add(a, b, e, 2 * k + 1, l, (l + r) >> 1);
    add(a, b, e, 2 * k + 2, (l + r) >> 1, r);
  }

  void add(int a, int b, const edge &e) {
    add(a, b, e, 0, 0, segsz);
  }

  void build() {
    for(auto &p : cnt) {
      if(p.second > 0) pend.emplace_back(make_pair(appear[p.first], Q), p.first);
    }
    for(auto &s : pend) {
      add(s.first.first, s.first.second, s.second);
    }
  }

  int run(const function< void(int) > &f, int k = 0) {
    int add = 0;
    for(auto &e : seg[k]) {
      add += uf.unite(e.first, e.second);
    }
    comp -= add;
    if(k < segsz - 1) {
      run(f, 2 * k + 1);
      run(f, 2 * k + 2);
    } else if(k - (segsz - 1) < Q) {
      int query_index = k - (segsz - 1);
      f(query_index);
    }
    for(auto &e : seg[k]) {
      uf.undo();
    }
    comp += add;
  }
};


##################################################
########## random-number-generator.cpp ###########
##################################################

struct RandomNumberGenerator {
  mt19937 mt;

  RandomNumberGenerator() : mt(chrono::steady_clock::now().time_since_epoch().count()) {}

  int operator()(int a, int b) { // [a, b)
    uniform_int_distribution< int > dist(a, b - 1);
    return dist(mt);
  }

  int operator()(int b) { // [0, b)
    return (*this)(0, b);
  }
};


##################################################
################ mo-rollback.cpp #################
##################################################

struct MoRollBack {
  using ADD = function< void(int) >;
  using REM = function< void(int) >;
  using RESET = function< void() >;
  using SNAPSHOT = function< void() >;
  using ROLLBACK = function< void() >;

  int width;
  vector< int > left, right, order;

  MoRollBack(int N, int Q) : width((int) sqrt(N)), order(Q) {
    iota(begin(order), end(order), 0);
  }

  void add(int l, int r) { /* [l, r) */
    left.emplace_back(l);
    right.emplace_back(r);
  }

  int run(const ADD &add, const REM &rem, const RESET &reset, const SNAPSHOT &snapshot, const ROLLBACK &rollback) {
    assert(left.size() == order.size());
    sort(begin(order), end(order), [&](int a, int b) {
      int ablock = left[a] / width, bblock = left[b] / width;
      if(ablock != bblock) return ablock < bblock;
      return right[a] < right[b];
    });
    reset();
    for(auto idx : order) {
      if(right[idx] - left[idx] < width) {
        for(int i = left[idx]; i < right[idx]; i++) add(i);
        rem(idx);
        rollback();
      }
    }
    int nr = 0, last_block = -1;
    for(auto idx : order) {
      if(right[idx] - left[idx] < width) continue;
      int block = left[idx] / width;
      if(last_block != block) {
        reset();
        last_block = block;
        nr = (block + 1) * width;
      }
      while(nr < right[idx]) add(nr++);
      snapshot();
      for(int j = (block + 1) * width - 1; j >= left[idx]; j--) add(j);
      rem(idx);
      rollback();
    }
  }
};



##################################################
################## compress.cpp ##################
##################################################

template< typename T >
struct Compress {
  vector< T > xs;

  Compress() = default;

  Compress(const vector< T > &vs) {
    add(vs);
  }

  Compress(const initializer_list< vector< T > > &vs) {
    for(auto &p : vs) add(p);
  }

  void add(const vector< T > &vs) {
    copy(begin(vs), end(vs), back_inserter(xs));
  }

  void add(const T &x) {
    xs.emplace_back(x);
  }

  void build() {
    sort(begin(xs), end(xs));
    xs.erase(unique(begin(xs), end(xs)), end(xs));
  }

  vector< int > get(const vector< T > &vs) const {
    vector< int > ret;
    transform(begin(vs), end(vs), back_inserter(ret), [&](const T &x) {
      return lower_bound(begin(xs), end(xs), x) - begin(xs);
    });
    return ret;
  }

  int get(const T &x) const {
    return lower_bound(begin(xs), end(xs), x) - begin(xs);
  }

  const T &operator[](int k) const {
    return xs[k];
  }
};


--------------------------------------------------
|                    template                    |
--------------------------------------------------

##################################################
################## template.cpp ##################
##################################################

#include<bits/stdc++.h>

using namespace std;

using int64 = long long;
const int mod = 1e9 + 7;

const int64 infll = (1LL << 62) - 1;
const int inf = (1 << 30) - 1;

struct IoSetup {
  IoSetup() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    cout << fixed << setprecision(10);
    cerr << fixed << setprecision(10);
  }
} iosetup;


template< typename T1, typename T2 >
ostream &operator<<(ostream &os, const pair< T1, T2 >& p) {
  os << p.first << " " << p.second;
  return os;
}

template< typename T1, typename T2 >
istream &operator>>(istream &is, pair< T1, T2 > &p) {
  is >> p.first >> p.second;
  return is;
}

template< typename T >
ostream &operator<<(ostream &os, const vector< T > &v) {
  for(int i = 0; i < (int) v.size(); i++) {
    os << v[i] << (i + 1 != v.size() ? " " : "");
  }
  return os;
}

template< typename T >
istream &operator>>(istream &is, vector< T > &v) {
  for(T &in : v) is >> in;
  return is;
}

template< typename T1, typename T2 >
inline bool chmax(T1 &a, T2 b) { return a < b && (a = b, true); }

template< typename T1, typename T2 >
inline bool chmin(T1 &a, T2 b) { return a > b && (a = b, true); }

template< typename T = int64 >
vector< T > make_v(size_t a) {
  return vector< T >(a);
}

template< typename T, typename... Ts >
auto make_v(size_t a, Ts... ts) {
  return vector< decltype(make_v< T >(ts...)) >(a, make_v< T >(ts...));
}

template< typename T, typename V >
typename enable_if< is_class< T >::value == 0 >::type fill_v(T &t, const V &v) {
  t = v;
}

template< typename T, typename V >
typename enable_if< is_class< T >::value != 0 >::type fill_v(T &t, const V &v) {
  for(auto &e : t) fill_v(e, v);
}

template< typename F >
struct FixPoint : F {
  FixPoint(F &&f) : F(forward< F >(f)) {}
 
  template< typename... Args >
  decltype(auto) operator()(Args &&... args) const {
    return F::operator()(*this, forward< Args >(args)...);
  }
};
 
template< typename F >
inline decltype(auto) MFP(F &&f) {
  return FixPoint< F >{forward< F >(f)};
}


--------------------------------------------------
|                      math                      |
--------------------------------------------------

##################################################
################ prime-factor.cpp ################
##################################################

map< int64_t, int > prime_factor(int64_t n) {
  map< int64_t, int > ret;
  for(int64_t i = 2; i * i <= n; i++) {
    while(n % i == 0) {
      ret[i]++;
      n /= i;
    }
  }
  if(n != 1) ret[n] = 1;
  return ret;
}


##################################################
########### stirling-number-second.cpp ###########
##################################################

template< typename T >
T stirling_number_second(int n, int k) {
  Combination< T > table(k);
  T ret = 0;
  for(int i = 0; i <= k; i++) {
    auto add = T(i).pow(n) * table.C(k, i);
    if((k - i) & 1) ret -= add;
    else ret += add;
  }
  return ret * table.rfact(k);
}



##################################################
################## mod-int.cpp ###################
##################################################

template< int mod >
struct ModInt {
  int x;

  ModInt() : x(0) {}

  ModInt(int64_t y) : x(y >= 0 ? y % mod : (mod - (-y) % mod) % mod) {}

  ModInt &operator+=(const ModInt &p) {
    if((x += p.x) >= mod) x -= mod;
    return *this;
  }

  ModInt &operator-=(const ModInt &p) {
    if((x += mod - p.x) >= mod) x -= mod;
    return *this;
  }

  ModInt &operator*=(const ModInt &p) {
    x = (int) (1LL * x * p.x % mod);
    return *this;
  }

  ModInt &operator/=(const ModInt &p) {
    *this *= p.inverse();
    return *this;
  }

  ModInt operator-() const { return ModInt(-x); }

  ModInt operator+(const ModInt &p) const { return ModInt(*this) += p; }

  ModInt operator-(const ModInt &p) const { return ModInt(*this) -= p; }

  ModInt operator*(const ModInt &p) const { return ModInt(*this) *= p; }

  ModInt operator/(const ModInt &p) const { return ModInt(*this) /= p; }

  bool operator==(const ModInt &p) const { return x == p.x; }

  bool operator!=(const ModInt &p) const { return x != p.x; }

  ModInt inverse() const {
    int a = x, b = mod, u = 1, v = 0, t;
    while(b > 0) {
      t = a / b;
      swap(a -= t * b, b);
      swap(u -= t * v, v);
    }
    return ModInt(u);
  }

  ModInt pow(int64_t n) const {
    ModInt ret(1), mul(x);
    while(n > 0) {
      if(n & 1) ret *= mul;
      mul *= mul;
      n >>= 1;
    }
    return ret;
  }

  friend ostream &operator<<(ostream &os, const ModInt &p) {
    return os << p.x;
  }

  friend istream &operator>>(istream &is, ModInt &a) {
    int64_t t;
    is >> t;
    a = ModInt< mod >(t);
    return (is);
  }

  static int get_mod() { return mod; }
};

using modint = ModInt< mod >;


##################################################
################## binomial.cpp ##################
##################################################

template< typename T >
T binomial(int64_t N, int64_t K) {
  if(K < 0 || N < K) return 0;
  T ret = 1;
  for(T i = 1; i <= K; ++i) {
    ret *= N--;
    ret /= i;
  }
  return ret;
}


##################################################
################# factorial.cpp ##################
##################################################

template< typename T >
T factorial(int64_t n) {
  if(n >= T::get_mod()) return 0;
  if(n == 0) return 1;

  const int64_t sn = sqrt(n);
  const T sn_inv = T(1) / sn;

  Combination< modint > comb(sn);
  using P = vector< T >;

  ArbitraryModConvolution< T > fft;
  using FPS = FormalPowerSeries< T >;
  auto mult = [&](const typename FPS::P &a, const typename FPS::P &b) {
    auto ret = fft.multiply(a, b);
    return typename FPS::P(ret.begin(), ret.end());
  };
  FPS::set_fft(mult);


  auto shift = [&](const P &f, T dx) {
    int n = (int) f.size();
    T a = dx * sn_inv;
    auto p1 = P(f);
    for(int i = 0; i < n; i++) {
      T d = comb.rfact(i) * comb.rfact((n - 1) - i);
      if(((n - 1 - i) & 1)) d = -d;
      p1[i] *= d;
    }
    auto p2 = P(2 * n);
    for(int i = 0; i < p2.size(); i++) {
      p2[i] = (a.x + i - n) <= 0 ? 1 : a + i - n;
    }
    for(int i = 1; i < p2.size(); i++) {
      p2[i] *= p2[i - 1];
    }
    T prod = p2[2 * n - 1];
    T prod_inv = T(1) / prod;
    for(int i = 2 * n - 1; i > 0; --i) {
      p2[i] = prod_inv * p2[i - 1];
      prod_inv *= a + i - n;
    }
    p2[0] = prod_inv;
    auto p3 = fft.multiply(p1, p2, (int) p2.size());
    p1 = P(p3.begin() + p1.size(), p3.begin() + p2.size());
    prod = 1;
    for(int i = 0; i < n; i++) {
      prod *= a + n - 1 - i;
    }
    for(int i = n - 1; i >= 0; --i) {
      p1[i] *= prod;
      prod *= p2[n + i] * (a + i - n);
    }
    return p1;
  };
  function< P(int) > rec = [&](int64_t n) {
    if(n == 1) return P({1, 1 + sn});
    int64_t nh = n >> 1;
    auto a1 = rec(nh);
    auto a2 = shift(a1, nh);
    auto b1 = shift(a1, sn * nh);
    auto b2 = shift(a1, sn * nh + nh);
    for(int i = 0; i <= nh; i++) a1[i] *= a2[i];
    for(int i = 1; i <= nh; i++) a1.emplace_back(b1[i] * b2[i]);
    if(n & 1) {
      for(int64_t i = 0; i < n; i++) {
        a1[i] *= n + 1LL * sn * i;
      }
      T prod = 1;
      for(int64_t i = 1LL * n * sn; i < 1LL * n * sn + n; i++) {
        prod *= (i + 1);
      }
      a1.push_back(prod);
    }
    return a1;
  };
  auto vs = rec(sn);
  T ret = 1;
  for(int64_t i = 0; i < sn; i++) ret *= vs[i];
  for(int64_t i = 1LL * sn * sn + 1; i <= n; i++) ret *= i;
  return ret;
}


##################################################
############### binomial-table.cpp ###############
##################################################

template< typename T >
vector< vector< T > > binomial_table(int N) {
  vector< vector< T > > mat(N + 1, vector< T >(N + 1));
  for(int i = 0; i <= N; i++) {
    for(int j = 0; j <= i; j++) {
      if(j == 0 || j == i) mat[i][j] = 1;
      else mat[i][j] = mat[i - 1][j - 1] + mat[i - 1][j];
    }
  }
  return mat;
}


##################################################
########## polynomial-interpolation.cpp ##########
##################################################

template< class T >
FormalPowerSeries< T > polynomial_interpolation(const FormalPowerSeries< T > &xs, const vector< T > &ys) {
  assert(xs.size() == ys.size());
  using FPS = FormalPowerSeries< T >;
  PolyBuf< T > buf(xs);
  FPS w = buf.query(0, xs.size()).diff();
  auto vs = multipoint_evaluation(w, xs, buf);
  function< FPS(int, int) > rec = [&](int l, int r) -> FPS {
    if(r - l == 1) return {ys[l] / vs[l]};
    int m = (l + r) >> 1;
    return rec(l, m) * buf.query(m, r) + rec(m, r) * buf.query(l, m);
  };
  return rec(0, xs.size());
}


##################################################
################ bell-number.cpp #################
##################################################

template< typename T >
T bell_number(int n, int k) {
  if(n == 0) return 1;
  k = min(k, n);
  Combination< T > uku(k);
  T ret = 0;
  vector< T > pref(k + 1);
  pref[0] = 1;
  for(int i = 1; i <= k; i++) {
    if(i & 1) pref[i] = pref[i - 1] - uku.rfact(i);
    else pref[i] = pref[i - 1] + uku.rfact(i);
  }
  for(int i = 1; i <= k; i++) {
    ret += T(i).pow(n) * uku.rfact(i) * pref[k - i];
  }
  return ret;
}


##################################################
################## divisor.cpp ###################
##################################################

vector< int64_t > divisor(int64_t n) {
  vector< int64_t > ret;
  for(int64_t i = 1; i * i <= n; i++) {
    if(n % i == 0) {
      ret.push_back(i);
      if(i * i != n) ret.push_back(n / i);
    }
  }
  sort(begin(ret), end(ret));
  return (ret);
}


##################################################
####### arbitrary-mod-convolution-long.cpp #######
##################################################

template< typename T >
struct ArbitraryModConvolutionLong {
  using real = FastFourierTransform::real;
  using C = FastFourierTransform::C;
 
  ArbitraryModConvolutionLong() = default;
 
  vector< T > multiply(const vector< T > &a, const vector< T > &b, int need = -1) {
    if(need == -1) need = a.size() + b.size() - 1;
    int nbase = 0;
    while((1 << nbase) < need) nbase++;
    FastFourierTransform::ensure_base(nbase);
    int sz = 1 << nbase;
    vector< C > fa(sz);
    for(int i = 0; i < a.size(); i++) {
      fa[i] = C(a[i].x & ((1 << 19) - 1), a[i].x >> 19);
    }
    fft(fa, sz);
    vector< C > fb(sz);
    if(a == b) {
      fb = fa;
    } else {
      for(int i = 0; i < b.size(); i++) {
        fb[i] = C(b[i].x & ((1 << 19) - 1), b[i].x >> 19);
      }
      fft(fb, sz);
    }
    real ratio = 0.25 / sz;
    C r2(0, -1), r3(ratio, 0), r4(0, -ratio), r5(0, 1);
    for(int i = 0; i <= (sz >> 1); i++) {
      int j = (sz - i) & (sz - 1);
      C a1 = (fa[i] + fa[j].conj());
      C a2 = (fa[i] - fa[j].conj()) * r2;
      C b1 = (fb[i] + fb[j].conj()) * r3;
      C b2 = (fb[i] - fb[j].conj()) * r4;
      if(i != j) {
        C c1 = (fa[j] + fa[i].conj());
        C c2 = (fa[j] - fa[i].conj()) * r2;
        C d1 = (fb[j] + fb[i].conj()) * r3;
        C d2 = (fb[j] - fb[i].conj()) * r4;
        fa[i] = c1 * d1 + c2 * d2 * r5;
        fb[i] = c1 * d2 + c2 * d1;
      }
      fa[j] = a1 * b1 + a2 * b2 * r5;
      fb[j] = a1 * b2 + a2 * b1;
    }
    fft(fa, sz);
    fft(fb, sz);
    vector< T > ret(need);
    auto mul1 = T(2).pow(19);
    auto mul2 = T(2).pow(38);
    for(int i = 0; i < need; i++) {
      int64_t aa = llround(fa[i].x);
      int64_t bb = llround(fb[i].x);
      int64_t cc = llround(fa[i].y);
      aa = T(aa).x, bb = T(bb).x, cc = T(cc).x;
      ret[i] = (mul1 * bb) + (mul2 * cc) + aa;
    }
    return ret;
  }
};


##################################################
################## mod-pow.cpp ###################
##################################################

template< typename T >
T mod_pow(T x, T n, const T &p) {
  T ret = 1;
  while(n > 0) {
    if(n & 1) (ret *= x) %= p;
    (x *= x) %= p;
    n >>= 1;
  }
  return ret;
}



##################################################
################ prime-table.cpp #################
##################################################

vector< bool > prime_table(int n) {
  vector< bool > prime(n + 1, true);
  if(n >= 0) prime[0] = false;
  if(n >= 1) prime[1] = false;
  for(int i = 2; i * i <= n; i++) {
    if(!prime[i]) continue;
    for(int j = i + i; j <= n; j += i) {
      prime[j] = false;
    }
  }
  return prime;
}


##################################################
########### multipoint-evaluation.cpp ############
##################################################

template< typename T >
struct PolyBuf {
  using FPS = FormalPowerSeries< T >;
  const FPS xs;
  using pi = pair< int, int >;
  map< pi, FPS > buf;

  PolyBuf(const FPS &xs) : xs(xs) {}

  const FPS &query(int l, int r) {
    if(buf.count({l, r})) return buf[{l, r}];
    if(l + 1 == r) return buf[{l, r}] = {-xs[l], 1};
    return buf[{l, r}] = query(l, (l + r) >> 1) * query((l + r) >> 1, r);
  }
};


template< typename T >
FormalPowerSeries< T > multipoint_evaluation(const FormalPowerSeries< T > &as, const FormalPowerSeries< T > &xs, PolyBuf< T > &buf) {
  using FPS = FormalPowerSeries< T >;
  FPS ret;
  const int B = 64;
  function< void(FPS, int, int) > rec = [&](FPS a, int l, int r) -> void {
    a %= buf.query(l, r);
    if(a.size() <= B) {
      for(int i = l; i < r; i++) ret.emplace_back(a.eval(xs[i]));
      return;
    }
    rec(a, l, (l + r) >> 1);
    rec(a, (l + r) >> 1, r);
  };
  rec(as, 0, xs.size());
  return ret;
};

template< typename T >
FormalPowerSeries< T > multipoint_evaluation(const FormalPowerSeries< T > &as, const FormalPowerSeries< T > &xs) {
  PolyBuf< T > buff(xs);
  return multipoint_evaluation(as, xs, buff);
}



##################################################
################## mod-sqrt.cpp ##################
##################################################

template< typename T >
T mod_sqrt(const T &a, const T &p) {
  if(a == 0) return 0;
  if(p == 2) return a;
  if(mod_pow(a, (p - 1) >> 1, p) != 1) return -1;
  T b = 1;
  while(mod_pow(b, (p - 1) >> 1, p) == 1) ++b;
  T e = 0, m = p - 1;
  while(m % 2 == 0) m >>= 1, ++e;
  T x = mod_pow(a, (m - 1) >> 1, p);
  T y = a * (x * x % p) % p;
  (x *= a) %= p;
  T z = mod_pow(b, m, p);
  while(y != 1) {
    T j = 0, t = y;
    while(t != 1) {
      j += 1;
      (t *= t) %= p;
    }
    z = mod_pow(z, T(1) << (e - j - 1), p);
    (x *= z) %= p;
    (z *= z) %= p;
    (y *= z) %= p;
    e = j;
  }
  return x;
}


##################################################
######### arbitrary-mod-convolution.cpp ##########
##################################################

template< typename T >
struct ArbitraryModConvolution {
  using real = FastFourierTransform::real;
  using C = FastFourierTransform::C;

  ArbitraryModConvolution() = default;

  vector< T > multiply(const vector< T > &a, const vector< T > &b, int need = -1) {
    if(need == -1) need = a.size() + b.size() - 1;
    int nbase = 0;
    while((1 << nbase) < need) nbase++;
    FastFourierTransform::ensure_base(nbase);
    int sz = 1 << nbase;
    vector< C > fa(sz);
    for(int i = 0; i < a.size(); i++) {
      fa[i] = C(a[i].x & ((1 << 15) - 1), a[i].x >> 15);
    }
    fft(fa, sz);
    vector< C > fb(sz);
    if(a == b) {
      fb = fa;
    } else {
      for(int i = 0; i < b.size(); i++) {
        fb[i] = C(b[i].x & ((1 << 15) - 1), b[i].x >> 15);
      }
      fft(fb, sz);
    }
    real ratio = 0.25 / sz;
    C r2(0, -1), r3(ratio, 0), r4(0, -ratio), r5(0, 1);
    for(int i = 0; i <= (sz >> 1); i++) {
      int j = (sz - i) & (sz - 1);
      C a1 = (fa[i] + fa[j].conj());
      C a2 = (fa[i] - fa[j].conj()) * r2;
      C b1 = (fb[i] + fb[j].conj()) * r3;
      C b2 = (fb[i] - fb[j].conj()) * r4;
      if(i != j) {
        C c1 = (fa[j] + fa[i].conj());
        C c2 = (fa[j] - fa[i].conj()) * r2;
        C d1 = (fb[j] + fb[i].conj()) * r3;
        C d2 = (fb[j] - fb[i].conj()) * r4;
        fa[i] = c1 * d1 + c2 * d2 * r5;
        fb[i] = c1 * d2 + c2 * d1;
      }
      fa[j] = a1 * b1 + a2 * b2 * r5;
      fb[j] = a1 * b2 + a2 * b1;
    }
    fft(fa, sz);
    fft(fb, sz);
    vector< T > ret(need);
    for(int i = 0; i < need; i++) {
      int64_t aa = llround(fa[i].x);
      int64_t bb = llround(fb[i].x);
      int64_t cc = llround(fa[i].y);
      aa = T(aa).x, bb = T(bb).x, cc = T(cc).x;
      ret[i] = aa + (bb << 15) + (cc << 30);
    }
    return ret;
  }
};


##################################################
 number-theoretic-transform-friendly-mod-int.cpp #
##################################################

template< typename Mint >
struct NumberTheoreticTransformFriendlyModInt {

  vector< int > rev;
  vector< Mint > rts;
  int base, max_base;
  Mint root;

  NumberTheoreticTransformFriendlyModInt() : base(1), rev{0, 1}, rts{0, 1} {
    const int mod = Mint::get_mod();
    assert(mod >= 3 && mod % 2 == 1);
    auto tmp = mod - 1;
    max_base = 0;
    while(tmp % 2 == 0) tmp >>= 1, max_base++;
    root = 2;
    while(root.pow((mod - 1) >> 1) == 1) root += 1;
    assert(root.pow(mod - 1) == 1);
    root = root.pow((mod - 1) >> max_base);
  }

  void ensure_base(int nbase) {
    if(nbase <= base) return;
    rev.resize(1 << nbase);
    rts.resize(1 << nbase);
    for(int i = 0; i < (1 << nbase); i++) {
      rev[i] = (rev[i >> 1] >> 1) + ((i & 1) << (nbase - 1));
    }
    assert(nbase <= max_base);
    while(base < nbase) {
      Mint z = root.pow(1 << (max_base - 1 - base));
      for(int i = 1 << (base - 1); i < (1 << base); i++) {
        rts[i << 1] = rts[i];
        rts[(i << 1) + 1] = rts[i] * z;
      }
      ++base;
    }
  }


  void ntt(vector< Mint > &a) {
    const int n = (int) a.size();
    assert((n & (n - 1)) == 0);
    int zeros = __builtin_ctz(n);
    ensure_base(zeros);
    int shift = base - zeros;
    for(int i = 0; i < n; i++) {
      if(i < (rev[i] >> shift)) {
        swap(a[i], a[rev[i] >> shift]);
      }
    }
    for(int k = 1; k < n; k <<= 1) {
      for(int i = 0; i < n; i += 2 * k) {
        for(int j = 0; j < k; j++) {
          Mint z = a[i + j + k] * rts[j + k];
          a[i + j + k] = a[i + j] - z;
          a[i + j] = a[i + j] + z;
        }
      }
    }
  }


  void intt(vector< Mint > &a) {
    const int n = (int) a.size();
    ntt(a);
    reverse(a.begin() + 1, a.end());
    Mint inv_sz = Mint(1) / n;
    for(int i = 0; i < n; i++) a[i] *= inv_sz;
  }

  vector< Mint > multiply(vector< Mint > a, vector< Mint > b) {
    int need = a.size() + b.size() - 1;
    int nbase = 1;
    while((1 << nbase) < need) nbase++;
    ensure_base(nbase);
    int sz = 1 << nbase;
    a.resize(sz, 0);
    b.resize(sz, 0);
    ntt(a);
    ntt(b);
    Mint inv_sz = Mint(1) / sz;
    for(int i = 0; i < sz; i++) {
      a[i] *= b[i] * inv_sz;
    }
    reverse(a.begin() + 1, a.end());
    ntt(a);
    a.resize(need);
    return a;
  }
};


##################################################
################# euler-phi.cpp ##################
##################################################

int64_t euler_phi(int64_t n) {
  int64_t ret = n;
  for(int64_t i = 2; i * i <= n; i++) {
    if(n % i == 0) {
      ret -= ret / i;
      while(n % i == 0) n /= i;
    }
  }
  if(n > 1) ret -= ret / n;
  return ret;
}


##################################################
############ lagrange-polynomial.cpp #############
##################################################

template< typename T >
T lagrange_polynomial(const vector< T > &y, int64_t t) {
  int N = y.size() - 1;
  Combination< T > comb(N);
  if(t <= N) return y[t];
  T ret(0);
  vector< T > dp(N + 1, 1), pd(N + 1, 1);
  for(int i = 0; i < N; i++) dp[i + 1] = dp[i] * (t - i);
  for(int i = N; i > 0; i--) pd[i - 1] = pd[i] * (t - i);
  for(int i = 0; i <= N; i++) {
    T tmp = y[i] * dp[i] * pd[i] * comb.rfact(i) * comb.rfact(N - i);
    if((N - i) & 1) ret -= tmp;
    else ret += tmp;
  }
  return ret;
}


##################################################
################ combination.cpp #################
##################################################

template< typename T >
struct Combination {
  vector< T > _fact, _rfact, _inv;

  Combination(int sz) : _fact(sz + 1), _rfact(sz + 1), _inv(sz + 1) {
    _fact[0] = _rfact[sz] = _inv[0] = 1;
    for(int i = 1; i <= sz; i++) _fact[i] = _fact[i - 1] * i;
    _rfact[sz] /= _fact[sz];
    for(int i = sz - 1; i >= 0; i--) _rfact[i] = _rfact[i + 1] * (i + 1);
    for(int i = 1; i <= sz; i++) _inv[i] = _rfact[i] * _fact[i - 1];
  }

  inline T fact(int k) const { return _fact[k]; }

  inline T rfact(int k) const { return _rfact[k]; }

  inline T inv(int k) const { return _inv[k]; }

  T P(int n, int r) const {
    if(r < 0 || n < r) return 0;
    return fact(n) * rfact(n - r);
  }

  T C(int p, int q) const {
    if(q < 0 || p < q) return 0;
    return fact(p) * rfact(q) * rfact(p - q);
  }

  T H(int n, int r) const {
    if(n < 0 || r < 0) return (0);
    return r == 0 ? 1 : C(n + r - 1, r);
  }
};


##################################################
################## mod-log.cpp ###################
##################################################

int64_t mod_log(int64_t a, int64_t b, int64_t p) {
  int64_t g = 1;

  for(int64_t i = p; i; i /= 2) (g *= a) %= p;
  g = __gcd(g, p);

  int64_t t = 1, c = 0;
  for(; t % g; c++) {
    if(t == b) return c;
    (t *= a) %= p;
  }
  if(b % g) return -1;

  t /= g;
  b /= g;

  int64_t n = p / g, h = 0, gs = 1;

  for(; h * h < n; h++) (gs *= a) %= n;

  unordered_map< int64_t, int64_t > bs;
  for(int64_t s = 0, e = b; s < h; bs[e] = ++s) {
    (e *= a) %= n;
  }

  for(int64_t s = 0, e = t; s < n;) {
    (e *= gs) %= n;
    s += h;
    if(bs.count(e)) return c + s - bs[e];
  }
  return -1;
}


##################################################
############### quotient-range.cpp ###############
##################################################

template< typename T >
vector< pair< pair< T, T >, T > > quotient_range(T N) {
  T M;
  vector< pair< pair< T, T >, T > > ret;
  for(M = 1; M * M <= N; M++) {
    ret.emplace_back(make_pair(M, M), N / M);
  }
  for(T i = M; i >= 1; i--) {
    T L = N / (i + 1) + 1;
    T R = N / i;
    if(L <= R && ret.back().first.second < L) ret.emplace_back(make_pair(L, R), N / L);
  }
  return ret;
}


##################################################
########## formal-power-series-seq.cpp ###########
##################################################

template< typename T >
FormalPowerSeries< T > bernoulli(int N) {
  FormalPowerSeries< T > poly(N + 1);
  poly[0] = T(1);
  for(int i = 1; i <= N; i++) {
    poly[i] = poly[i - 1] / T(i + 1);
  }
  poly = poly.inv();
  T tmp(1);
  for(int i = 1; i <= N; i++) {
    tmp *= T(i);
    poly[i] *= tmp;
  }
  return poly;
}

template< typename T >
FormalPowerSeries< T > partition(int N) {
  FormalPowerSeries< T > poly(N + 1);
  poly[0] = 1;
  for(int k = 1; k <= N; k++) {
    if(1LL * k * (3 * k + 1) / 2 <= N) poly[k * (3 * k + 1) / 2] += (k % 2 ? -1 : 1);
    if(1LL * k * (3 * k - 1) / 2 <= N) poly[k * (3 * k - 1) / 2] += (k % 2 ? -1 : 1);
  }
  return poly.inv();
}

template< typename T >
FormalPowerSeries< T > bell(int N) {
  FormalPowerSeries< T > poly(N + 1), ret(N + 1);
  poly[1] = 1;
  poly = poly.exp();
  poly[0] -= 1;
  poly = poly.exp();
  T mul = 1;
  for(int i = 0; i <= N; i++) {
    ret[i] = poly[i] * mul;
    mul *= i + 1;
  }
  return ret;
}

template< typename T >
FormalPowerSeries< T > stirling_first(int N) {
  if(N == 0) return {1};
  int M = N / 2;
  FormalPowerSeries< T > A = stirling_first< T >(M), B, C(N - M + 1);

  if(N % 2 == 0) {
    B = A;
  } else {
    B.resize(M + 2);
    B[M + 1] = 1;
    for(int i = 1; i < M + 1; i++) B[i] = A[i - 1] + A[i] * M;
  }

  T tmp = 1;
  for(int i = 0; i <= N - M; i++) {
    C[N - M - i] = T(M).pow(i) / tmp;
    B[i] *= tmp;
    tmp *= T(i + 1);
  }
  C *= B;
  tmp = 1;
  for(int i = 0; i <= N - M; i++) {
    B[i] = C[N - M + i] / tmp;
    tmp *= T(i + 1);
  }
  return A * B;
}

template< typename T >
FormalPowerSeries< T > stirling_second(int N) {
  FormalPowerSeries< T > A(N + 1), B(N + 1);
  modint tmp = 1;
  for(int i = 0; i <= N; i++) {
    T rev = T(1) / tmp;
    A[i] = T(i).pow(N) * rev;
    B[i] = T(1) * rev;
    if(i & 1) B[i] *= -1;
    tmp *= i + 1;
  }
  return (A * B).pre(N + 1);
}

template< typename T >
FormalPowerSeries< T > stirling_second_kth_column(int N, int K) {
  FormalPowerSeries< T > poly(N + 1), ret(N + 1);
  poly[1] = 1;
  poly = poly.exp();
  poly[0] -= 1;
  poly = poly.pow(K);
  T rev = 1, mul = 1;
  for(int i = 2; i <= K; i++) rev *= i;
  rev = T(1) / rev;
  poly *= rev;
  for(int i = 0; i <= N; i++) {
    ret[i] = poly[i] * mul;
    mul *= i + 1;
  }
  return ret;
}

template< typename T >
FormalPowerSeries< T > eulerian(int N) {
  vector< T > fact(N + 2), rfact(N + 2);
  fact[0] = rfact[N + 1] = 1;
  for(int i = 1; i <= N + 1; i++) fact[i] = fact[i - 1] * i;
  rfact[N + 1] /= fact[N + 1];
  for(int i = N; i >= 0; i--) rfact[i] = rfact[i + 1] * (i + 1);

  FormalPowerSeries< T > A(N + 1), B(N + 1);
  for(int i = 0; i <= N; i++) {
    A[i] = fact[N + 1] * rfact[i] * rfact[N + 1 - i];
    if(i & 1) A[i] *= -1;
    B[i] = T(i + 1).pow(N);
  }
  return (A * B).pre(N + 1);
}


##################################################
########## fast-prime-factorization.cpp ##########
##################################################

namespace FastPrimeFactorization {

  template< typename word, typename dword, typename sword >
  struct UnsafeMod {
    UnsafeMod() : x(0) {}

    UnsafeMod(word _x) : x(init(_x)) {}

    bool operator==(const UnsafeMod &rhs) const {
      return x == rhs.x;
    }

    bool operator!=(const UnsafeMod &rhs) const {
      return x != rhs.x;
    }

    UnsafeMod &operator+=(const UnsafeMod &rhs) {
      if((x += rhs.x) >= mod) x -= mod;
      return *this;
    }

    UnsafeMod &operator-=(const UnsafeMod &rhs) {
      if(sword(x -= rhs.x) < 0) x += mod;
      return *this;
    }

    UnsafeMod &operator*=(const UnsafeMod &rhs) {
      x = reduce(dword(x) * rhs.x);
      return *this;
    }

    UnsafeMod operator+(const UnsafeMod &rhs) const {
      return UnsafeMod(*this) += rhs;
    }

    UnsafeMod operator-(const UnsafeMod &rhs) const {
      return UnsafeMod(*this) -= rhs;
    }

    UnsafeMod operator*(const UnsafeMod &rhs) const {
      return UnsafeMod(*this) *= rhs;
    }

    UnsafeMod pow(uint64_t e) const {
      UnsafeMod ret(1);
      for(UnsafeMod base = *this; e; e >>= 1, base *= base) {
        if(e & 1) ret *= base;
      }
      return ret;
    }

    word get() const {
      return reduce(x);
    }

    static constexpr int word_bits = sizeof(word) * 8;

    static word modulus() {
      return mod;
    }

    static word init(word w) {
      return reduce(dword(w) * r2);
    }

    static void set_mod(word m) {
      mod = m;
      inv = mul_inv(mod);
      r2 = -dword(mod) % mod;
    }

    static word reduce(dword x) {
      word y = word(x >> word_bits) - word((dword(word(x) * inv) * mod) >> word_bits);
      return sword(y) < 0 ? y + mod : y;
    }

    static word mul_inv(word n, int e = 6, word x = 1) {
      return !e ? x : mul_inv(n, e - 1, x * (2 - x * n));
    }

    static word mod, inv, r2;

    word x;
  };

  using uint128_t = __uint128_t;

  using Mod64 = UnsafeMod< uint64_t, uint128_t, int64_t >;
  template<> uint64_t Mod64::mod = 0;
  template<> uint64_t Mod64::inv = 0;
  template<> uint64_t Mod64::r2 = 0;

  using Mod32 = UnsafeMod< uint32_t, uint64_t, int32_t >;
  template<> uint32_t Mod32::mod = 0;
  template<> uint32_t Mod32::inv = 0;
  template<> uint32_t Mod32::r2 = 0;

  bool miller_rabin_primality_test_uint64(uint64_t n) {
    Mod64::set_mod(n);
    uint64_t d = n - 1;
    while(d % 2 == 0) d /= 2;
    Mod64 e{1}, rev{n - 1};
    // http://miller-rabin.appspot.com/  < 2^64
    for(uint64_t a : {2, 325, 9375, 28178, 450775, 9780504, 1795265022}) {
      if(n <= a) break;
      uint64_t t = d;
      Mod64 y = Mod64(a).pow(t);
      while(t != n - 1 && y != e && y != rev) {
        y *= y;
        t *= 2;
      }
      if(y != rev && t % 2 == 0) return false;
    }
    return true;
  }

  bool miller_rabin_primality_test_uint32(uint32_t n) {
    Mod32::set_mod(n);
    uint32_t d = n - 1;
    while(d % 2 == 0) d /= 2;
    Mod32 e{1}, rev{n - 1};
    for(uint32_t a : {2, 7, 61}) {
      if(n <= a) break;
      uint32_t t = d;
      Mod32 y = Mod32(a).pow(t);
      while(t != n - 1 && y != e && y != rev) {
        y *= y;
        t *= 2;
      }
      if(y != rev && t % 2 == 0) return false;
    }
    return true;
  }

  bool is_prime(uint64_t n) {
    if(n == 2) return true;
    if(n == 1 || n % 2 == 0) return false;
    if(n < uint64_t(1) << 31) return miller_rabin_primality_test_uint32(n);
    return miller_rabin_primality_test_uint64(n);
  }

  uint64_t pollard_rho(uint64_t n) {
    if(is_prime(n)) return n;
    if(n % 2 == 0) return 2;
    Mod64::set_mod(n);
    uint64_t d;
    Mod64 one{1};
    for(Mod64 c{one};; c += one) {
      Mod64 x{2}, y{2};
      do {
        x = x * x + c;
        y = y * y + c;
        y = y * y + c;
        d = __gcd((x - y).get(), n);
      } while(d == 1);
      if(d < n) return d;
    }
    assert(0);
  }

  vector< uint64_t > prime_factor(uint64_t n) {
    if(n <= 1) return {};
    uint64_t p = pollard_rho(n);
    if(p == n) return {p};
    auto l = prime_factor(p);
    auto r = prime_factor(n / p);
    copy(begin(r), end(r), back_inserter(l));
    return l;
  }
};


##################################################
################## is-prime.cpp ##################
##################################################

bool is_prime(int64_t x) {
  for(int64_t i = 2; i * i <= x; i++) {
    if(x % i == 0) return false;
  }
  return true;
}


##################################################
############### sparse-matrix.cpp ################
##################################################

template< typename T >
using FPSGraph = vector< vector< pair< int, T > > >;

template< typename T >
FormalPowerSeries< T > random_poly(int n) {
  mt19937 mt(1333333);
  FormalPowerSeries< T > res(n);
  uniform_int_distribution< int > rand(0, T::get_mod() - 1);
  for(int i = 0; i < n; i++) res[i] = rand(mt);
  return res;
}

template< typename T >
FormalPowerSeries< T > next_poly(const FormalPowerSeries< T > &dp, const FPSGraph< T > &g) {
  const int N = (int) dp.size();
  FormalPowerSeries< T > nxt(N);
  for(int i = 0; i < N; i++) {
    for(auto &p : g[i]) nxt[p.first] += p.second * dp[i];
  }
  return nxt;
}

template< typename T >
FormalPowerSeries< T > minimum_poly(const FPSGraph< T > &g) {
  const int N = (int) g.size();
  auto dp = random_poly< T >(N), u = random_poly< T >(N);
  FormalPowerSeries< T > f(2 * N);
  for(int i = 0; i < 2 * N; i++) {
    for(auto &p : u.dot(dp)) f[i] += p;
    dp = next_poly(dp, g);
  }
  return berlekamp_massey(f);
}

/* O(N(N+S) + N log N log Q) (O(S): time complexity of nex) */
template< typename T >
FormalPowerSeries< T > sparse_pow(int64_t Q, FormalPowerSeries< modint > dp, const FPSGraph< T > &g) {
  const int N = (int) dp.size();
  auto A = FormalPowerSeries< T >({0, 1}).pow_mod(Q, minimum_poly(g));
  FormalPowerSeries< T > res(N);
  for(int i = 0; i < A.size(); i++) {
    res += dp * A[i];
    dp = next_poly(dp, g);
  }
  return res;
}

/* O(N(N+S)) (S: none-zero elements)*/
template< typename T >
T sparse_determinant(FPSGraph< T > g) {
  using FPS = FormalPowerSeries< T >;
  int N = (int) g.size();
  auto C = random_poly< T >(N);
  for(int i = 0; i < N; i++) for(auto &p : g[i]) p.second *= C[i];
  auto u = minimum_poly(g);
  T acdet = u[0];
  if(N % 2 == 0) acdet *= -1;
  T cdet = 1;
  for(int i = 0; i < N; i++) cdet *= C[i];
  return acdet / cdet;
}


##################################################
################ convert-base.cpp ################
##################################################

template< typename T >
vector< T > convert_base(T x, T b) {
  vector< T > ret;
  T t = 1, k = abs(b);
  while(x) {
    ret.emplace_back((x * t) % k);
    if(ret.back() < 0) ret.back() += k;
    x -= ret.back() * t;
    x /= k;
    t *= b / k;
  }
  if(ret.empty()) ret.emplace_back(0);
  reverse(begin(ret), end(ret));
  return ret;
}


##################################################
############## partition-table.cpp ###############
##################################################

template< typename T >
vector< vector< T > > get_partition(int n, int k) {
  vector< vector< T > > dp(n + 1, vector< T >(k + 1));
  dp[0][0] = 1;
  for(int i = 0; i <= n; i++) {
    for(int j = 1; j <= k; j++) {
      if(i - j >= 0) dp[i][j] = dp[i][j - 1] + dp[i - j][j];
      else dp[i][j] = dp[i][j - 1];
    }
  }
  return dp;
}


##################################################
########### fast-fourier-transform.cpp ###########
##################################################

namespace FastFourierTransform {
  using real = double;

  struct C {
    real x, y;

    C() : x(0), y(0) {}

    C(real x, real y) : x(x), y(y) {}

    inline C operator+(const C &c) const { return C(x + c.x, y + c.y); }

    inline C operator-(const C &c) const { return C(x - c.x, y - c.y); }

    inline C operator*(const C &c) const { return C(x * c.x - y * c.y, x * c.y + y * c.x); }

    inline C conj() const { return C(x, -y); }
  };

  const real PI = acosl(-1);
  int base = 1;
  vector< C > rts = { {0, 0},
                     {1, 0} };
  vector< int > rev = {0, 1};


  void ensure_base(int nbase) {
    if(nbase <= base) return;
    rev.resize(1 << nbase);
    rts.resize(1 << nbase);
    for(int i = 0; i < (1 << nbase); i++) {
      rev[i] = (rev[i >> 1] >> 1) + ((i & 1) << (nbase - 1));
    }
    while(base < nbase) {
      real angle = PI * 2.0 / (1 << (base + 1));
      for(int i = 1 << (base - 1); i < (1 << base); i++) {
        rts[i << 1] = rts[i];
        real angle_i = angle * (2 * i + 1 - (1 << base));
        rts[(i << 1) + 1] = C(cos(angle_i), sin(angle_i));
      }
      ++base;
    }
  }

  void fft(vector< C > &a, int n) {
    assert((n & (n - 1)) == 0);
    int zeros = __builtin_ctz(n);
    ensure_base(zeros);
    int shift = base - zeros;
    for(int i = 0; i < n; i++) {
      if(i < (rev[i] >> shift)) {
        swap(a[i], a[rev[i] >> shift]);
      }
    }
    for(int k = 1; k < n; k <<= 1) {
      for(int i = 0; i < n; i += 2 * k) {
        for(int j = 0; j < k; j++) {
          C z = a[i + j + k] * rts[j + k];
          a[i + j + k] = a[i + j] - z;
          a[i + j] = a[i + j] + z;
        }
      }
    }
  }

  vector< int64_t > multiply(const vector< int > &a, const vector< int > &b) {
    int need = (int) a.size() + (int) b.size() - 1;
    int nbase = 1;
    while((1 << nbase) < need) nbase++;
    ensure_base(nbase);
    int sz = 1 << nbase;
    vector< C > fa(sz);
    for(int i = 0; i < sz; i++) {
      int x = (i < (int) a.size() ? a[i] : 0);
      int y = (i < (int) b.size() ? b[i] : 0);
      fa[i] = C(x, y);
    }
    fft(fa, sz);
    C r(0, -0.25 / (sz >> 1)), s(0, 1), t(0.5, 0);
    for(int i = 0; i <= (sz >> 1); i++) {
      int j = (sz - i) & (sz - 1);
      C z = (fa[j] * fa[j] - (fa[i] * fa[i]).conj()) * r;
      fa[j] = (fa[i] * fa[i] - (fa[j] * fa[j]).conj()) * r;
      fa[i] = z;
    }
    for(int i = 0; i < (sz >> 1); i++) {
      C A0 = (fa[i] + fa[i + (sz >> 1)]) * t;
      C A1 = (fa[i] - fa[i + (sz >> 1)]) * t * rts[(sz >> 1) + i];
      fa[i] = A0 + A1 * s;
    }
    fft(fa, sz >> 1);
    vector< int64_t > ret(need);
    for(int i = 0; i < need; i++) {
      ret[i] = llround(i & 1 ? fa[i >> 1].y : fa[i >> 1].x);
    }
    return ret;
  }
};


##################################################
################### extgcd.cpp ###################
##################################################

template< typename T >
T extgcd(T a, T b, T &x, T &y) {
  T d = a;
  if(b != 0) {
    d = extgcd(b, a % b, y, x);
    y -= (a / b) * x;
  } else {
    x = 1;
    y = 0;
  }
  return d;
}


##################################################
############ formal-power-series.cpp #############
##################################################

template< typename T >
struct FormalPowerSeries : vector< T > {
  using vector< T >::vector;
  using P = FormalPowerSeries;

  using MULT = function< P(P, P) >;
  using FFT = function< void(P &) >;

  static MULT &get_mult() {
    static MULT mult = nullptr;
    return mult;
  }

  static void set_mult(MULT f) { get_mult() = f; }

  static FFT &get_fft() {
    static FFT fft = nullptr;
    return fft;
  }

  static FFT &get_ifft() {
    static FFT ifft = nullptr;
    return ifft;
  }

  static void set_fft(FFT f, FFT g) {
    get_fft() = f;
    get_ifft() = g;
  }

  void shrink() {
    while(this->size() && this->back() == T(0)) this->pop_back();
  }

  P operator+(const P &r) const { return P(*this) += r; }

  P operator+(const T &v) const { return P(*this) += v; }

  P operator-(const P &r) const { return P(*this) -= r; }

  P operator-(const T &v) const { return P(*this) -= v; }

  P operator*(const P &r) const { return P(*this) *= r; }

  P operator*(const T &v) const { return P(*this) *= v; }

  P operator/(const P &r) const { return P(*this) /= r; }

  P operator%(const P &r) const { return P(*this) %= r; }

  P &operator+=(const P &r) {
    if(r.size() > this->size()) this->resize(r.size());
    for(int i = 0; i < r.size(); i++) (*this)[i] += r[i];
    return *this;
  }

  P &operator+=(const T &r) {
    if(this->empty()) this->resize(1);
    (*this)[0] += r;
    return *this;
  }

  P &operator-=(const P &r) {
    if(r.size() > this->size()) this->resize(r.size());
    for(int i = 0; i < r.size(); i++) (*this)[i] -= r[i];
    shrink();
    return *this;
  }

  P &operator-=(const T &r) {
    if(this->empty()) this->resize(1);
    (*this)[0] -= r;
    shrink();
    return *this;
  }

  P &operator*=(const T &v) {
    const int n = (int) this->size();
    for(int k = 0; k < n; k++) (*this)[k] *= v;
    return *this;
  }

  P &operator*=(const P &r) {
    if(this->empty() || r.empty()) {
      this->clear();
      return *this;
    }
    assert(get_mult() != nullptr);
    return *this = get_mult()(*this, r);
  }

  P &operator%=(const P &r) { return *this -= *this / r * r; }

  P operator-() const {
    P ret(this->size());
    for(int i = 0; i < this->size(); i++) ret[i] = -(*this)[i];
    return ret;
  }

  P &operator/=(const P &r) {
    if(this->size() < r.size()) {
      this->clear();
      return *this;
    }
    int n = this->size() - r.size() + 1;
    return *this = (rev().pre(n) * r.rev().inv(n)).pre(n).rev(n);
  }

  P dot(P r) const {
    P ret(min(this->size(), r.size()));
    for(int i = 0; i < ret.size(); i++) ret[i] = (*this)[i] * r[i];
    return ret;
  }

  P pre(int sz) const { return P(begin(*this), begin(*this) + min((int) this->size(), sz)); }

  P operator>>(int sz) const {
    if(this->size() <= sz) return {};
    P ret(*this);
    ret.erase(ret.begin(), ret.begin() + sz);
    return ret;
  }

  P operator<<(int sz) const {
    P ret(*this);
    ret.insert(ret.begin(), sz, T(0));
    return ret;
  }

  P rev(int deg = -1) const {
    P ret(*this);
    if(deg != -1) ret.resize(deg, T(0));
    reverse(begin(ret), end(ret));
    return ret;
  }

  P diff() const {
    const int n = (int) this->size();
    P ret(max(0, n - 1));
    for(int i = 1; i < n; i++) ret[i - 1] = (*this)[i] * T(i);
    return ret;
  }

  P integral() const {
    const int n = (int) this->size();
    P ret(n + 1);
    ret[0] = T(0);
    for(int i = 0; i < n; i++) ret[i + 1] = (*this)[i] / T(i + 1);
    return ret;
  }

  // F(0) must not be 0
  P inv(int deg = -1) const {
    assert(((*this)[0]) != T(0));
    const int n = (int) this->size();
    if(deg == -1) deg = n;
    if(get_fft() != nullptr) {
      P ret(*this);
      ret.resize(deg, T(0));
      return ret.inv_fast();
    }
    P ret({T(1) / (*this)[0]});
    for(int i = 1; i < deg; i <<= 1) {
      ret = (ret + ret - ret * ret * pre(i << 1)).pre(i << 1);
    }
    return ret.pre(deg);
  }

  // F(0) must be 1
  P log(int deg = -1) const {
    assert((*this)[0] == 1);
    const int n = (int) this->size();
    if(deg == -1) deg = n;
    return (this->diff() * this->inv(deg)).pre(deg - 1).integral();
  }

  P sqrt(int deg = -1) const {
    const int n = (int) this->size();
    if(deg == -1) deg = n;
    if((*this)[0] == T(0)) {
      for(int i = 1; i < n; i++) {
        if((*this)[i] != T(0)) {
          if(i & 1) return {};
          if(deg - i / 2 <= 0) break;
          auto ret = (*this >> i).sqrt(deg - i / 2) << (i / 2);
          if(ret.size() < deg) ret.resize(deg, T(0));
          return ret;
        }
      }
      return P(deg, 0);
    }

    P ret({T(1)});
    T inv2 = T(1) / T(2);
    for(int i = 1; i < deg; i <<= 1) {
      ret = (ret + pre(i << 1) * ret.inv(i << 1)) * inv2;
    }
    return ret.pre(deg);
  }

  // F(0) must be 0
  P exp(int deg = -1) const {
    assert((*this)[0] == T(0));
    const int n = (int) this->size();
    if(deg == -1) deg = n;
    if(get_fft() != nullptr) {
      P ret(*this);
      ret.resize(deg, T(0));
      return ret.exp_rec();
    }
    P ret({T(1)});
    for(int i = 1; i < deg; i <<= 1) {
      ret = (ret * (pre(i << 1) + T(1) - ret.log(i << 1))).pre(i << 1);
    }
    return ret.pre(deg);
  }


  P online_convolution_exp(const P &conv_coeff) const {
    const int n = (int) conv_coeff.size();
    assert((n & (n - 1)) == 0);
    vector< P > conv_ntt_coeff;
    for(int i = n; i >= 1; i >>= 1) {
      P g(conv_coeff.pre(i));
      get_fft()(g);
      conv_ntt_coeff.emplace_back(g);
    }
    P conv_arg(n), conv_ret(n);
    auto rec = [&](auto rec, int l, int r, int d) -> void {
      if(r - l <= 16) {
        for(int i = l; i < r; i++) {
          T sum = 0;
          for(int j = l; j < i; j++) sum += conv_arg[j] * conv_coeff[i - j];
          conv_ret[i] += sum;
          conv_arg[i] = i == 0 ? T(1) : conv_ret[i] / i;
        }
      } else {
        int m = (l + r) / 2;
        rec(rec, l, m, d + 1);
        P pre(r - l);
        for(int i = 0; i < m - l; i++) pre[i] = conv_arg[l + i];
        get_fft()(pre);
        for(int i = 0; i < r - l; i++) pre[i] *= conv_ntt_coeff[d][i];
        get_ifft()(pre);
        for(int i = 0; i < r - m; i++) conv_ret[m + i] += pre[m + i - l];
        rec(rec, m, r, d + 1);
      }
    };
    rec(rec, 0, n, 0);
    return conv_arg;
  }

  P exp_rec() const {
    assert((*this)[0] == T(0));
    const int n = (int) this->size();
    int m = 1;
    while(m < n) m *= 2;
    P conv_coeff(m);
    for(int i = 1; i < n; i++) conv_coeff[i] = (*this)[i] * i;
    return online_convolution_exp(conv_coeff).pre(n);
  }


  P inv_fast() const {
    assert(((*this)[0]) != T(0));

    const int n = (int) this->size();
    P res{T(1) / (*this)[0]};

    for(int d = 1; d < n; d <<= 1) {
      P f(2 * d), g(2 * d);
      for(int j = 0; j < min(n, 2 * d); j++) f[j] = (*this)[j];
      for(int j = 0; j < d; j++) g[j] = res[j];
      get_fft()(f);
      get_fft()(g);
      for(int j = 0; j < 2 * d; j++) f[j] *= g[j];
      get_ifft()(f);
      for(int j = 0; j < d; j++) {
        f[j] = 0;
        f[j + d] = -f[j + d];
      }
      get_fft()(f);
      for(int j = 0; j < 2 * d; j++) f[j] *= g[j];
      get_ifft()(f);
      for(int j = 0; j < d; j++) f[j] = res[j];
      res = f;
    }
    return res.pre(n);
  }

  P pow(int64_t k, int deg = -1) const {
    const int n = (int) this->size();
    if(deg == -1) deg = n;
    for(int i = 0; i < n; i++) {
      if((*this)[i] != T(0)) {
        T rev = T(1) / (*this)[i];
        P ret = (((*this * rev) >> i).log() * k).exp() * ((*this)[i].pow(k));
        if(i * k > deg) return P(deg, T(0));
        ret = (ret << (i * k)).pre(deg);
        if(ret.size() < deg) ret.resize(deg, T(0));
        return ret;
      }
    }
    return *this;
  }

  T eval(T x) const {
    T r = 0, w = 1;
    for(auto &v : *this) {
      r += w * v;
      w *= x;
    }
    return r;
  }

  P pow_mod(int64_t n, P mod) const {
    P modinv = mod.rev().inv();
    auto get_div = [&](P base) {
      if(base.size() < mod.size()) {
        base.clear();
        return base;
      }
      int n = base.size() - mod.size() + 1;
      return (base.rev().pre(n) * modinv.pre(n)).pre(n).rev(n);
    };
    P x(*this), ret{1};
    while(n > 0) {
      if(n & 1) {
        ret *= x;
        ret -= get_div(ret) * mod;
      }
      x *= x;
      x -= get_div(x) * mod;
      n >>= 1;
    }
    return ret;
  }
};


##################################################
################### matrix.cpp ###################
##################################################

template< class T >
struct Matrix {
  vector< vector< T > > A;

  Matrix() {}

  Matrix(size_t n, size_t m) : A(n, vector< T >(m, 0)) {}

  Matrix(size_t n) : A(n, vector< T >(n, 0)) {};

  size_t height() const {
    return (A.size());
  }

  size_t width() const {
    return (A[0].size());
  }

  inline const vector< T > &operator[](int k) const {
    return (A.at(k));
  }

  inline vector< T > &operator[](int k) {
    return (A.at(k));
  }

  static Matrix I(size_t n) {
    Matrix mat(n);
    for(int i = 0; i < n; i++) mat[i][i] = 1;
    return (mat);
  }

  Matrix &operator+=(const Matrix &B) {
    size_t n = height(), m = width();
    assert(n == B.height() && m == B.width());
    for(int i = 0; i < n; i++)
      for(int j = 0; j < m; j++)
        (*this)[i][j] += B[i][j];
    return (*this);
  }

  Matrix &operator-=(const Matrix &B) {
    size_t n = height(), m = width();
    assert(n == B.height() && m == B.width());
    for(int i = 0; i < n; i++)
      for(int j = 0; j < m; j++)
        (*this)[i][j] -= B[i][j];
    return (*this);
  }

  Matrix &operator*=(const Matrix &B) {
    size_t n = height(), m = B.width(), p = width();
    assert(p == B.height());
    vector< vector< T > > C(n, vector< T >(m, 0));
    for(int i = 0; i < n; i++)
      for(int j = 0; j < m; j++)
        for(int k = 0; k < p; k++)
          C[i][j] = (C[i][j] + (*this)[i][k] * B[k][j]);
    A.swap(C);
    return (*this);
  }

  Matrix &operator^=(long long k) {
    Matrix B = Matrix::I(height());
    while(k > 0) {
      if(k & 1) B *= *this;
      *this *= *this;
      k >>= 1LL;
    }
    A.swap(B.A);
    return (*this);
  }

  Matrix operator+(const Matrix &B) const {
    return (Matrix(*this) += B);
  }

  Matrix operator-(const Matrix &B) const {
    return (Matrix(*this) -= B);
  }

  Matrix operator*(const Matrix &B) const {
    return (Matrix(*this) *= B);
  }

  Matrix operator^(const long long k) const {
    return (Matrix(*this) ^= k);
  }

  friend ostream &operator<<(ostream &os, Matrix &p) {
    size_t n = p.height(), m = p.width();
    for(int i = 0; i < n; i++) {
      os << "[";
      for(int j = 0; j < m; j++) {
        os << p[i][j] << (j + 1 == m ? "]\n" : ",");
      }
    }
    return (os);
  }


  T determinant() {
    Matrix B(*this);
    assert(width() == height());
    T ret = 1;
    for(int i = 0; i < width(); i++) {
      int idx = -1;
      for(int j = i; j < width(); j++) {
        if(B[j][i] != 0) idx = j;
      }
      if(idx == -1) return (0);
      if(i != idx) {
        ret *= -1;
        swap(B[i], B[idx]);
      }
      ret *= B[i][i];
      T vv = B[i][i];
      for(int j = 0; j < width(); j++) {
        B[i][j] /= vv;
      }
      for(int j = i + 1; j < width(); j++) {
        T a = B[j][i];
        for(int k = 0; k < width(); k++) {
          B[j][k] -= B[i][k] * a;
        }
      }
    }
    return (ret);
  }
};


##################################################
############## berlekamp-massey.cpp ##############
##################################################

template< class T >
FormalPowerSeries< T > berlekamp_massey(const FormalPowerSeries< T > &s) {
  const int N = (int) s.size();
  FormalPowerSeries< T > b = {T(-1)}, c = {T(-1)};
  T y = T(1);
  for(int ed = 1; ed <= N; ed++) {
    int l = int(c.size()), m = int(b.size());
    T x = 0;
    for(int i = 0; i < l; i++) x += c[i] * s[ed - l + i];
    b.emplace_back(0);
    m++;
    if(x == T(0)) continue;
    T freq = x / y;
    if(l < m) {
      auto tmp = c;
      c.insert(begin(c), m - l, T(0));
      for(int i = 0; i < m; i++) c[m - 1 - i] -= freq * b[m - 1 - i];
      b = tmp;
      y = x;
    } else {
      for(int i = 0; i < m; i++) c[l - 1 - i] -= freq * b[m - 1 - i];
    }
  }
  return c;
}


##################################################
############## euler-phi-table.cpp ###############
##################################################

vector< int > euler_phi_table(int n) {
  vector< int > euler(n + 1);
  for(int i = 0; i <= n; i++) {
    euler[i] = i;
  }
  for(int i = 2; i <= n; i++) {
    if(euler[i] == i) {
      for(int j = i; j <= n; j += i) {
        euler[j] = euler[j] / i * (i - 1);
      }
    }
  }
  return euler;
}


##################################################
######### number-theoretic-transform.cpp #########
##################################################

template< int mod >
struct NumberTheoreticTransform {

  vector< int > rev, rts;
  int base, max_base, root;

  NumberTheoreticTransform() : base(1), rev{0, 1}, rts{0, 1} {
    assert(mod >= 3 && mod % 2 == 1);
    auto tmp = mod - 1;
    max_base = 0;
    while(tmp % 2 == 0) tmp >>= 1, max_base++;
    root = 2;
    while(mod_pow(root, (mod - 1) >> 1) == 1) ++root;
    assert(mod_pow(root, mod - 1) == 1);
    root = mod_pow(root, (mod - 1) >> max_base);
  }

  inline int mod_pow(int x, int n) {
    int ret = 1;
    while(n > 0) {
      if(n & 1) ret = mul(ret, x);
      x = mul(x, x);
      n >>= 1;
    }
    return ret;
  }

  inline int inverse(int x) {
    return mod_pow(x, mod - 2);
  }

  inline unsigned add(unsigned x, unsigned y) {
    x += y;
    if(x >= mod) x -= mod;
    return x;
  }

  inline unsigned mul(unsigned a, unsigned b) {
    return 1ull * a * b % (unsigned long long) mod;
  }

  void ensure_base(int nbase) {
    if(nbase <= base) return;
    rev.resize(1 << nbase);
    rts.resize(1 << nbase);
    for(int i = 0; i < (1 << nbase); i++) {
      rev[i] = (rev[i >> 1] >> 1) + ((i & 1) << (nbase - 1));
    }
    assert(nbase <= max_base);
    while(base < nbase) {
      int z = mod_pow(root, 1 << (max_base - 1 - base));
      for(int i = 1 << (base - 1); i < (1 << base); i++) {
        rts[i << 1] = rts[i];
        rts[(i << 1) + 1] = mul(rts[i], z);
      }
      ++base;
    }
  }


  void ntt(vector< int > &a) {
    const int n = (int) a.size();
    assert((n & (n - 1)) == 0);
    int zeros = __builtin_ctz(n);
    ensure_base(zeros);
    int shift = base - zeros;
    for(int i = 0; i < n; i++) {
      if(i < (rev[i] >> shift)) {
        swap(a[i], a[rev[i] >> shift]);
      }
    }
    for(int k = 1; k < n; k <<= 1) {
      for(int i = 0; i < n; i += 2 * k) {
        for(int j = 0; j < k; j++) {
          int z = mul(a[i + j + k], rts[j + k]);
          a[i + j + k] = add(a[i + j], mod - z);
          a[i + j] = add(a[i + j], z);
        }
      }
    }
  }


  vector< int > multiply(vector< int > a, vector< int > b) {
    int need = a.size() + b.size() - 1;
    int nbase = 1;
    while((1 << nbase) < need) nbase++;
    ensure_base(nbase);
    int sz = 1 << nbase;
    a.resize(sz, 0);
    b.resize(sz, 0);
    ntt(a);
    ntt(b);
    int inv_sz = inverse(sz);
    for(int i = 0; i < sz; i++) {
      a[i] = mul(a[i], mul(b[i], inv_sz));
    }
    reverse(a.begin() + 1, a.end());
    ntt(a);
    a.resize(need);
    return a;
  }
};


##################################################
############# arbitrary-mod-int.cpp ##############
##################################################

struct ArbitraryModInt {

  int x;

  ArbitraryModInt() : x(0) {}

  ArbitraryModInt(int64_t y) : x(y >= 0 ? y % mod() : (mod() - (-y) % mod()) % mod()) {}

  static int &mod() {
    static int mod = 0;
    return mod;
  }

  static int set_mod(int md) {
    mod() = md;
  }

  ArbitraryModInt &operator+=(const ArbitraryModInt &p) {
    if((x += p.x) >= mod()) x -= mod();
    return *this;
  }

  ArbitraryModInt &operator-=(const ArbitraryModInt &p) {
    if((x += mod() - p.x) >= mod()) x -= mod();
    return *this;
  }

  ArbitraryModInt &operator*=(const ArbitraryModInt &p) {
    unsigned long long a = (unsigned long long) x * p.x;
    unsigned xh = (unsigned) (a >> 32), xl = (unsigned) a, d, m;
    asm("divl %4; \n\t" : "=a" (d), "=d" (m) : "d" (xh), "a" (xl), "r" (mod()));
    x = m;
    return *this;
  }

  ArbitraryModInt &operator/=(const ArbitraryModInt &p) {
    *this *= p.inverse();
    return *this;
  }

  ArbitraryModInt operator-() const { return ArbitraryModInt(-x); }

  ArbitraryModInt operator+(const ArbitraryModInt &p) const { return ArbitraryModInt(*this) += p; }

  ArbitraryModInt operator-(const ArbitraryModInt &p) const { return ArbitraryModInt(*this) -= p; }

  ArbitraryModInt operator*(const ArbitraryModInt &p) const { return ArbitraryModInt(*this) *= p; }

  ArbitraryModInt operator/(const ArbitraryModInt &p) const { return ArbitraryModInt(*this) /= p; }

  bool operator==(const ArbitraryModInt &p) const { return x == p.x; }

  bool operator!=(const ArbitraryModInt &p) const { return x != p.x; }

  ArbitraryModInt inverse() const {
    int a = x, b = mod(), u = 1, v = 0, t;
    while(b > 0) {
      t = a / b;
      swap(a -= t * b, b);
      swap(u -= t * v, v);
    }
    return ArbitraryModInt(u);
  }

  ArbitraryModInt pow(int64_t n) const {
    ArbitraryModInt ret(1), mul(x);
    while(n > 0) {
      if(n & 1) ret *= mul;
      mul *= mul;
      n >>= 1;
    }
    return ret;
  }

  friend ostream &operator<<(ostream &os, const ArbitraryModInt &p) {
    return os << p.x;
  }

  friend istream &operator>>(istream &is, ArbitraryModInt &a) {
    int64_t t;
    is >> t;
    a = ArbitraryModInt(t);
    return (is);
  }
};


--------------------------------------------------
|                       dp                       |
--------------------------------------------------

##################################################
############ knapsack-limitations.cpp ############
##################################################

template< typename T, typename Compare = greater< T > >
vector< T > knapsack_limitations(const vector< int > &w, const vector< int > &m, const vector< T > &v,
                                 const int &W, const T &NG, const Compare &comp = Compare()) {
  const int N = (int) w.size();
  vector< T > dp(W + 1, NG), deqv(W + 1);
  dp[0] = T();
  vector< int > deq(W + 1);
  for(int i = 0; i < N; i++) {
    for(int a = 0; a < w[i]; a++) {
      int s = 0, t = 0;
      for(int j = 0; w[i] * j + a <= W; j++) {
        if(dp[w[i] * j + a] != NG) {
          auto val = dp[w[i] * j + a] - j * v[i];
          while(s < t && comp(val, deqv[t - 1])) --t;
          deq[t] = j;
          deqv[t++] = val;
        }
        if(s < t) {
          dp[j * w[i] + a] = deqv[s] + j * v[i];
          if(deq[s] == j - m[i]) ++s;
        }
      }
    }
  }
  return dp;
}


##################################################
############# online-offline-dp.cpp ##############
##################################################

template< typename T, typename Compare = less< T > >
vector< T > online_offline_dp(int W, const function< T(int, int) > &f, const Compare &comp = Compare()) {
  vector< T > dp(W + 1);
  vector< int > isset(W + 1);
  int y_base = -1, x_base = -1;
  function< T(int, int) > get_cost = [&](int y, int x) { // return dp[0, x+x_base)+f[x+x_base, y+y_base)
    return dp[x + x_base] + f(x + x_base, y + y_base);
  };
  function< void(int, int, int) > induce = [&](int l, int m, int r) { // dp[l, m) -> dp[m, r)
    x_base = l, y_base = m;
    auto ret = monotone_minima(r - m, m - l, get_cost, comp);
    for(int i = 0; i < ret.size(); i++) {
      if(!isset[m + i] || comp(ret[i].second, dp[m + i])) {
        isset[m + i] = true;
        dp[m + i] = ret[i].second;
      }
    }
  };
  function< void(int, int) > dfs = [&](int l, int r) {
    if(l + 1 == r) {
      x_base = l, y_base = l;
      T cst = l ? get_cost(0, -1) : 0;
      if(!isset[l] || comp(cst, dp[l])) {
        isset[l] = true;
        dp[l] = cst;
      }
    } else {
      int mid = (l + r) / 2;
      dfs(l, mid);
      induce(l, mid, r);
      dfs(mid, r);
    }
  };
  dfs(0, W + 1);
  return dp;
};


##################################################
############### cumulative-sum.cpp ###############
##################################################

template< class T >
struct CumulativeSum {
  vector< T > data;

  CumulativeSum(int sz) : data(sz, 0) {};

  void add(int k, T x) {
    data[k] += x;
  }

  void build() {
    for(int i = 1; i < data.size(); i++) {
      data[i] += data[i - 1];
    }
  }

  T query(int k) {
    if(k < 0) return (0);
    return (data[min(k, (int) data.size() - 1)]);
  }
};


##################################################
############# cumulative-sum-2d.cpp ##############
##################################################

template< class T >
struct CumulativeSum2D {
  vector< vector< T > > data;

  CumulativeSum2D(int W, int H) : data(W + 1, vector< int >(H + 1, 0)) {}

  void add(int x, int y, T z) {
    ++x, ++y;
    if(x >= data.size() || y >= data[0].size()) return;
    data[x][y] += z;
  }

  void build() {
    for(int i = 1; i < data.size(); i++) {
      for(int j = 1; j < data[i].size(); j++) {
        data[i][j] += data[i][j - 1] + data[i - 1][j] - data[i - 1][j - 1];
      }
    }
  }

  T query(int sx, int sy, int gx, int gy) {
    return (data[gx][gy] - data[sx][gy] - data[gx][sy] + data[sx][sy]);
  }
};


##################################################
############# largest-rectangle.cpp ##############
##################################################

template< typename T >
int64_t largest_rectangle(vector< T > height)
{
  stack< int > st;
  height.push_back(0);
  vector< int > left(height.size());
  int64_t ret = 0;
  for(int i = 0; i < height.size(); i++) {
    while(!st.empty() && height[st.top()] >= height[i]) {
      ret = max(ret, (int64_t) (i - left[st.top()] - 1) * height[st.top()]);
      st.pop();
    }
    left[i] = st.empty() ? -1 : st.top();
    st.emplace(i);
  }
  return (ret);
}


##################################################
################# slide-min.cpp ##################
##################################################

template< typename T >
vector< T > slide_min(const vector< T > &v, int k)
{
  deque< int > deq;
  vector< T > ret;
  for(int i = 0; i < v.size(); i++) {
    while(!deq.empty() && v[deq.back()] >= v[i]) {
      deq.pop_back();
    }
    deq.push_back(i);
    if(i - k + 1 >= 0) {
      ret.emplace_back(v[deq.front()]);
      if(deq.front() == i - k + 1) deq.pop_front();
    }
  }
  return ret;
}


##################################################
####### longest-increasing-subsequence.cpp #######
##################################################

template< typename T >
size_t longest_increasing_subsequence(const vector< T > &a, bool strict) {
  vector< T > lis;
  for(auto &p : a) {
    typename vector< T >::iterator it;
    if(strict) it = lower_bound(begin(lis), end(lis), p);
    else it = upper_bound(begin(lis), end(lis), p);
    if(end(lis) == it) lis.emplace_back(p);
    else *it = p;
  }
  return lis.size();
}


##################################################
############## monotone-minima.cpp ###############
##################################################

template< typename T, typename Compare = less< T > >
vector< pair< int, T > > monotone_minima(int H, int W, const function< T(int, int) > &f, const Compare &comp = Compare()) {
  vector< pair< int, T > > dp(H);
  function< void(int, int, int, int) > dfs = [&](int top, int bottom, int left, int right) {
    if(top > bottom) return;
    int line = (top + bottom) / 2;
    T ma;
    int mi = -1;
    for(int i = left; i <= right; i++) {
      T cst = f(line, i);
      if(mi == -1 || comp(cst, ma)) {
        ma = cst;
        mi = i;
      }
    }
    dp[line] = make_pair(mi, ma);
    dfs(top, line - 1, left, mi);
    dfs(line + 1, bottom, mi, right);
  };
  dfs(0, H - 1, 0, W - 1);
  return dp;
}



##################################################
########### knapsack-limitations-2.cpp ###########
##################################################

template< typename T >
T knapsack_limitations(const vector< T > &w, const vector< T > &m, const vector< int > &v,
                       const T &W) {
  const int N = (int) w.size();
  auto v_max = *max_element(begin(v), end(v));
  if(v_max == 0) return 0;
  vector< int > ma(N);
  vector< T > mb(N);
  for(int i = 0; i < N; i++) {
    ma[i] = min< T >(m[i], v_max - 1);
    mb[i] = m[i] - ma[i];
  }
  T sum = 0;
  for(int i = 0; i < N; i++) sum += ma[i] * v[i];
  auto dp = knapsack_limitations(v, ma, w, sum, T(-1), less<>());
  vector< int > ord(N);
  iota(begin(ord), end(ord), 0);
  sort(begin(ord), end(ord), [&](int a, int b) {
    return v[a] * w[b] > v[b] * w[a];
  });
  T ret = T();
  for(int i = 0; i < dp.size(); i++) {
    if(dp[i] > W || dp[i] == -1) continue;
    T rest = W - dp[i], cost = i;
    for(auto &p : ord) {
      auto get = min(mb[p], rest / w[p]);
      if(get == 0) break;
      cost += get * v[p];
      rest -= get * w[p];
    }
    ret = max(ret, cost);
  }
  return ret;
}


##################################################
###### divide-and-conquer-optimization.cpp #######
##################################################

template< typename T, typename Compare = less< T > >
vector< vector< T > > divide_and_conquer_optimization(int H, int W, T INF, const function< T(int, int) > &f, const Compare &comp = Compare()) {
  vector< vector< T > > dp(H + 1, vector< T >(W + 1, INF));
  dp[0][0] = 0;
  for(int i = 1; i <= H; i++) {
    function< T(int, int) > get_cost = [&](int y, int x) {
      if(x >= y) return INF;
      return dp[i - 1][x] + f(x, y);
    };
    auto ret = monotone_minima(W + 1, W + 1, get_cost, comp);
    for(int j = 0; j <= W; j++) dp[i][j] = ret[j].second;
  }
  return dp;
}


##################################################
################# hu-tucker.cpp ##################
##################################################

te< typename Heap, typename T >
T hu_tucker(vector< T > vs, T INF) {
  int N = (int) vs.size();
  Heap heap;
  vector< typename Heap::Node * > hs(N - 1, heap.makeheap());
  vector< int > ls(N), rs(N);
  vector< T > cs(N - 1);
  using pi = pair< T, int >;
  priority_queue< pi, vector< pi >, greater< pi > > que;
  for(int i = 0; i + 1 < N; i++) {
    ls[i] = i - 1;
    rs[i] = i + 1;
    cs[i] = vs[i] + vs[i + 1];
    que.emplace(cs[i], i);
  }
  T ret = 0;
  for(int k = 0; k + 1 < N; k++) {
    T c;
    int i;
    do {
      tie(c, i) = que.top();
      que.pop();
    } while(rs[i] < 0 || cs[i] != c);
 
    bool ml = false, mr = false;
    if(!heap.empty(hs[i]) && vs[i] + heap.top(hs[i]) == c) {
      heap.pop(hs[i]);
      ml = true;
    } else if(vs[i] + vs[rs[i]] == c) {
      ml = mr = true;
    } else {
      auto top = heap.pop(hs[i]);
      if(!heap.empty(hs[i]) && heap.top(hs[i]) + top == c) {
        heap.pop(hs[i]);
      } else {
        mr = true;
      }
    }
    ret += c;
    heap.push(hs[i], c);
    if(ml) vs[i] = INF;
    if(mr) vs[rs[i]] = INF;
 
    if(ml && i > 0) {
      int j = ls[i];
      hs[j] = heap.merge(hs[j], hs[i]);
      rs[j] = rs[i];
      rs[i] = -1;
      ls[rs[j]] = j;
      i = j;
    }
 
    if(mr && rs[i] + 1 < N) {
      int j = rs[i];
      hs[i] = heap.merge(hs[i], hs[j]);
      rs[i] = rs[j];
      rs[j] = -1;
      ls[rs[i]] = i;
    }
    cs[i] = vs[i] + vs[rs[i]];
 
    if(!heap.empty(hs[i])) {
      T top = heap.pop(hs[i]);
      cs[i] = min(cs[i], min(vs[i], vs[rs[i]]) + top);
      if(!heap.empty(hs[i])) cs[i] = min(cs[i], top + heap.top(hs[i]));
      heap.push(hs[i], top);
    }
    que.emplace(cs[i], i);
  }
  return ret;
}


--------------------------------------------------
|                     string                     |
--------------------------------------------------

##################################################
################## manacher.cpp ##################
##################################################

vector< int > manacher(const string &s) {
  vector< int > radius(s.size());
  int i = 0, j = 0;
  while(i < s.size()) {
    while(i - j >= 0 && i + j < s.size() && s[i - j] == s[i + j]) {
      ++j;
    }
    radius[i] = j;
    int k = 1;
    while(i - k >= 0 && i + k < s.size() && k + radius[i - k] < j) {
      radius[i + k] = radius[i - k];
      ++k;
    }
    i += k;
    j -= k;
  }
  return radius;
}


##################################################
################ rolling-hash.cpp ################
##################################################

template< unsigned mod >
struct RollingHash {
  vector< unsigned > hashed, power;

  inline unsigned mul(unsigned a, unsigned b) const {
    unsigned long long x = (unsigned long long) a * b;
    unsigned xh = (unsigned) (x >> 32), xl = (unsigned) x, d, m;
    asm("divl %4; \n\t" : "=a" (d), "=d" (m) : "d" (xh), "a" (xl), "r" (mod));
    return m;
  }

  RollingHash(const string &s, unsigned base = 10007) {
    int sz = (int) s.size();
    hashed.assign(sz + 1, 0);
    power.assign(sz + 1, 0);
    power[0] = 1;
    for(int i = 0; i < sz; i++) {
      power[i + 1] = mul(power[i], base);
      hashed[i + 1] = mul(hashed[i], base) + s[i];
      if(hashed[i + 1] >= mod) hashed[i + 1] -= mod;
    }
  }

  unsigned get(int l, int r) const {
    unsigned ret = hashed[r] + mod - mul(hashed[l], power[r - l]);
    if(ret >= mod) ret -= mod;
    return ret;
  }

  unsigned connect(unsigned h1, int h2, int h2len) const {
    unsigned ret = mul(h1, power[h2len]) + h2;
    if(ret >= mod) ret -= mod;
    return ret;
  }

  int LCP(const RollingHash< mod > &b, int l1, int r1, int l2, int r2) {
    int len = min(r1 - l1, r2 - l2);
    int low = -1, high = len + 1;
    while(high - low > 1) {
      int mid = (low + high) / 2;
      if(get(l1, l1 + mid) == b.get(l2, l2 + mid)) low = mid;
      else high = mid;
    }
    return (low);
  }
};

using RH = RollingHash< 1000000007 >;


##################################################
################ aho-corasick.cpp ################
##################################################

template< int char_size, int margin >
struct AhoCorasick : Trie< char_size + 1, margin > {
  using Trie< char_size + 1, margin >::Trie;

  const int FAIL = char_size;
  vector< int > correct;

  void build(bool heavy = true) {
    correct.resize(this->size());
    for(int i = 0; i < this->size(); i++) {
      correct[i] = (int) this->nodes[i].accept.size();
    }
    queue< int > que;
    for(int i = 0; i <= char_size; i++) {
      if(~this->nodes[0].nxt[i]) {
        this->nodes[this->nodes[0].nxt[i]].nxt[FAIL] = 0;
        que.emplace(this->nodes[0].nxt[i]);
      } else {
        this->nodes[0].nxt[i] = 0;
      }
    }
    while(!que.empty()) {
      auto &now = this->nodes[que.front()];
      int fail = now.nxt[FAIL];
      correct[que.front()] += correct[fail];
      que.pop();
      for(int i = 0; i < char_size; i++) {
        if(~now.nxt[i]) {
          this->nodes[now.nxt[i]].nxt[FAIL] = this->nodes[fail].nxt[i];
          if(heavy) {
            auto &u = this->nodes[now.nxt[i]].accept;
            auto &v = this->nodes[this->nodes[fail].nxt[i]].accept;
            vector< int > accept;
            set_union(begin(u), end(u), begin(v), end(v), back_inserter(accept));
            u = accept;
          }
          que.emplace(now.nxt[i]);
        } else {
          now.nxt[i] = this->nodes[fail].nxt[i];
        }
      }
    }
  }

  map< int, int > match(const string &str, int now = 0) {
    map< int, int > result;
    for(auto &c : str) {
      now = this->nodes[now].nxt[c - margin];
      for(auto &v : this->nodes[now].accept) result[v] += 1;
    }
    return result;
  }

  pair< int64_t, int > move(const char &c, int now = 0) {
    now = this->nodes[now].nxt[c - margin];
    return {correct[now], now};
  }

  pair< int64_t, int > move(const string &str, int now = 0) {
    int64_t sum = 0;
    for(auto &c : str) {
      auto nxt = move(c, now);
      sum += nxt.first;
      now = nxt.second;
    }
    return {sum, now};
  }
};


##################################################
################ suffix-array.cpp ################
##################################################

struct SuffixArray {
  vector< int > SA;
  const string s;

  SuffixArray(const string &str) : s(str) {
    SA.resize(s.size());
    iota(begin(SA), end(SA), 0);
    sort(begin(SA), end(SA), [&](int a, int b) {
      return s[a] == s[b] ? a > b : s[a] < s[b];
    });
    vector< int > classes(s.size()), c(s.begin(), s.end()), cnt(s.size());
    for(int len = 1; len < s.size(); len <<= 1) {
      for(int i = 0; i < s.size(); i++) {
        if(i > 0 && c[SA[i - 1]] == c[SA[i]] && SA[i - 1] + len < s.size() && c[SA[i - 1] + len / 2] == c[SA[i] + len / 2]) {
          classes[SA[i]] = classes[SA[i - 1]];
        } else {
          classes[SA[i]] = i;
        }
      }
      iota(begin(cnt), end(cnt), 0);
      copy(begin(SA), end(SA), begin(c));
      for(int i = 0; i < s.size(); i++) {
        int s1 = c[i] - len;
        if(s1 >= 0) SA[cnt[classes[s1]]++] = s1;
      }
      classes.swap(c);
    }
  }

  int operator[](int k) const {
    return SA[k];
  }

  size_t size() const {
    return s.size();
  }

  bool lt_substr(const string &t, int si = 0, int ti = 0) {
    int sn = (int) s.size(), tn = (int) t.size();
    while(si < sn && ti < tn) {
      if(s[si] < t[ti]) return true;
      if(s[si] > t[ti]) return false;
      ++si, ++ti;
    }
    return si >= sn && ti < tn;
  }

  int lower_bound(const string &t) {
    int low = -1, high = (int) SA.size();
    while(high - low > 1) {
      int mid = (low + high) / 2;
      if(lt_substr(t, SA[mid])) low = mid;
      else high = mid;
    }
    return high;
  }

  pair< int, int > lower_upper_bound(string &t) {
    int idx = lower_bound(t);
    int low = idx - 1, high = (int) SA.size();
    t.back()++;
    while(high - low > 1) {
      int mid = (low + high) / 2;
      if(lt_substr(t, SA[mid])) low = mid;
      else high = mid;
    }
    t.back()--;
    return {idx, high};
  }

  void output() {
    for(int i = 0; i < size(); i++) {
      cout << i << ": " << s.substr(SA[i]) << endl;
    }
  }
};


##################################################
######## longest-common-prefix-array.cpp #########
##################################################

struct LongestCommonPrefixArray {
  const SuffixArray &SA;
  vector< int > LCP, rank;

  LongestCommonPrefixArray(const SuffixArray &SA) : SA(SA), LCP(SA.size()) {
    rank.resize(SA.size());
    for(int i = 0; i < SA.size(); i++) {
      rank[SA[i]] = i;
    }
    for(int i = 0, h = 0; i < SA.size(); i++) {
      if(rank[i] + 1 < SA.size()) {
        for(int j = SA[rank[i] + 1]; max(i, j) + h < SA.size() && SA.s[i + h] == SA.s[j + h]; ++h);
        LCP[rank[i] + 1] = h;
        if(h > 0) --h;
      }
    }
  }

  int operator[](int k) const {
    return LCP[k];
  }

  size_t size() const {
    return LCP.size();
  }

  void output() {
    for(int i = 0; i < size(); i++) {
      cout << i << ": " << LCP[i] << " " << SA.s.substr(SA[i]) << endl;
    }
  }
};


##################################################
################ z-algorithm.cpp #################
##################################################

vector< int > z_algorithm(const string &s) {
  vector< int > prefix(s.size());
  for(int i = 1, j = 0; i < s.size(); i++) {
    if(i + prefix[i - j] < j + prefix[j]) {
      prefix[i] = prefix[i - j];
    } else {
      int k = max(0, j + prefix[j] - i);
      while(i + k < s.size() && s[k] == s[i + k]) ++k;
      prefix[i] = k;
      j = i;
    }
  }
  prefix[0] = (int) s.size();
  return prefix;
}


--------------------------------------------------
|                    geometry                    |
--------------------------------------------------

##################################################
################## template.cpp ##################
##################################################

using Real = double;
using Point = complex< Real >;
const Real EPS = 1e-8, PI = acos(-1);

inline bool eq(Real a, Real b) { return fabs(b - a) < EPS; }

Point operator*(const Point &p, const Real &d) {
  return Point(real(p) * d, imag(p) * d);
}

istream &operator>>(istream &is, Point &p) {
  Real a, b;
  is >> a >> b;
  p = Point(a, b);
  return is;
}

ostream &operator<<(ostream &os, Point &p) {
  return os << fixed << setprecision(10) << p.real() << " " << p.imag();
}

// rotate point p counterclockwise by theta rad
Point rotate(Real theta, const Point &p) {
  return Point(cos(theta) * p.real() - sin(theta) * p.imag(), sin(theta) * p.real() + cos(theta) * p.imag());
}

Real radian_to_degree(Real r) {
  return (r * 180.0 / PI);
}

Real degree_to_radian(Real d) {
  return (d * PI / 180.0);
}

// smaller angle of the a-b-c
Real get_angle(const Point &a, const Point &b, const Point &c) {
  const Point v(b - a), w(c - b);
  Real alpha = atan2(v.imag(), v.real()), beta = atan2(w.imag(), w.real());
  if(alpha > beta) swap(alpha, beta);
  Real theta = (beta - alpha);
  return min(theta, 2 * acos(-1) - theta);
}

namespace std {
  bool operator<(const Point &a, const Point &b) {
    return a.real() != b.real() ? a.real() < b.real() : a.imag() < b.imag();
  }
}


struct Line {
  Point a, b;

  Line() = default;

  Line(Point a, Point b) : a(a), b(b) {}

  Line(Real A, Real B, Real C) // Ax + By = C
  {
    if(eq(A, 0)) a = Point(0, C / B), b = Point(1, C / B);
    else if(eq(B, 0)) b = Point(C / A, 0), b = Point(C / A, 1);
    else a = Point(0, C / B), b = Point(C / A, 0);
  }

  friend ostream &operator<<(ostream &os, Line &p) {
    return os << p.a << " to " << p.b;
  }

  friend istream &operator>>(istream &is, Line &a) {
    return is >> a.a >> a.b;
  }
};

struct Segment : Line {
  Segment() = default;

  Segment(Point a, Point b) : Line(a, b) {}
};

struct Circle {
  Point p;
  Real r;

  Circle() = default;

  Circle(Point p, Real r) : p(p), r(r) {}
};

using Points = vector< Point >;
using Polygon = vector< Point >;
using Segments = vector< Segment >;
using Lines = vector< Line >;
using Circles = vector< Circle >;

Real cross(const Point &a, const Point &b) {
  return real(a) * imag(b) - imag(a) * real(b);
}

Real dot(const Point &a, const Point &b) {
  return real(a) * real(b) + imag(a) * imag(b);
}

// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_1_C
int ccw(const Point &a, Point b, Point c) {
  b = b - a, c = c - a;
  if(cross(b, c) > EPS) return +1;  // "COUNTER_CLOCKWISE"
  if(cross(b, c) < -EPS) return -1; // "CLOCKWISE"
  if(dot(b, c) < 0) return +2;      // "ONLINE_BACK" c-a-b
  if(norm(b) < norm(c)) return -2;  // "ONLINE_FRONT" a-b-c
  return 0;                         // "ON_SEGMENT" a-c-b
}

// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_2_A
bool parallel(const Line &a, const Line &b) {
  return eq(cross(a.b - a.a, b.b - b.a), 0.0);
}

// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_2_A
bool orthogonal(const Line &a, const Line &b) {
  return eq(dot(a.a - a.b, b.a - b.b), 0.0);
}

// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_1_A
Point projection(const Line &l, const Point &p) {
  double t = dot(p - l.a, l.a - l.b) / norm(l.a - l.b);
  return l.a + (l.a - l.b) * t;
}

Point projection(const Segment &l, const Point &p) {
  double t = dot(p - l.a, l.a - l.b) / norm(l.a - l.b);
  return l.a + (l.a - l.b) * t;
}

// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_1_B
Point reflection(const Line &l, const Point &p) {
  return p + (projection(l, p) - p) * 2.0;
}

bool intersect(const Line &l, const Point &p) {
  return abs(ccw(l.a, l.b, p)) != 1;
}

bool intersect(const Line &l, const Line &m) {
  return abs(cross(l.b - l.a, m.b - m.a)) > EPS || abs(cross(l.b - l.a, m.b - l.a)) < EPS;
}

bool intersect(const Segment &s, const Point &p) {
  return ccw(s.a, s.b, p) == 0;
}

bool intersect(const Line &l, const Segment &s) {
  return cross(l.b - l.a, s.a - l.a) * cross(l.b - l.a, s.b - l.a) < EPS;
}

Real distance(const Line &l, const Point &p);

bool intersect(const Circle &c, const Line &l) {
  return distance(l, c.p) <= c.r + EPS;
}

bool intersect(const Circle &c, const Point &p) {
  return abs(abs(p - c.p) - c.r) < EPS;
}

// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_2_B
bool intersect(const Segment &s, const Segment &t) {
  return ccw(s.a, s.b, t.a) * ccw(s.a, s.b, t.b) <= 0 && ccw(t.a, t.b, s.a) * ccw(t.a, t.b, s.b) <= 0;
}

int intersect(const Circle &c, const Segment &l) {
  if(norm(projection(l, c.p) - c.p) - c.r * c.r > EPS) return 0;
  auto d1 = abs(c.p - l.a), d2 = abs(c.p - l.b);
  if(d1 < c.r + EPS && d2 < c.r + EPS) return 0;
  if(d1 < c.r - EPS && d2 > c.r + EPS || d1 > c.r + EPS && d2 < c.r - EPS) return 1;
  const Point h = projection(l, c.p);
  if(dot(l.a - h, l.b - h) < 0) return 2;
  return 0;
}

// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_7_A&lang=jp
int intersect(Circle c1, Circle c2) {
  if(c1.r < c2.r) swap(c1, c2);
  Real d = abs(c1.p - c2.p);
  if(c1.r + c2.r < d) return 4;
  if(eq(c1.r + c2.r, d)) return 3;
  if(c1.r - c2.r < d) return 2;
  if(eq(c1.r - c2.r, d)) return 1;
  return 0;
}

Real distance(const Point &a, const Point &b) {
  return abs(a - b);
}

Real distance(const Line &l, const Point &p) {
  return abs(p - projection(l, p));
}

Real distance(const Line &l, const Line &m) {
  return intersect(l, m) ? 0 : distance(l, m.a);
}

Real distance(const Segment &s, const Point &p) {
  Point r = projection(s, p);
  if(intersect(s, r)) return abs(r - p);
  return min(abs(s.a - p), abs(s.b - p));
}

// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_2_D
Real distance(const Segment &a, const Segment &b) {
  if(intersect(a, b)) return 0;
  return min({distance(a, b.a), distance(a, b.b), distance(b, a.a), distance(b, a.b)});
}

Real distance(const Line &l, const Segment &s) {
  if(intersect(l, s)) return 0;
  return min(distance(l, s.a), distance(l, s.b));
}

Point crosspoint(const Line &l, const Line &m) {
  Real A = cross(l.b - l.a, m.b - m.a);
  Real B = cross(l.b - l.a, l.b - m.a);
  if(eq(abs(A), 0.0) && eq(abs(B), 0.0)) return m.a;
  return m.a + (m.b - m.a) * B / A;
}

// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_2_C
Point crosspoint(const Segment &l, const Segment &m) {
  return crosspoint(Line(l), Line(m));
}

// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_7_D
pair< Point, Point > crosspoint(const Circle &c, const Line l) {
  Point pr = projection(l, c.p);
  Point e = (l.b - l.a) / abs(l.b - l.a);
  if(eq(distance(l, c.p), c.r)) return {pr, pr};
  double base = sqrt(c.r * c.r - norm(pr - c.p));
  return {pr - e * base, pr + e * base};
}

pair< Point, Point > crosspoint(const Circle &c, const Segment &l) {
  Line aa = Line(l.a, l.b);
  if(intersect(c, l) == 2) return crosspoint(c, aa);
  auto ret = crosspoint(c, aa);
  if(dot(l.a - ret.first, l.b - ret.first) < 0) ret.second = ret.first;
  else ret.first = ret.second;
  return ret;
}

// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_7_E
pair< Point, Point > crosspoint(const Circle &c1, const Circle &c2) {
  Real d = abs(c1.p - c2.p);
  Real a = acos((c1.r * c1.r + d * d - c2.r * c2.r) / (2 * c1.r * d));
  Real t = atan2(c2.p.imag() - c1.p.imag(), c2.p.real() - c1.p.real());
  Point p1 = c1.p + Point(cos(t + a) * c1.r, sin(t + a) * c1.r);
  Point p2 = c1.p + Point(cos(t - a) * c1.r, sin(t - a) * c1.r);
  return {p1, p2};
}

// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_7_F
// tangent of circle c through point p
pair< Point, Point > tangent(const Circle &c1, const Point &p2) {
  return crosspoint(c1, Circle(p2, sqrt(norm(c1.p - p2) - c1.r * c1.r)));
}

// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_7_G
// common tangent of circles c1 and c2
Lines tangent(Circle c1, Circle c2) {
  Lines ret;
  if(c1.r < c2.r) swap(c1, c2);
  Real g = norm(c1.p - c2.p);
  if(eq(g, 0)) return ret;
  Point u = (c2.p - c1.p) / sqrt(g);
  Point v = rotate(PI * 0.5, u);
  for(int s : {-1, 1}) {
    Real h = (c1.r + s * c2.r) / sqrt(g);
    if(eq(1 - h * h, 0)) {
      ret.emplace_back(c1.p + u * c1.r, c1.p + (u + v) * c1.r);
    } else if(1 - h * h > 0) {
      Point uu = u * h, vv = v * sqrt(1 - h * h);
      ret.emplace_back(c1.p + (uu + vv) * c1.r, c2.p - (uu + vv) * c2.r * s);
      ret.emplace_back(c1.p + (uu - vv) * c1.r, c2.p - (uu - vv) * c2.r * s);
    }
  }
  return ret;
}

// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_3_B
bool is_convex(const Polygon &p) {
  int n = (int) p.size();
  for(int i = 0; i < n; i++) {
    if(ccw(p[(i + n - 1) % n], p[i], p[(i + 1) % n]) == -1) return false;
  }
  return true;
}

// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_4_A
Polygon convex_hull(Polygon &p) {
  int n = (int) p.size(), k = 0;
  if(n <= 2) return p;
  sort(p.begin(), p.end());
  vector< Point > ch(2 * n);
  for(int i = 0; i < n; ch[k++] = p[i++]) {
    while(k >= 2 && cross(ch[k - 1] - ch[k - 2], p[i] - ch[k - 1]) < EPS) --k;
  }
  for(int i = n - 2, t = k + 1; i >= 0; ch[k++] = p[i--]) {
    while(k >= t && cross(ch[k - 1] - ch[k - 2], p[i] - ch[k - 1]) < EPS) --k;
  }
  ch.resize(k - 1);
  return ch;
}

// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_3_C
enum {
  OUT, ON, IN
};

int contains(const Polygon &Q, const Point &p) {
  bool in = false;
  for(int i = 0; i < Q.size(); i++) {
    Point a = Q[i] - p, b = Q[(i + 1) % Q.size()] - p;
    if(a.imag() > b.imag()) swap(a, b);
    if(a.imag() <= 0 && 0 < b.imag() && cross(a, b) < 0) in = !in;
    if(cross(a, b) == 0 && dot(a, b) <= 0) return ON;
  }
  return in ? IN : OUT;
}


// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=1033
// deduplication of line segments
void merge_segments(vector< Segment > &segs) {

  auto merge_if_able = [](Segment &s1, const Segment &s2) {
    if(abs(cross(s1.b - s1.a, s2.b - s2.a)) > EPS) return false;
    if(ccw(s1.a, s2.a, s1.b) == 1 || ccw(s1.a, s2.a, s1.b) == -1) return false;
    if(ccw(s1.a, s1.b, s2.a) == -2 || ccw(s2.a, s2.b, s1.a) == -2) return false;
    s1 = Segment(min(s1.a, s2.a), max(s1.b, s2.b));
    return true;
  };

  for(int i = 0; i < segs.size(); i++) {
    if(segs[i].b < segs[i].a) swap(segs[i].a, segs[i].b);
  }
  for(int i = 0; i < segs.size(); i++) {
    for(int j = i + 1; j < segs.size(); j++) {
      if(merge_if_able(segs[i], segs[j])) {
        segs[j--] = segs.back(), segs.pop_back();
      }
    }
  }
}

// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=1033
// construct a graph with the vertex of the intersection of any two line segments
vector< vector< int > > segment_arrangement(vector< Segment > &segs, vector< Point > &ps) {
  vector< vector< int > > g;
  int N = (int) segs.size();
  for(int i = 0; i < N; i++) {
    ps.emplace_back(segs[i].a);
    ps.emplace_back(segs[i].b);
    for(int j = i + 1; j < N; j++) {
      const Point p1 = segs[i].b - segs[i].a;
      const Point p2 = segs[j].b - segs[j].a;
      if(cross(p1, p2) == 0) continue;
      if(intersect(segs[i], segs[j])) {
        ps.emplace_back(crosspoint(segs[i], segs[j]));
      }
    }
  }
  sort(begin(ps), end(ps));
  ps.erase(unique(begin(ps), end(ps)), end(ps));

  int M = (int) ps.size();
  g.resize(M);
  for(int i = 0; i < N; i++) {
    vector< int > vec;
    for(int j = 0; j < M; j++) {
      if(intersect(segs[i], ps[j])) {
        vec.emplace_back(j);
      }
    }
    for(int j = 1; j < vec.size(); j++) {
      g[vec[j - 1]].push_back(vec[j]);
      g[vec[j]].push_back(vec[j - 1]);
    }
  }
  return (g);
}

// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_4_C
// cut with a straight line l and return a convex polygon on the left
Polygon convex_cut(const Polygon &U, Line l) {
  Polygon ret;
  for(int i = 0; i < U.size(); i++) {
    Point now = U[i], nxt = U[(i + 1) % U.size()];
    if(ccw(l.a, l.b, now) != -1) ret.push_back(now);
    if(ccw(l.a, l.b, now) * ccw(l.a, l.b, nxt) < 0) {
      ret.push_back(crosspoint(Line(now, nxt), l));
    }
  }
  return (ret);
}

// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_3_A
Real area(const Polygon &p) {
  Real A = 0;
  for(int i = 0; i < p.size(); ++i) {
    A += cross(p[i], p[(i + 1) % p.size()]);
  }
  return A * 0.5;
}

// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_7_H
Real area(const Polygon &p, const Circle &c) {
  if(p.size() < 3) return 0.0;
  function< Real(Circle, Point, Point) > cross_area = [&](const Circle &c, const Point &a, const Point &b) {
    Point va = c.p - a, vb = c.p - b;
    Real f = cross(va, vb), ret = 0.0;
    if(eq(f, 0.0)) return ret;
    if(max(abs(va), abs(vb)) < c.r + EPS) return f;
    if(distance(Segment(a, b), c.p) > c.r - EPS) return c.r * c.r * arg(vb * conj(va));
    auto u = crosspoint(c, Segment(a, b));
    vector< Point > tot{a, u.first, u.second, b};
    for(int i = 0; i + 1 < tot.size(); i++) {
      ret += cross_area(c, tot[i], tot[i + 1]);
    }
    return ret;
  };
  Real A = 0;
  for(int i = 0; i < p.size(); i++) {
    A += cross_area(c, p[i], p[(i + 1) % p.size()]);
  }
  return A;
}

// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_4_B
Real convex_diameter(const Polygon &p) {
  int N = (int) p.size();
  int is = 0, js = 0;
  for(int i = 1; i < N; i++) {
    if(p[i].imag() > p[is].imag()) is = i;
    if(p[i].imag() < p[js].imag()) js = i;
  }
  Real maxdis = norm(p[is] - p[js]);

  int maxi, maxj, i, j;
  i = maxi = is;
  j = maxj = js;
  do {
    if(cross(p[(i + 1) % N] - p[i], p[(j + 1) % N] - p[j]) >= 0) {
      j = (j + 1) % N;
    } else {
      i = (i + 1) % N;
    }
    if(norm(p[i] - p[j]) > maxdis) {
      maxdis = norm(p[i] - p[j]);
      maxi = i;
      maxj = j;
    }
  } while(i != is || j != js);
  return sqrt(maxdis);
}

// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_5_A
Real closest_pair(Points ps) {
  if(ps.size() <= 1) throw (0);
  sort(begin(ps), end(ps));

  auto compare_y = [&](const Point &a, const Point &b) {
    return imag(a) < imag(b);
  };
  vector< Point > beet(ps.size());
  const Real INF = 1e18;

  function< Real(int, int) > rec = [&](int left, int right) {
    if(right - left <= 1) return INF;
    int mid = (left + right) >> 1;
    auto x = real(ps[mid]);
    auto ret = min(rec(left, mid), rec(mid, right));
    inplace_merge(begin(ps) + left, begin(ps) + mid, begin(ps) + right, compare_y);
    int ptr = 0;
    for(int i = left; i < right; i++) {
      if(abs(real(ps[i]) - x) >= ret) continue;
      for(int j = 0; j < ptr; j++) {
        auto luz = ps[i] - beet[ptr - j - 1];
        if(imag(luz) >= ret) break;
        ret = min(ret, abs(luz));
      }
      beet[ptr++] = ps[i];
    }
    return ret;
  };
  return rec(0, (int) ps.size());
}


--------------------------------------------------
|                   structure                    |
--------------------------------------------------

##################################################
####### convex-hull-trick-add-monotone.cpp #######
##################################################

template< typename T, bool isMin >
struct ConvexHullTrickAddMonotone {
#define F first
#define S second
  using P = pair< T, T >;
  deque< P > H;

  ConvexHullTrickAddMonotone() = default;

  bool empty() const { return H.empty(); }

  void clear() { H.clear(); }

  inline int sgn(T x) { return x == 0 ? 0 : (x < 0 ? -1 : 1); }

  using D = long double;

  inline bool check(const P &a, const P &b, const P &c) {
    if(b.S == a.S || c.S == b.S)
      return sgn(b.F - a.F) * sgn(c.S - b.S) >= sgn(c.F - b.F) * sgn(b.S - a.S);

    //return (b.F-a.F)*(c.S-b.S) >= (b.S-a.S)*(c.F-b.F);
    return
        D(b.F - a.F) * sgn(c.S - b.S) / D(abs(b.S - a.S)) >=
        D(c.F - b.F) * sgn(b.S - a.S) / D(abs(c.S - b.S));
  }

  void add(T a, T b) {
    if(!isMin) a *= -1, b *= -1;
    P line(a, b);
    if(empty()) {
      H.emplace_front(line);
      return;
    }
    if(H.front().F <= a) {
      if(H.front().F == a) {
        if(H.front().S <= b) return;
        H.pop_front();
      }
      while(H.size() >= 2 && check(line, H.front(), H[1])) H.pop_front();
      H.emplace_front(line);
    } else {
      assert(a <= H.back().F);
      if(H.back().F == a) {
        if(H.back().S <= b) return;
        H.pop_back();
      }
      while(H.size() >= 2 && check(H[H.size() - 2], H.back(), line)) H.pop_back();
      H.emplace_back(line);
    }
  }

  inline T get_y(const P &a, const T &x) {
    return a.F * x + a.S;
  }

  T query(T x) {
    assert(!empty());
    int l = -1, r = H.size() - 1;
    while(l + 1 < r) {
      int m = (l + r) >> 1;
      if(get_y(H[m], x) >= get_y(H[m + 1], x)) l = m;
      else r = m;
    }
    if(isMin) return get_y(H[r], x);
    return -get_y(H[r], x);
  }

  T query_monotone_inc(T x) {
    assert(!empty());
    while(H.size() >= 2 && get_y(H.front(), x) >= get_y(H[1], x)) H.pop_front();
    if(isMin) return get_y(H.front(), x);
    return -get_y(H.front(), x);
  }

  T query_monotone_dec(T x) {
    assert(!empty());
    while(H.size() >= 2 && get_y(H.back(), x) >= get_y(H[H.size() - 2], x)) H.pop_back();
    if(isMin) return get_y(H.back(), x);
    return -get_y(H.back(), x);
  }

#undef F
#undef S
};


##################################################
################# skew-heap.cpp ##################
##################################################

template< typename T, typename E = T >
struct SkewHeap {
  using G = function< T(T, E) >;
  using H = function< E(E, E) >;
 
  struct Node {
    T key;
    E lazy;
    Node *l, *r;
  };
 
  const bool rev;
  const G g;
  const H h;
 
  SkewHeap(bool rev = false) : g([](const T &a, const E &b) { return a + b; }),
                               h([](const E &a, const E &b) { return a + b; }), rev(rev) {}
 
  SkewHeap(const G &g, const H &h, bool rev = false) : g(g), h(h), rev(rev) {}
 
  Node *propagate(Node *t) {
    if(t->lazy != 0) {
      if(t->l) t->l->lazy = h(t->l->lazy, t->lazy);
      if(t->r) t->r->lazy = h(t->r->lazy, t->lazy);
      t->key = g(t->key, t->lazy);
      t->lazy = 0;
    }
    return t;
  }
 
  Node *merge(Node *x, Node *y) {
    if(!x || !y) return x ? x : y;
    propagate(x), propagate(y);
    if((x->key > y->key) ^ rev) swap(x, y);
    x->r = merge(y, x->r);
    swap(x->l, x->r);
    return x;
  }
 
  void push(Node *&root, const T &key) {
    root = merge(root, new Node({key, 0, nullptr, nullptr}));
  }
 
  T top(Node *root) {
    return propagate(root)->key;
  }
 
  T pop(Node *&root) {
    T top = propagate(root)->key;
    auto *temp = root;
    root = merge(root->l, root->r);
    delete temp;
    return top;
  }
 
  bool empty(Node *root) const {
    return !root;
  }
 
  void add(Node *root, const E &lazy) {
    if(root) {
      root->lazy = h(root->lazy, lazy);
      propagate(root);
    }
  }
 
  Node *makeheap() {
    return nullptr;
  }
};


##################################################
############# segment-tree-2d-2.cpp ##############
##################################################

template< typename structure_t, typename get_t, typename update_t >
struct SegmentTree2D {
  using merge_f = function< get_t(get_t, get_t) >;
  using get_t = function< get_t(structure_t &, int) >;
  using range_update_f = function< get_t(structure_t &, int, int, update_t) >;

  int sz;
  vector< structure_t > seg;
  const merge_f &f;
  const get_t &g;
  const range_update_f &h;

  SegmentTree2D(int n, const merge_f &f, const get_t &g, const range_update_f &h) : f(f), g(g), h(h) {
    sz = 1;
    while(sz < n) sz <<= 1;
    seg.resize(2 * sz - 1);
  }

  void update(int a, int b, int lower, int upper, update_t x, int k, int l, int r) {
    if(r <= a || b <= l) {
      return;
    } else if(a <= l && r <= b) {
      g(seg[k], lower, upper, x);
    } else {
      update(a, b, lower, upper, x, 2 * k + 1, l, (l + r) >> 1);
      update(a, b, lower, upper, x, 2 * k + 2, (l + r) >> 1, r);
    }
  }

  void update(int a, int b, int l, int r, update_t x) {
    update(a, b, l, r, x, 0, 0, sz);
  }

  get_t get(int x, int y) {
    x += sz - 1;
    get_t ret = g(seg[x], y);
    while(x > 0) {
      x = (x - 1) >> 1;
      ret = f(ret, g(seg[x], y));
    }
  }
};


##################################################
############# lazy-segment-tree.cpp ##############
##################################################

template< typename Monoid, typename OperatorMonoid = Monoid >
struct LazySegmentTree {
  using F = function< Monoid(Monoid, Monoid) >;
  using G = function< Monoid(Monoid, OperatorMonoid) >;
  using H = function< OperatorMonoid(OperatorMonoid, OperatorMonoid) >;

  int sz, height;
  vector< Monoid > data;
  vector< OperatorMonoid > lazy;
  const F f;
  const G g;
  const H h;
  const Monoid M1;
  const OperatorMonoid OM0;


  LazySegmentTree(int n, const F f, const G g, const H h,
                  const Monoid &M1, const OperatorMonoid OM0)
      : f(f), g(g), h(h), M1(M1), OM0(OM0) {
    sz = 1;
    height = 0;
    while(sz < n) sz <<= 1, height++;
    data.assign(2 * sz, M1);
    lazy.assign(2 * sz, OM0);
  }

  void set(int k, const Monoid &x) {
    data[k + sz] = x;
  }

  void build() {
    for(int k = sz - 1; k > 0; k--) {
      data[k] = f(data[2 * k + 0], data[2 * k + 1]);
    }
  }

  inline void propagate(int k) {
    if(lazy[k] != OM0) {
      lazy[2 * k + 0] = h(lazy[2 * k + 0], lazy[k]);
      lazy[2 * k + 1] = h(lazy[2 * k + 1], lazy[k]);
      data[k] = reflect(k);
      lazy[k] = OM0;
    }
  }

  inline Monoid reflect(int k) {
    return lazy[k] == OM0 ? data[k] : g(data[k], lazy[k]);
  }

  inline void recalc(int k) {
    while(k >>= 1) data[k] = f(reflect(2 * k + 0), reflect(2 * k + 1));
  }

  inline void thrust(int k) {
    for(int i = height; i > 0; i--) propagate(k >> i);
  }

  void update(int a, int b, const OperatorMonoid &x) {
    thrust(a += sz);
    thrust(b += sz - 1);
    for(int l = a, r = b + 1; l < r; l >>= 1, r >>= 1) {
      if(l & 1) lazy[l] = h(lazy[l], x), ++l;
      if(r & 1) --r, lazy[r] = h(lazy[r], x);
    }
    recalc(a);
    recalc(b);
  }

  Monoid query(int a, int b) {
    thrust(a += sz);
    thrust(b += sz - 1);
    Monoid L = M1, R = M1;
    for(int l = a, r = b + 1; l < r; l >>= 1, r >>= 1) {
      if(l & 1) L = f(L, reflect(l++));
      if(r & 1) R = f(reflect(--r), R);
    }
    return f(L, R);
  }

  Monoid operator[](const int &k) {
    return query(k, k + 1);
  }

  template< typename C >
  int find_subtree(int a, const C &check, Monoid &M, bool type) {
    while(a < sz) {
      propagate(a);
      Monoid nxt = type ? f(reflect(2 * a + type), M) : f(M, reflect(2 * a + type));
      if(check(nxt)) a = 2 * a + type;
      else M = nxt, a = 2 * a + 1 - type;
    }
    return a - sz;
  }

  template< typename C >
  int find_first(int a, const C &check) {
    Monoid L = M1;
    if(a <= 0) {
      if(check(f(L, reflect(1)))) return find_subtree(1, check, L, false);
      return -1;
    }
    thrust(a + sz);
    int b = sz;
    for(a += sz, b += sz; a < b; a >>= 1, b >>= 1) {
      if(a & 1) {
        Monoid nxt = f(L, reflect(a));
        if(check(nxt)) return find_subtree(a, check, L, false);
        L = nxt;
        ++a;
      }
    }
    return -1;
  }


  template< typename C >
  int find_last(int b, const C &check) {
    Monoid R = M1;
    if(b >= sz) {
      if(check(f(reflect(1), R))) return find_subtree(1, check, R, true);
      return -1;
    }
    thrust(b + sz - 1);
    int a = sz;
    for(b += sz; a < b; a >>= 1, b >>= 1) {
      if(b & 1) {
        Monoid nxt = f(reflect(--b), R);
        if(check(nxt)) return find_subtree(b, check, R, true);
        R = nxt;
      }
    }
    return -1;
  }
};


##################################################
###### partially-persistent-union-find.cpp #######
##################################################

struct PartiallyPersistentUnionFind {
  vector< int > data;
  vector< int > last;
  vector< vector< pair< int, int > > > add;

  PartiallyPersistentUnionFind() {}

  PartiallyPersistentUnionFind(int sz) : data(sz, -1), last(sz, 1e9), add(sz) {
    for(auto &vs : add) vs.emplace_back(-1, -1);
  }

  bool unite(int t, int x, int y) {
    x = find(t, x);
    y = find(t, y);
    if(x == y) return false;
    if(data[x] > data[y]) swap(x, y);
    data[x] += data[y];
    add[x].emplace_back(t, data[x]);
    data[y] = x;
    last[y] = t;
    return true;
  }

  int find(int t, int x) {
    if(t < last[x]) return x;
    return find(t, data[x]);
  }

  int size(int t, int x) {
    x = find(t, x);
    return -prev(lower_bound(begin(add[x]), end(add[x]), make_pair(t, 0)))->second;
  }
};


##################################################
############ binary-indexed-tree.cpp #############
##################################################

template< typename T >
struct BinaryIndexedTree {
  vector< T > data;

  BinaryIndexedTree(int sz) {
    data.assign(++sz, 0);
  }

  T sum(int k) {
    T ret = 0;
    for(++k; k > 0; k -= k & -k) ret += data[k];
    return (ret);
  }

  void add(int k, T x) {
    for(++k; k < data.size(); k += k & -k) data[k] += x;
  }
};


##################################################
################# union-find.cpp #################
##################################################

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


##################################################
########### link-cut-tree-subtree.cpp ############
##################################################

template< typename SUM, typename KEY >
struct LinkCutTreeSubtree {
 
  struct Node {
    Node *l, *r, *p;
 
    KEY key;
    SUM sum;
 
    bool rev;
    int sz;
 
    bool is_root() const {
      return !p || (p->l != this && p->r != this);
    }
 
    Node(const KEY &key, const SUM &sum) :
        key(key), sum(sum), rev(false), sz(1),
        l(nullptr), r(nullptr), p(nullptr) {}
  };
 
  const SUM ident;
 
  LinkCutTreeSubtree(const SUM &ident) : ident(ident) {}
 
  Node *make_node(const KEY &key) {
    auto ret = new Node(key, ident);
    update(ret);
    return ret;
  }
 
  Node *set_key(Node *t, const KEY &key) {
    expose(t);
    t->key = key;
    update(t);
    return t;
  }
 
  void toggle(Node *t) {
    swap(t->l, t->r);
    t->sum.toggle();
    t->rev ^= true;
  }
 
  void push(Node *t) {
    if(t->rev) {
      if(t->l) toggle(t->l);
      if(t->r) toggle(t->r);
      t->rev = false;
    }
  }
 
 
  void update(Node *t) {
    t->sz = 1;
    if(t->l) t->sz += t->l->sz;
    if(t->r) t->sz += t->r->sz;
    t->sum.merge(t->key, t->l ? t->l->sum : ident, t->r ? t->r->sum : ident);
  }
 
  void rotr(Node *t) {
    auto *x = t->p, *y = x->p;
    if((x->l = t->r)) t->r->p = x;
    t->r = x, x->p = t;
    update(x), update(t);
    if((t->p = y)) {
      if(y->l == x) y->l = t;
      if(y->r == x) y->r = t;
      update(y);
    }
  }
 
  void rotl(Node *t) {
    auto *x = t->p, *y = x->p;
    if((x->r = t->l)) t->l->p = x;
    t->l = x, x->p = t;
    update(x), update(t);
    if((t->p = y)) {
      if(y->l == x) y->l = t;
      if(y->r == x) y->r = t;
      update(y);
    }
  }
 
 
  void splay(Node *t) {
    push(t);
    while(!t->is_root()) {
      auto *q = t->p;
      if(q->is_root()) {
        push(q), push(t);
        if(q->l == t) rotr(t);
        else rotl(t);
      } else {
        auto *r = q->p;
        push(r), push(q), push(t);
        if(r->l == q) {
          if(q->l == t) rotr(q), rotr(t);
          else rotl(t), rotr(t);
        } else {
          if(q->r == t) rotl(q), rotl(t);
          else rotr(t), rotl(t);
        }
      }
    }
  }
 
 
  Node *expose(Node *t) {
    Node *rp = nullptr;
    for(auto *cur = t; cur; cur = cur->p) {
      splay(cur);
      if(cur->r) cur->sum.add(cur->r->sum);
      cur->r = rp;
      if(cur->r) cur->sum.erase(cur->r->sum);
      update(cur);
      rp = cur;
    }
    splay(t);
    return rp;
  }
 
  void link(Node *child, Node *parent) {
    expose(child);
    expose(parent);
    child->p = parent;
    parent->r = child;
    update(parent);
  }
 
  void cut(Node *child) {
    expose(child);
    auto *parent = child->l;
    child->l = nullptr;
    parent->p = nullptr;
    update(child);
  }
 
  void evert(Node *t) {
    expose(t);
    toggle(t);
    push(t);
  }
 
  Node *lca(Node *u, Node *v) {
    if(get_root(u) != get_root(v)) return nullptr;
    expose(u);
    return expose(v);
  }
 
 
  Node *get_kth(Node *x, int k) {
    expose(x);
    while(x) {
      push(x);
      if(x->r && x->r->sz > k) {
        x = x->r;
      } else {
        if(x->r) k -= x->r->sz;
        if(k == 0) return x;
        k -= 1;
        x = x->l;
      }
    }
    return nullptr;
  }
 
  Node *get_root(Node *x) {
    expose(x);
    while(x->l) {
      push(x);
      x = x->l;
    }
    return x;
  }
 
  SUM &query(Node *t) {
    expose(t);
    return t->sum;
  }
};


##################################################
##### segment-tree-fractional-cascading.cpp ######
##################################################

struct SegmentTreeFractionalCascading {
  vector< vector< int > > seg;
  vector< vector< int > > LL, RR;
  int sz;

  SegmentTreeFractionalCascading(vector< int > &array) {
    sz = 1;
    while(sz < array.size()) sz <<= 1;
    seg.resize(2 * sz - 1);
    LL.resize(2 * sz - 1);
    RR.resize(2 * sz - 1);
    for(int k = 0; k < array.size(); k++) {
      seg[k + sz - 1].emplace_back(array[k]);
    }
    for(int k = sz - 2; k >= 0; k--) {
      seg[k].resize(seg[2 * k + 1].size() + seg[2 * k + 2].size());
      LL[k].resize(seg[k].size() + 1);
      RR[k].resize(seg[k].size() + 1);
      merge(begin(seg[2 * k + 1]), end(seg[2 * k + 1]), begin(seg[2 * k + 2]), end(seg[2 * k + 2]), begin(seg[k]));
      int tail1 = 0, tail2 = 0;
      for(int i = 0; i < seg[k].size(); i++) {
        while(tail1 < seg[2 * k + 1].size() && seg[2 * k + 1][tail1] < seg[k][i]) ++tail1;
        while(tail2 < seg[2 * k + 2].size() && seg[2 * k + 2][tail2] < seg[k][i]) ++tail2;
        LL[k][i] = tail1, RR[k][i] = tail2;
      }
      LL[k][seg[k].size()] = (int) seg[2 * k + 1].size();
      RR[k][seg[k].size()] = (int) seg[2 * k + 2].size();
    }
  }

  int query(int a, int b, int lower, int upper, int k, int l, int r) {
    if(a >= r || b <= l) {
      return (0);
    } else if(a <= l && r <= b) {
      return (upper - lower);
    } else {
      return (query(a, b, LL[k][lower], LL[k][upper], 2 * k + 1, l, (l + r) >> 1) + query(a, b, RR[k][lower], RR[k][upper], 2 * k + 2, (l + r) >> 1, r));
    }
  }

  int query(int a, int b, int l, int r) {
    l = lower_bound(begin(seg[0]), end(seg[0]), l) - begin(seg[0]);
    r = lower_bound(begin(seg[0]), end(seg[0]), r) - begin(seg[0]);
    return (query(a, b, l, r, 0, 0, sz));
  }
};


##################################################
############# dual-segment-tree.cpp ##############
##################################################

template< typename OperatorMonoid >
struct DualSegmentTree {
  using H = function< OperatorMonoid(OperatorMonoid, OperatorMonoid) >;

  int sz, height;
  vector< OperatorMonoid > lazy;
  const H h;
  const OperatorMonoid OM0;


  DualSegmentTree(int n, const H h, const OperatorMonoid OM0)
      : h(h), OM0(OM0) {
    sz = 1;
    height = 0;
    while(sz < n) sz <<= 1, height++;
    lazy.assign(2 * sz, OM0);
  }

  inline void propagate(int k) {
    if(lazy[k] != OM0) {
      lazy[2 * k + 0] = h(lazy[2 * k + 0], lazy[k]);
      lazy[2 * k + 1] = h(lazy[2 * k + 1], lazy[k]);
      lazy[k] = OM0;
    }
  }

  inline void thrust(int k) {
    for(int i = height; i > 0; i--) propagate(k >> i);
  }

  void update(int a, int b, const OperatorMonoid &x) {
    thrust(a += sz);
    thrust(b += sz - 1);
    for(int l = a, r = b + 1; l < r; l >>= 1, r >>= 1) {
      if(l & 1) lazy[l] = h(lazy[l], x), ++l;
      if(r & 1) --r, lazy[r] = h(lazy[r], x);
    }
  }

  OperatorMonoid operator[](int k) {
    thrust(k += sz);
    return lazy[k];
  }
};


##################################################
############ weighted-union-find.cpp #############
##################################################

template< typename T >
struct WeightedUnionFind {
  vector< int > data;
  vector< T > ws;

  WeightedUnionFind() {}

  WeightedUnionFind(int sz) : data(sz, -1), ws(sz) {}

  int find(int k) {
    if(data[k] < 0) return k;
    auto par = find(data[k]);
    ws[k] += ws[data[k]];
    return data[k] = par;
  }

  T weight(int t) {
    find(t);
    return ws[t];
  }

  bool unite(int x, int y, T w) {
    w += weight(x);
    w -= weight(y);
    x = find(x), y = find(y);
    if(x == y) return false;
    if(data[x] > data[y]) {
      swap(x, y);
      w *= -1;
    }
    data[x] += data[y];
    data[y] = x;
    ws[y] = w;
    return true;
  }

  T diff(int x, int y) {
    return weight(y) - weight(x);
  }
};


##################################################
################ sparse-table.cpp ################
##################################################

template< typename T >
struct SparseTable {
  vector< vector< T > > st;
  vector< int > lookup;

  SparseTable(const vector< T > &v) {
    int b = 0;
    while((1 << b) <= v.size()) ++b;
    st.assign(b, vector< T >(1 << b));
    for(int i = 0; i < v.size(); i++) {
      st[0][i] = v[i];
    }
    for(int i = 1; i < b; i++) {
      for(int j = 0; j + (1 << i) <= (1 << b); j++) {
        st[i][j] = min(st[i - 1][j], st[i - 1][j + (1 << (i - 1))]);
      }
    }
    lookup.resize(v.size() + 1);
    for(int i = 2; i < lookup.size(); i++) {
      lookup[i] = lookup[i >> 1] + 1;
    }
  }

  inline T rmq(int l, int r) {
    int b = lookup[r - l];
    return min(st[b][l], st[b][r - (1 << b)]);
  }
};


##################################################
######### persistent-red-black-tree.cpp ##########
##################################################

template< class D, class L, D (*f)(D, D), D (*g)(D, L), L (*h)(L, L), L (*p)(L, int) >
struct PersistentRedBlackTree : RedBlackTree< D, L, f, g, h, p > {
  using RBT = RedBlackTree< D, L, f, g, h, p >;
  using Node = typename RBT::Node;

  PersistentRedBlackTree(int sz, const D &M1, const L &OM0) :
      RBT(sz, M1, OM0) {}

  Node *clone(Node *t) override { return &(*RBT::pool.alloc() = *t); }

  Node *rebuild(Node *r) {
    auto ret = RBT::dump(r);
    RBT::pool.clear();
    return RBT::build(ret);
  }
};


##################################################
############## persistent-array.cpp ##############
##################################################

template< typename T, int LOG >
struct PersistentArray {
  struct Node {
    T data;
    Node *child[1 << LOG] = {};

    Node() {}

    Node(const T &data) : data(data) {}
  };

  Node *root;

  PersistentArray() : root(nullptr) {}

  T get(Node *t, int k) {
    if(k == 0) return t->data;
    return get(t->child[k & ((1 << LOG) - 1)], k >> LOG);
  }

  T get(const int &k) {
    return get(root, k);
  }

  pair< Node *, T * > mutable_get(Node *t, int k) {
    t = t ? new Node(*t) : new Node();
    if(k == 0) return {t, &t->data};
    auto p = mutable_get(t->child[k & ((1 << LOG) - 1)], k >> LOG);
    t->child[k & ((1 << LOG) - 1)] = p.first;
    return {t, p.second};
  }

  T *mutable_get(const int &k) {
    auto ret = mutable_get(root, k);
    root = ret.first;
    return ret.second;
  }

  Node *build(Node *t, const T &data, int k) {
    if(!t) t = new Node();
    if(k == 0) {
      t->data = data;
      return t;
    }
    auto p = build(t->child[k & ((1 << LOG) - 1)], data, k >> LOG);
    t->child[k & ((1 << LOG) - 1)] = p;
    return t;
  }

  void build(const vector< T > &v) {
    root = nullptr;
    for(int i = 0; i < v.size(); i++) {
      root = build(root, v[i], i);
    }
  }
};



##################################################
##### randomized-binary-search-tree-set.cpp ######
##################################################

template< class T >
struct OrderedMultiSet : RandomizedBinarySearchTree< T >
{
  using RBST = RandomizedBinarySearchTree< T >;
  using Node = typename RBST::Node;

  OrderedMultiSet(int sz) : RBST(sz, [&](T x, T y) { return x; }, T()) {}

  T kth_element(Node *t, int k)
  {
    if(k < RBST::count(t->l)) return kth_element(t->l, k);
    if(k == RBST::count(t->l)) return t->key;
    return kth_element(t->r, k - RBST::count(t->l) - 1);
  }

  virtual void insert_key(Node *&t, const T &x)
  {
    RBST::insert(t, lower_bound(t, x), x);
  }

  void erase_key(Node *&t, const T &x)
  {
    if(!count(t, x)) return;
    RBST::erase(t, lower_bound(t, x));
  }

  int count(Node *t, const T &x)
  {
    return upper_bound(t, x) - lower_bound(t, x);
  }

  int lower_bound(Node *t, const T &x)
  {
    if(!t) return 0;
    if(x <= t->key) return lower_bound(t->l, x);
    return lower_bound(t->r, x) + RBST::count(t->l) + 1;
  }

  int upper_bound(Node *t, const T &x)
  {
    if(!t) return 0;
    if(x < t->key) return upper_bound(t->l, x);
    return upper_bound(t->r, x) + RBST::count(t->l) + 1;
  }
};
template< class T >
struct OrderedSet : OrderedMultiSet< T >
{
  using SET = OrderedMultiSet< T >;
  using RBST = typename SET::RBST;
  using Node = typename RBST::Node;

  OrderedSet(int sz) : OrderedMultiSet< T >(sz) {}

  void insert_key(Node *&t, const T &x) override
  {
    if(SET::count(t, x)) return;
    RBST::insert(t, SET::lower_bound(t, x), x);
  }
};


##################################################
############# segment-tree-beats.cpp #############
##################################################

template< typename Monoid, typename OperatorMonoid = Monoid >
struct SegmentTreeBeats {
  using F = function< Monoid(Monoid, Monoid) >;
  using G = function< Monoid(Monoid, OperatorMonoid) >;
  using H = function< OperatorMonoid(OperatorMonoid, OperatorMonoid) >;

  int sz, height;
  vector< Monoid > data;
  vector< OperatorMonoid > lazy;
  const F f;
  const G g;
  const H h;
  const Monoid M1;
  const OperatorMonoid OM0;


  SegmentTreeBeats(int n, const F f, const G g, const H h,
                   const Monoid &M1, const OperatorMonoid OM0)
      : f(f), g(g), h(h), M1(M1), OM0(OM0) {
    sz = 1;
    height = 0;
    while(sz < n) sz <<= 1, height++;
    data.assign(2 * sz, M1);
    lazy.assign(2 * sz, OM0);
  }

  void set(int k, const Monoid &x) {
    data[k + sz] = x;
  }

  void build() {
    for(int k = sz - 1; k > 0; k--) {
      data[k] = f(data[2 * k + 0], data[2 * k + 1]);
    }
  }

  inline void propagate(int k) {
    if(lazy[k] != OM0) {
      lazy[2 * k + 0] = h(lazy[2 * k + 0], lazy[k]);
      lazy[2 * k + 1] = h(lazy[2 * k + 1], lazy[k]);
      data[k] = reflect(k);
      lazy[k] = OM0;
    }
  }

  inline Monoid reflect(int k) {
    return lazy[k] == OM0 ? data[k] : g(data[k], lazy[k]);
  }

  inline void recalc(int k) {
    while(k >>= 1) data[k] = f(reflect(2 * k + 0), reflect(2 * k + 1));
  }

  inline void thrust(int k) {
    for(int i = height; i > 0; i--) propagate(k >> i);
  }

  void update(int a, int b, const OperatorMonoid &x) {
    thrust(a += sz);
    thrust(b += sz - 1);
    for(int l = a, r = b + 1; l < r; l >>= 1, r >>= 1) {
      if(l & 1) lazy[l] = h(lazy[l], x), ++l;
      if(r & 1) --r, lazy[r] = h(lazy[r], x);
    }
    recalc(a);
    recalc(b);
  }

  Monoid query(int a, int b) {
    thrust(a += sz);
    thrust(b += sz - 1);
    Monoid L = M1, R = M1;
    for(int l = a, r = b + 1; l < r; l >>= 1, r >>= 1) {
      if(l & 1) L = f(L, reflect(l++));
      if(r & 1) R = f(reflect(--r), R);
    }
    return f(L, R);
  }

  Monoid operator[](const int &k) {
    return query(k, k + 1);
  }

  template< typename Uku, typename Check, typename Func, typename X >
  void update_beats_subtree(int k, const X &x, const Uku &uku, const Check &check, const Func &func) {
    if(k >= sz) {
      auto v = reflect(k);
      if(uku(v, x)) return;
      if(check(v)) lazy[k] = func(v, x);
      return;
    }
    propagate(k);
    if(uku(data[k], x)) return;
    if(check(data[k])) {
      lazy[k] = func(data[k], x);
      return;
    }
    update_beats_subtree(k * 2 + 0, x, uku, check, func);
    update_beats_subtree(k * 2 + 1, x, uku, check, func);
    data[k] = f(reflect(2 * k + 0), reflect(2 * k + 1));
  }

  template< typename Uku, typename Check, typename Func, typename X >
  void update_beats(int a, int b, const X &x, const Uku &uku, const Check &check, const Func &func) {
    thrust(a += sz);
    thrust(b += sz - 1);
    for(int l = a, r = b + 1; l < r; l >>= 1, r >>= 1) {
      if(l & 1) update_beats_subtree(l++, x, uku, check, func);
      if(r & 1) update_beats_subtree(--r, x, uku, check, func);
    }
    recalc(a);
    recalc(b);
  }
};


##################################################
#################### trie.cpp ####################
##################################################

template< int char_size >
struct TrieNode {
  int nxt[char_size];

  int exist;
  vector< int > accept;

  TrieNode() : exist(0) {
    memset(nxt, -1, sizeof(nxt));
  }
};

template< int char_size, int margin >
struct Trie {
  using Node = TrieNode< char_size >;

  vector< Node > nodes;
  int root;

  Trie() : root(0) {
    nodes.push_back(Node());
  }

  void update_direct(int node, int id) {
    nodes[node].accept.push_back(id);
  }

  void update_child(int node, int child, int id) {
    ++nodes[node].exist;
  }

  void add(const string &str, int str_index, int node_index, int id) {
    if(str_index == str.size()) {
      update_direct(node_index, id);
    } else {
      const int c = str[str_index] - margin;
      if(nodes[node_index].nxt[c] == -1) {
        nodes[node_index].nxt[c] = (int) nodes.size();
        nodes.push_back(Node());
      }
      add(str, str_index + 1, nodes[node_index].nxt[c], id);
      update_child(node_index, nodes[node_index].nxt[c], id);
    }
  }

  void add(const string &str, int id) {
    add(str, 0, 0, id);
  }

  void add(const string &str) {
    add(str, nodes[0].exist);
  }

  void query(const string &str, const function< void(int) > &f, int str_index, int node_index) {
    for(auto &idx : nodes[node_index].accept) f(idx);
    if(str_index == str.size()) {
      return;
    } else {
      const int c = str[str_index] - margin;
      if(nodes[node_index].nxt[c] == -1) return;
      query(str, f, str_index + 1, nodes[node_index].nxt[c]);
    }
  }

  void query(const string &str, const function< void(int) > &f) {
    query(str, f, 0, 0);
  }

  int count() const {
    return (nodes[0].exist);
  }

  int size() const {
    return ((int) nodes.size());
  }
};


##################################################
############## union-find-undo.cpp ###############
##################################################

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


##################################################
############## segment-tree-2d.cpp ###############
##################################################

template< typename structure_t, typename get_t, typename update_t >
struct SegmentTree2DCompressed {

  using merge_f = function< get_t(get_t, get_t) >;
  using range_get_f = function< get_t(structure_t &, int, int) >;
  using update_f = function< void(structure_t &, int, update_t) >;

  int sz;
  vector< structure_t > seg;
  const merge_f f;
  const range_get_f g;
  const update_f h;
  const get_t identity;
  vector< vector< int > > LL, RR;
  vector< vector< int > > beet;

  SegmentTree2DCompressed(int n, const merge_f &f, const range_get_f &g, const update_f &h, const get_t &identity)
      : f(f), g(g), h(h), identity(identity) {
    sz = 1;
    while(sz < n) sz <<= 1;
    beet.resize(2 * sz);
    LL.resize(2 * sz);
    RR.resize(2 * sz);
  }

  void update(int a, int x, update_t z, int k, int l, int r) {
    if(r <= a || a + 1 <= l) return;
    if(a <= l && r <= a + 1) return h(seg[k], x, z);
    update(a, LL[k][x], z, 2 * k + 0, l, (l + r) >> 1);
    update(a, RR[k][x], z, 2 * k + 1, (l + r) >> 1, r);
    return h(seg[k], x, z);
  }

  void update(int x, int y, update_t z) {
    y = lower_bound(begin(beet[1]), end(beet[1]), y) - begin(beet[1]);
    return update(x, y, z, 1, 0, sz);
  }

  get_t query(int a, int b, int x, int y, int k, int l, int r) {
    if(a >= r || b <= l) return identity;
    if(a <= l && r <= b) return g(seg[k], x, y);
    return f(query(a, b, LL[k][x], LL[k][y], 2 * k + 0, l, (l + r) >> 1),
             query(a, b, RR[k][x], RR[k][y], 2 * k + 1, (l + r) >> 1, r));
  }

  get_t query(int a, int b, int x, int y) {
    x = lower_bound(begin(beet[1]), end(beet[1]), x) - begin(beet[1]);
    y = lower_bound(begin(beet[1]), end(beet[1]), y) - begin(beet[1]);
    return query(a, b, x, y, 1, 0, sz);
  }

  void build() {
    for(int k = (int) beet.size() - 1; k >= sz; k--) {
      sort(begin(beet[k]), end(beet[k]));
      beet[k].erase(unique(begin(beet[k]), end(beet[k])), end(beet[k]));
    }
    for(int k = sz - 1; k > 0; k--) {
      beet[k].resize(beet[2 * k + 0].size() + beet[2 * k + 1].size());
      merge(begin(beet[2 * k + 0]), end(beet[2 * k + 0]), begin(beet[2 * k + 1]), end(beet[2 * k + 1]), begin(beet[k]));
      beet[k].erase(unique(begin(beet[k]), end(beet[k])), end(beet[k]));
      LL[k].resize(beet[k].size() + 1);
      RR[k].resize(beet[k].size() + 1);
      int tail1 = 0, tail2 = 0;
      for(int i = 0; i < beet[k].size(); i++) {
        while(tail1 < beet[2 * k + 0].size() && beet[2 * k + 0][tail1] < beet[k][i]) ++tail1;
        while(tail2 < beet[2 * k + 1].size() && beet[2 * k + 1][tail2] < beet[k][i]) ++tail2;
        LL[k][i] = tail1, RR[k][i] = tail2;
      }
      LL[k][beet[k].size()] = (int) beet[2 * k + 0].size();
      RR[k][beet[k].size()] = (int) beet[2 * k + 1].size();
    }
    for(int k = 0; k < beet.size(); k++) {
      seg.emplace_back(structure_t(beet[k].size()));
    }
  }

  void preupdate(int x, int y) {
    beet[x + sz].push_back(y);
  }
};


##################################################
############## union-rectangle.cpp ###############
##################################################

template< typename T >
struct UnionRectangle {
  map< T, T > data;
  int64 sum;

  UnionRectangle() : sum(0) {
    const T INF = numeric_limits< T >::max();
    data[0] = INF;
    data[INF] = 0;
  }
  void add_point(T x, T y) {
    auto p = data.lower_bound(x);
    if(p->second >= y) return;
    const T nxtY = p->second;
    --p;
    while(p->second <= y) {
      auto it = *p;
      p = --data.erase(p);
      sum -= (it.first - p->first) * (it.second - nxtY);
    }
    sum += (x - p->first) * (y - nxtY);
    data[x] = y;
  }

  int64 get() {
    return sum;
  }
};


##################################################
########## persistent-segment-tree.cpp ###########
##################################################

template< typename Monoid >
struct PersistentSegmentTree {
  using F = function< Monoid(Monoid, Monoid) >;
 
  struct Node {
    Monoid data;
    Node *l, *r;
 
    Node(const Monoid &data) : data(data), l(nullptr), r(nullptr) {}
  };
 
 
  int sz;
  const F f;
  const Monoid M1;
 
  PersistentSegmentTree(const F f, const Monoid &M1) : f(f), M1(M1) {}
 
  Node *build(vector< Monoid > &v) {
    sz = (int) v.size();
    return build(0, (int) v.size(), v);
  }
 
  Node *merge(Node *l, Node *r) {
    auto t = new Node(f(l->data, r->data));
    t->l = l;
    t->r = r;
    return t;
  }
 
  Node *build(int l, int r, vector< Monoid > &v) {
    if(l + 1 >= r) return new Node(v[l]);
    return merge(build(l, (l + r) >> 1, v), build((l + r) >> 1, r, v));
  }
 
  Node *update(int a, const Monoid &x, Node *k, int l, int r) {
    if(r <= a || a + 1 <= l) {
      return k;
    } else if(a <= l && r <= a + 1) {
      return new Node(x);
    } else {
      return merge(update(a, x, k->l, l, (l + r) >> 1), update(a, x, k->r, (l + r) >> 1, r));
    }
  }
 
  Node *update(Node *t, int k, const Monoid &x) {
    return update(k, x, t, 0, sz);
  }
 
  Monoid query(int a, int b, Node *k, int l, int r) {
    if(r <= a || b <= l) {
      return M1;
    } else if(a <= l && r <= b) {
      return k->data;
    } else {
      return f(query(a, b, k->l, l, (l + r) >> 1),
               query(a, b, k->r, (l + r) >> 1, r));
    }
  }
 
  Monoid query(Node *t, int a, int b) {
    return query(a, b, t, 0, sz);
  }
};


##################################################
############### red-black-tree.cpp ###############
##################################################

template< class T >
struct ArrayPool {
  vector< T > pool;
  vector< T * > stock;
  int ptr;

  ArrayPool(int sz) : pool(sz), stock(sz) {}

  inline T *alloc() { return stock[--ptr]; }

  inline void free(T *t) { stock[ptr++] = t; }

  void clear() {
    ptr = (int) pool.size();
    for(int i = 0; i < pool.size(); i++) stock[i] = &pool[i];
  }
};

template< class D, class L, D (*f)(D, D), D (*g)(D, L), L (*h)(L, L), L (*p)(L, int) >
struct RedBlackTree {
  enum COLOR {
    BLACK, RED
  };

  struct Node {
    Node *l, *r;
    COLOR color;
    int level, cnt;
    D key, sum;
    L lazy;

    Node() {}

    Node(const D &k, const L &laz) :
        key(k), sum(k), l(nullptr), r(nullptr), color(BLACK), level(0), cnt(1), lazy(laz) {}

    Node(Node *l, Node *r, const D &k, const L &laz) :
        key(k), color(RED), l(l), r(r), lazy(laz) {}
  };

  ArrayPool< Node > pool;


  const D M1;
  const L OM0;

  RedBlackTree(int sz, const D &M1, const L &OM0) :
      pool(sz), M1(M1), OM0(OM0) { pool.clear(); }


  inline Node *alloc(const D &key) {
    return &(*pool.alloc() = Node(key, OM0));
  }

  inline Node *alloc(Node *l, Node *r) {
    auto t = &(*pool.alloc() = Node(l, r, M1, OM0));
    return update(t);
  }

  virtual Node *clone(Node *t) { return t; }

  inline int count(const Node *t) { return t ? t->cnt : 0; }

  inline D sum(const Node *t) { return t ? t->sum : M1; }

  Node *update(Node *t) {
    t->cnt = count(t->l) + count(t->r) + (!t->l || !t->r);
    t->level = t->l ? t->l->level + (t->l->color == BLACK) : 0;
    t->sum = f(f(sum(t->l), t->key), sum(t->r));
    return t;
  }

  Node *propagate(Node *t) {
    t = clone(t);
    if(t->lazy != OM0) {
      if(!t->l) {
        t->key = g(t->key, p(t->lazy, 1));
      } else {
        if(t->l) {
          t->l = clone(t->l);
          t->l->lazy = h(t->l->lazy, t->lazy);
          t->l->sum = g(t->l->sum, p(t->lazy, count(t->l)));
        }
        if(t->r) {
          t->r = clone(t->r);
          t->r->lazy = h(t->r->lazy, t->lazy);
          t->r->sum = g(t->r->sum, p(t->lazy, count(t->r)));
        }
      }
      t->lazy = OM0;
    }
    return update(t);
  }

  Node *rotate(Node *t, bool b) {
    t = propagate(t);
    Node *s;
    if(b) {
      s = propagate(t->l);
      t->l = s->r;
      s->r = t;
    } else {
      s = propagate(t->r);
      t->r = s->l;
      s->l = t;
    }
    update(t);
    return update(s);
  }

  Node *submerge(Node *l, Node *r) {
    if(l->level < r->level) {
      r = propagate(r);
      Node *c = (r->l = submerge(l, r->l));
      if(r->color == BLACK && c->color == RED && c->l && c->l->color == RED) {
        r->color = RED;
        c->color = BLACK;
        if(r->r->color == BLACK) return rotate(r, true);
        r->r->color = BLACK;
      }
      return update(r);
    }
    if(l->level > r->level) {
      l = propagate(l);
      Node *c = (l->r = submerge(l->r, r));
      if(l->color == BLACK && c->color == RED && c->r && c->r->color == RED) {
        l->color = RED;
        c->color = BLACK;
        if(l->l->color == BLACK) return rotate(l, false);
        l->l->color = BLACK;
      }
      return update(l);
    }
    return alloc(l, r);
  }

  Node *merge(Node *l, Node *r) {
    if(!l || !r) return l ? l : r;
    Node *c = submerge(l, r);
    c->color = BLACK;
    return c;
  }

  pair< Node *, Node * > split(Node *t, int k) {
    if(!t) return {nullptr, nullptr};
    t = propagate(t);
    if(k == 0) return {nullptr, t};
    if(k >= count(t)) return {t, nullptr};
    Node *l = t->l, *r = t->r;
    pool.free(t);
    if(k < count(l)) {
      auto pp = split(l, k);
      return {pp.first, merge(pp.second, r)};
    }
    if(k > count(l)) {
      auto pp = split(r, k - count(l));
      return {merge(l, pp.first), pp.second};
    }
    return {l, r};
  }

  Node *build(int l, int r, const vector< D > &v) {
    if(l + 1 >= r) return alloc(v[l]);
    return merge(build(l, (l + r) >> 1, v), build((l + r) >> 1, r, v));
  }

  Node *build(const vector< D > &v) {
    //pool.clear();
    return build(0, (int) v.size(), v);
  }

  void dump(Node *r, typename vector< D >::iterator &it, L lazy) {
    if(r->lazy != OM0) lazy = h(lazy, r->lazy);
    if(!r->l || !r->r) {
      *it++ = g(r->key, lazy);
      return;
    }
    dump(r->l, it, lazy);
    dump(r->r, it, lazy);
  }

  vector< D > dump(Node *r) {
    vector< D > v((size_t) count(r));
    auto it = begin(v);
    dump(r, it, OM0);
    return v;
  }

  string to_string(Node *r) {
    auto s = dump(r);
    string ret;
    for(int i = 0; i < s.size(); i++) {
      ret += std::to_string(s[i]);
      ret += ", ";
    }
    return (ret);
  }

  void insert(Node *&t, int k, const D &v) {
    auto x = split(t, k);
    t = merge(merge(x.first, alloc(v)), x.second);
  }

  D erase(Node *&t, int k) {
    auto x = split(t, k);
    auto y = split(x.second, 1);
    auto v = y.first->key;
    pool.free(y.first);
    t = merge(x.first, y.second);
    return v;
  }

  D query(Node *&t, int a, int b) {
    auto x = split(t, a);
    auto y = split(x.second, b - a);
    auto ret = sum(y.first);
    t = merge(x.first, merge(y.first, y.second));
    return ret;
  }

  void set_propagate(Node *&t, int a, int b, const L &pp) {
    auto x = split(t, a);
    auto y = split(x.second, b - a);
    y.first->lazy = h(y.first->lazy, pp);
    t = merge(x.first, merge(propagate(y.first), y.second));
  }

  void set_element(Node *&t, int k, const D &x) {
    if(!t->l) {
      t->key = t->sum = x;
      return;
    }
    t = propagate(t);
    if(k < count(t->l)) set_element(t->l, k, x);
    else set_element(t->r, k - count(t->l), x);
    t = update(t);
  }

  int size(Node *t) {
    return count(t);
  }

  bool empty(Node *t) {
    return !t;
  }

  Node *makeset() {
    return (nullptr);
  }
};


##################################################
####### randomized-binary-search-tree.cpp ########
##################################################

template< class Monoid, class OperatorMonoid = Monoid >
struct RandomizedBinarySearchTree {
  using F = function< Monoid(Monoid, Monoid) >;
  using G = function< Monoid(Monoid, OperatorMonoid) >;
  using H = function< OperatorMonoid(OperatorMonoid, OperatorMonoid) >;
  using P = function< OperatorMonoid(OperatorMonoid, int) >;

  inline int xor128() {
    static int x = 123456789;
    static int y = 362436069;
    static int z = 521288629;
    static int w = 88675123;
    int t;

    t = x ^ (x << 11);
    x = y;
    y = z;
    z = w;
    return w = (w ^ (w >> 19)) ^ (t ^ (t >> 8));
  }

  struct Node {
    Node *l, *r;
    int cnt;
    Monoid key, sum;
    OperatorMonoid lazy;

    Node() = default;

    Node(const Monoid &k, const OperatorMonoid &p) : cnt(1), key(k), sum(k), lazy(p), l(nullptr), r(nullptr) {}
  };

  vector< Node > pool;
  int ptr;

  const Monoid M1;
  const OperatorMonoid OM0;
  const F f;
  const G g;
  const H h;
  const P p;

  RandomizedBinarySearchTree(int sz, const F &f, const Monoid &M1) :
      pool(sz), ptr(0), f(f), g(G()), h(H()), p(P()), M1(M1), OM0(OperatorMonoid()) {}

  RandomizedBinarySearchTree(int sz, const F &f, const G &g, const H &h, const P &p,
                             const Monoid &M1, const OperatorMonoid &OM0) :
      pool(sz), ptr(0), f(f), g(g), h(h), p(p), M1(M1), OM0(OM0) {}

  inline Node *alloc(const Monoid &key) { return &(pool[ptr++] = Node(key, OM0)); }

  virtual Node *clone(Node *t) { return t; }

  inline int count(const Node *t) { return t ? t->cnt : 0; }

  inline Monoid sum(const Node *t) { return t ? t->sum : M1; }

  inline Node *update(Node *t) {
    t->cnt = count(t->l) + count(t->r) + 1;
    t->sum = f(f(sum(t->l), t->key), sum(t->r));
    return t;
  }

  Node *propagate(Node *t) {
    t = clone(t);
    if(t->lazy != OM0) {
      t->key = g(t->key, p(t->lazy, 1));
      if(t->l) {
        t->l = clone(t->l);
        t->l->lazy = h(t->l->lazy, t->lazy);
        t->l->sum = g(t->l->sum, p(t->lazy, count(t->l)));
      }
      if(t->r) {
        t->r = clone(t->r);
        t->r->lazy = h(t->r->lazy, t->lazy);
        t->r->sum = g(t->r->sum, p(t->lazy, count(t->r)));
      }
      t->lazy = OM0;
    }
    return update(t);
  }

  Node *merge(Node *l, Node *r) {
    if(!l || !r) return l ? l : r;
    if(xor128() % (l->cnt + r->cnt) < l->cnt) {
      l = propagate(l);
      l->r = merge(l->r, r);
      return update(l);
    } else {
      r = propagate(r);
      r->l = merge(l, r->l);
      return update(r);
    }
  }

  pair< Node *, Node * > split(Node *t, int k) {
    if(!t) return {t, t};
    t = propagate(t);
    if(k <= count(t->l)) {
      auto s = split(t->l, k);
      t->l = s.second;
      return {s.first, update(t)};
    } else {
      auto s = split(t->r, k - count(t->l) - 1);
      t->r = s.first;
      return {update(t), s.second};
    }
  }

  Node *build(int l, int r, const vector< Monoid > &v) {
    if(l + 1 >= r) return alloc(v[l]);
    return merge(build(l, (l + r) >> 1, v), build((l + r) >> 1, r, v));
  }

  Node *build(const vector< Monoid > &v) {
    ptr = 0;
    return build(0, (int) v.size(), v);
  }

  void dump(Node *r, typename vector< Monoid >::iterator &it) {
    if(!r) return;
    r = propagate(r);
    dump(r->l, it);
    *it = r->key;
    dump(r->r, ++it);
  }

  vector< Monoid > dump(Node *r) {
    vector< Monoid > v((size_t) count(r));
    auto it = begin(v);
    dump(r, it);
    return v;
  }

  string to_string(Node *r) {
    auto s = dump(r);
    string ret;
    for(int i = 0; i < s.size(); i++) ret += ", ";
    return (ret);
  }

  void insert(Node *&t, int k, const Monoid &v) {
    auto x = split(t, k);
    t = merge(merge(x.first, alloc(v)), x.second);
  }

  void erase(Node *&t, int k) {
    auto x = split(t, k);
    t = merge(x.first, split(x.second, 1).second);
  }

  Monoid query(Node *&t, int a, int b) {
    auto x = split(t, a);
    auto y = split(x.second, b - a);
    auto ret = sum(y.first);
    t = merge(x.first, merge(y.first, y.second));
    return ret;
  }

  void set_propagate(Node *&t, int a, int b, const OperatorMonoid &p) {
    auto x = split(t, a);
    auto y = split(x.second, b - a);
    y.first->lazy = h(y.first->lazy, p);
    t = merge(x.first, merge(propagate(y.first), y.second));
  }

  void set_element(Node *&t, int k, const Monoid &x) {
    t = propagate(t);
    if(k < count(t->l)) set_element(t->l, k, x);
    else if(k == count(t->l)) t->key = t->sum = x;
    else set_element(t->r, k - count(t->l) - 1, x);
    t = update(t);
  }


  int size(Node *t) {
    return count(t);
  }

  bool empty(Node *t) {
    return !t;
  }

  Node *makeset() {
    return nullptr;
  }
};


##################################################
############## bipartite-graph.cpp ###############
##################################################

struct BipartiteGraph : UnionFind
{
  vector< int > color;

  BipartiteGraph(int v) : color(v + v, -1), UnionFind(v + v) {}

  bool bipartite_graph_coloring()
  {
    for(int i = 0; i < color.size() / 2; i++) {
      int a = find(i);
      int b = find(i + (int) color.size() / 2);
      if(a == b) return (false);
      if(color[a] < 0) color[a] = 0, color[b] = 1;
    }
    return (true);
  }

  bool operator[](int k)
  {
    return (bool(color[find(k)]));
  }
};


##################################################
################ li-chao-tree.cpp ################
##################################################

template< typename T >
struct LiChaoTree {
  struct Line {
    T a, b;

    Line(T a, T b) : a(a), b(b) {}

    inline T get(T x) const { return a * x + b; }

    inline bool over(const Line &b, const T &x) const {
      return get(x) < b.get(x);
    }
  };

  vector< T > xs;
  vector< Line > seg;
  int sz;

  LiChaoTree(const vector< T > &x, T INF) : xs(x) {
    sz = 1;
    while(sz < xs.size()) sz <<= 1;
    while(xs.size() < sz) xs.push_back(xs.back() + 1);
    seg.assign(2 * sz - 1, Line(0, INF));
  }

  void update(Line &x, int k, int l, int r) {
    int mid = (l + r) >> 1;
    auto latte = x.over(seg[k], xs[l]), malta = x.over(seg[k], xs[mid]);
    if(malta) swap(seg[k], x);
    if(l + 1 >= r) return;
    else if(latte != malta) update(x, 2 * k + 1, l, mid);
    else update(x, 2 * k + 2, mid, r);
  }

  void update(T a, T b) { // ax+b
    Line l(a, b);
    update(l, 0, 0, sz);
  }

  T query(int k) { // xs[k]
    const T x = xs[k];
    k += sz - 1;
    T ret = seg[k].get(x);
    while(k > 0) {
      k = (k - 1) >> 1;
      ret = min(ret, seg[k].get(x));
    }
    return ret;
  }
};


##################################################
########### persistent-binary-trie.cpp ###########
##################################################

template< typename T >
struct BinaryTrieNode {
  using Node = BinaryTrieNode< T >;
 
  BinaryTrieNode< T > *nxt[2];
  int max_index;
 
  BinaryTrieNode() : max_index(-1) {
    nxt[0] = nxt[1] = nullptr;
  }
 
  void update_direct(int id) {
    max_index = max(max_index, id);
  }
 
  void update_child(Node *child, int id) {
    max_index = max(max_index, id);
  }
 
  Node *add(const T &bit, int bit_index, int id, bool need = true) {
    Node *node = need ? new Node(*this) : this;
    if(bit_index == -1) {
      node->update_direct(id);
    } else {
      const int c = (bit >> bit_index) & 1;
      if(node->nxt[c] == nullptr) node->nxt[c] = new Node(), need = false;
      node->nxt[c] = node->nxt[c]->add(bit, bit_index - 1, id, need);
      node->update_child(node->nxt[c], id);
    }
    return node;
  }
 
  inline T min_query(T bit, int bit_index, int bit2, int l) {
    if(bit_index == -1) return bit;
    int c = (bit2 >> bit_index) & 1;
    if(nxt[c] != nullptr && l <= nxt[c]->max_index) {
      return nxt[c]->min_query(bit, bit_index - 1, bit2, l);
    } else {
      return nxt[1 ^ c]->min_query(bit | (1LL << bit_index), bit_index - 1, bit2, l);
    }
  }
};
 
template< typename T, int MAX_LOG >
struct PersistentBinaryTrie {
  using Node = BinaryTrieNode< T >;
  Node *root;
 
  PersistentBinaryTrie(Node *root) : root(root) {}
 
  PersistentBinaryTrie() : root(new Node()) {}
 
  PersistentBinaryTrie add(const T &bit, int id) {
    return PersistentBinaryTrie(root->add(bit, MAX_LOG, id));
  }
 
  T min_query(int bit, int l) {
    return root->min_query(0, MAX_LOG, bit, l);
  }
};


##################################################
################ segment-tree.cpp ################
##################################################

template< typename Monoid >
struct SegmentTree {
  using F = function< Monoid(Monoid, Monoid) >;

  int sz;
  vector< Monoid > seg;

  const F f;
  const Monoid M1;

  SegmentTree(int n, const F f, const Monoid &M1) : f(f), M1(M1) {
    sz = 1;
    while(sz < n) sz <<= 1;
    seg.assign(2 * sz, M1);
  }

  void set(int k, const Monoid &x) {
    seg[k + sz] = x;
  }

  void build() {
    for(int k = sz - 1; k > 0; k--) {
      seg[k] = f(seg[2 * k + 0], seg[2 * k + 1]);
    }
  }

  void update(int k, const Monoid &x) {
    k += sz;
    seg[k] = x;
    while(k >>= 1) {
      seg[k] = f(seg[2 * k + 0], seg[2 * k + 1]);
    }
  }

  Monoid query(int a, int b) {
    Monoid L = M1, R = M1;
    for(a += sz, b += sz; a < b; a >>= 1, b >>= 1) {
      if(a & 1) L = f(L, seg[a++]);
      if(b & 1) R = f(seg[--b], R);
    }
    return f(L, R);
  }

  Monoid operator[](const int &k) const {
    return seg[k + sz];
  }

  template< typename C >
  int find_subtree(int a, const C &check, Monoid &M, bool type) {
    while(a < sz) {
      Monoid nxt = type ? f(seg[2 * a + type], M) : f(M, seg[2 * a + type]);
      if(check(nxt)) a = 2 * a + type;
      else M = nxt, a = 2 * a + 1 - type;
    }
    return a - sz;
  }


  template< typename C >
  int find_first(int a, const C &check) {
    Monoid L = M1;
    if(a <= 0) {
      if(check(f(L, seg[1]))) return find_subtree(1, check, L, false);
      return -1;
    }
    int b = sz;
    for(a += sz, b += sz; a < b; a >>= 1, b >>= 1) {
      if(a & 1) {
        Monoid nxt = f(L, seg[a]);
        if(check(nxt)) return find_subtree(a, check, L, false);
        L = nxt;
        ++a;
      }
    }
    return -1;
  }

  template< typename C >
  int find_last(int b, const C &check) {
    Monoid R = M1;
    if(b >= sz) {
      if(check(f(seg[1], R))) return find_subtree(1, check, R, true);
      return -1;
    }
    int a = sz;
    for(b += sz; a < b; a >>= 1, b >>= 1) {
      if(b & 1) {
        Monoid nxt = f(seg[--b], R);
        if(check(nxt)) return find_subtree(b, check, R, true);
        R = nxt;
      }
    }
    return -1;
  }
};



##################################################
################ binary-trie.cpp #################
##################################################

template< typename T, int MAX_LOG >
struct BinaryTrie {
  BinaryTrie *nxt[2];
  T lazy;
  int exist;
  bool fill;
  vector< int > accept;

  BinaryTrie() : exist(0), lazy(0), nxt{nullptr, nullptr} {}

  void add(const T &bit, int bit_index, int id) {
    propagate(bit_index);
    if(bit_index == -1) {
      ++exist;
      accept.push_back(id);
    } else {
      auto &to = nxt[(bit >> bit_index) & 1];
      if(!to) to = new BinaryTrie();
      to->add(bit, bit_index - 1, id);
      ++exist;
    }
  }

  void add(const T &bit, int id) {
    add(bit, MAX_LOG, id);
  }

  void add(const T &bit) {
    add(bit, exist);
  }

  void del(const T &bit, int bit_index) {
    propagate(bit_index);
    if(bit_index == -1) {
      exist--;
    } else {
      nxt[(bit >> bit_index) & 1]->del(bit, bit_index - 1);
      exist--;
    }
  }

  void del(const T &bit) {
    del(bit, MAX_LOG);
  }


  pair< T, BinaryTrie * > max_element(int bit_index) {
    propagate(bit_index);
    if(bit_index == -1) return {0, this};
    if(nxt[1] && nxt[1]->size()) {
      auto ret = nxt[1]->max_element(bit_index - 1);
      ret.first |= T(1) << bit_index;
      return ret;
    } else {
      return nxt[0]->max_element(bit_index - 1);
    }
  }

  pair< T, BinaryTrie * > min_element(int bit_index) {
    propagate(bit_index);
    if(bit_index == -1) return {0, this};
    if(nxt[0] && nxt[0]->size()) {
      return nxt[0]->min_element(bit_index - 1);
    } else {
      auto ret = nxt[1]->min_element(bit_index - 1);
      ret.first |= T(1) << bit_index;
      return ret;
    }
  }

  T mex_query(int bit_index) { // distinct-values
    propagate(bit_index);
    if(bit_index == -1 || !nxt[0]) return 0;
    if(nxt[0]->size() == (T(1) << bit_index)) {
      T ret = T(1) << bit_index;
      if(nxt[1]) ret |= nxt[1]->mex_query(bit_index - 1);
      return ret;
    } else {
      return nxt[0]->mex_query(bit_index - 1);
    }
  }

  int64_t count_less(const T &bit, int bit_index) {
    propagate(bit_index);
    if(bit_index == -1) return 0;
    int64_t ret = 0;
    if((bit >> bit_index) & 1) {
      if(nxt[0]) ret += nxt[0]->size();
      if(nxt[1]) ret += nxt[1]->count_less(bit, bit_index - 1);
    } else {
      if(nxt[0]) ret += nxt[0]->count_less(bit, bit_index - 1);
    }
    return ret;
  }

  pair< T, BinaryTrie * > get_kth(int64_t k, int bit_index) { // 1-indexed
    propagate(bit_index);
    if(bit_index == -1) return {0, this};
    if((nxt[0] ? nxt[0]->size() : 0) < k) {
      auto ret = nxt[1]->get_kth(k - (nxt[0] ? nxt[0]->size() : 0), bit_index - 1);
      ret.first |= T(1) << bit_index;
      return ret;
    } else {
      return nxt[0]->get_kth(k, bit_index - 1);
    }
  }

  pair< T, BinaryTrie * > max_element() {
    assert(exist);
    return max_element(MAX_LOG);
  }

  pair< T, BinaryTrie * > min_element() {
    assert(exist);
    return min_element(MAX_LOG);
  }

  T mex_query() {
    return mex_query(MAX_LOG);
  }

  int size() const {
    return exist;
  }

  void xorpush(const T &bit) {
    lazy ^= bit;
  }

  int64_t count_less(const T &bit) {
    return count_less(bit, MAX_LOG);
  }

  pair< T, BinaryTrie * > get_kth(int64_t k) {
    assert(0 < k && k <= size());
    return get_kth(k, MAX_LOG);
  }

  void propagate(int bit_index) {
    if((lazy >> bit_index) & 1) swap(nxt[0], nxt[1]);
    if(nxt[0]) nxt[0]->lazy ^= lazy;
    if(nxt[1]) nxt[1]->lazy ^= lazy;
    lazy = 0;
  }
};


##################################################
########### disjoint-sparse-table.cpp ############
##################################################

template< typename Semigroup >
struct DisjointSparseTable {
  using F = function< Semigroup(Semigroup, Semigroup) >;
  const F f;
  vector< vector< Semigroup > > st;

  DisjointSparseTable(const vector< Semigroup > &v, const F &f) : f(f) {
    int b = 0;
    while((1 << b) <= v.size()) ++b;
    st.resize(b, vector< Semigroup >(v.size(), Semigroup()));
    for(int i = 0; i < v.size(); i++) st[0][i] = v[i];
    for(int i = 1; i < b; i++) {
      int shift = 1 << i;
      for(int j = 0; j < v.size(); j += shift << 1) {
        int t = min(j + shift, (int) v.size());
        st[i][t - 1] = v[t - 1];
        for(int k = t - 2; k >= j; k--) st[i][k] = f(v[k], st[i][k + 1]);
        if(v.size() <= t) break;
        st[i][t] = v[t];
        int r = min(t + shift, (int) v.size());
        for(int k = t + 1; k < r; k++) st[i][k] = f(st[i][k - 1], v[k]);
      }
    }
  }

  Semigroup query(int l, int r) {
    if(l >= --r) return st[0][l];
    int p = 31 - __builtin_clz(l ^ r);
    return f(st[p][l], st[p][r]);
  }
};


##################################################
############### wavelet-matrix.cpp ###############
##################################################

struct SuccinctIndexableDictionary {
  size_t length;
  size_t blocks;
  vector< unsigned > bit, sum;

  SuccinctIndexableDictionary() {
  }

  SuccinctIndexableDictionary(size_t _length) {
    length = _length;
    blocks = (length + 31) >> 5;
    bit.assign(blocks, 0U);
    sum.assign(blocks, 0U);
  }

  void set(int k) {
    bit[k >> 5] |= 1U << (k & 31);
  }

  void build() {
    sum[0] = 0U;
    for(int i = 1; i < blocks; i++) {
      sum[i] = sum[i - 1] + __builtin_popcount(bit[i - 1]);
    }
  }

  bool operator[](int k) const {
    return (bool((bit[k >> 5] >> (k & 31)) & 1));
  }

  int rank(int k) {
    return (sum[k >> 5] + __builtin_popcount(bit[k >> 5] & ((1U << (k & 31)) - 1)));
  }

  int rank(bool val, int k) {
    return (val ? rank(k) : k - rank(k));
  }

  int select(bool val, int k) {
    if(k < 0 || rank(val, length) <= k) return (-1);
    int low = 0, high = length;
    while(high - low > 1) {
      int mid = (low + high) >> 1;
      if(rank(val, mid) >= k + 1) high = mid;
      else low = mid;
    }
    return (high - 1);
  }

  int select(bool val, int i, int l) {
    return select(val, i + rank(val, l));
  }
};

template< class T, int MAXLOG >
struct WaveletMatrix {
  size_t length;
  SuccinctIndexableDictionary matrix[MAXLOG];
  int zs[MAXLOG];
  int buff1[MAXLOG], buff2[MAXLOG];

  int freq_dfs(int d, int l, int r, T val, T a, T b) {
    if(l == r) return 0;
    if(d == MAXLOG) return (a <= val && val < b) ? r - l : 0;
    T nv = 1ULL << (MAXLOG - d - 1) | val, nnv = ((1ULL << (MAXLOG - d - 1)) - 1) | nv;
    if(nnv < a || b <= val) return 0;
    if(a <= val && nnv < b) return r - l;
    int lc = matrix[d].rank(1, l), rc = matrix[d].rank(1, r);
    return freq_dfs(d + 1, l - lc, r - rc, val, a, b) +
           freq_dfs(d + 1, lc + zs[d], rc + zs[d], nv, a, b);
  }

  WaveletMatrix(vector< T > data) {
    length = data.size();
    vector< T > l(length), r(length);
    for(int depth = 0; depth < MAXLOG; depth++) {
      matrix[depth] = SuccinctIndexableDictionary(length + 1);
      int left = 0, right = 0;
      for(int i = 0; i < length; i++) {
        bool k = (data[i] >> (MAXLOG - depth - 1)) & 1;
        if(k) r[right++] = data[i], matrix[depth].set(i);
        else l[left++] = data[i];
      }
      zs[depth] = left;
      matrix[depth].build();
      swap(l, data);
      for(int i = 0; i < right; i++) data[left + i] = r[i];
    }
  }

  T access(int k) {
    int ret = 0;
    bool bit;
    for(int depth = 0; depth < MAXLOG; depth++) {
      bit = matrix[depth][k];
      ret = (ret << 1) | bit;
      k = matrix[depth].rank(bit, k) + zs[depth] * bit;
    }
    return (ret);
  }

  int rank(T val, int k) {
    int l = 0, r = k;
    for(int depth = 0; depth < MAXLOG; depth++) {
      buff1[depth] = l, buff2[depth] = r;
      bool bit = (val >> (MAXLOG - depth - 1)) & 1;
      l = matrix[depth].rank(bit, l) + zs[depth] * bit;
      r = matrix[depth].rank(bit, r) + zs[depth] * bit;
    }
    return (r - l);
  }

  int select(T val, int kth) {
    rank(val, length);
    for(int depth = MAXLOG - 1; depth >= 0; depth--) {
      bool bit = (val >> (MAXLOG - depth - 1)) & 1;
      kth = matrix[depth].select(bit, kth, buff1[depth]);
      if(kth >= buff2[depth] || kth < 0) return (-1);
      kth -= buff1[depth];
    }
    return (kth);
  }

  int select(T val, int k, int l) {
    return select(val, k + rank(val, l));
  }

  int quantile(int left, int right, int kth) {
    if(right - left <= kth || kth < 0) return (-1);
    T ret = 0;
    for(int depth = 0; depth < MAXLOG; depth++) {
      int l = matrix[depth].rank(1, left);
      int r = matrix[depth].rank(1, right);
      if(r - l > kth) {
        left = l + zs[depth];
        right = r + zs[depth];
        ret |= 1ULL << (MAXLOG - depth - 1);
      } else {
        kth -= r - l;
        left -= l;
        right -= r;
      }
    }
    return ret;
  }
  
  int rangefreq(int left, int right, T lower, T upper) {
    return freq_dfs(0, left, right, 0, lower, upper);
  }
};



##################################################
############# sqrt-decomposition.cpp #############
##################################################

template< typename T, typename E = int >
struct SqrtDecomposition {

  vector< E > block_add, elem_add;
  vector< int > block_pos;
  vector< T > data, lsum;
  vector< vector< T > > sum;
  int N, B, K;
  E L;

  SqrtDecomposition(int N, E L = 0) : N(N), L(L) { // find the sum of L or more in the interval
    B = (int) sqrt(N);
    K = (N + B - 1) / B;

    block_add.assign(K, 0);
    block_pos.resize(N);
    for(int k = 0; k < K; k++) {
      for(int i = k * B; i < min((k + 1) * B, N); i++) block_pos[i] = k;
    }
    elem_add.assign(N, 0);
    data.assign(N, 0);
    sum.assign(K, vector< T >(B, 0));
    lsum.assign(K, 0);
  }


  void build(const vector< E > &add, const vector< T > &dat) {
    assert(add.size() == elem_add.size());
    assert(dat.size() == data.size());
    elem_add = add;
    data = dat;
    for(int k = 0; k < K; k++) {
      E tap = elem_add[k * B];
      for(int i = k * B; i < min((k + 1) * B, N); i++) tap = min(tap, elem_add[i]);
      block_add[k] = tap;
      for(int i = k * B; i < min((k + 1) * B, N); i++) {
        elem_add[i] -= block_add[k];
        set(i, dat[i]);
      }
    }
  }

  inline void del(int k) {
    sum[block_pos[k]][elem_add[k]] -= data[k];
    if(block_add[block_pos[k]] + elem_add[k] >= L) lsum[block_pos[k]] -= data[k];
  }

  inline void set(int k) {
    while(sum[block_pos[k]].size() <= elem_add[k]) sum[block_pos[k]].push_back(0);
    sum[block_pos[k]][elem_add[k]] += data[k];
    if(block_add[block_pos[k]] + elem_add[k] >= L) lsum[block_pos[k]] += data[k];
  }

  void set(int k, T x) {
    data[k] = x;
    set(k);
  }

  void add(int a, int b) {
    for(int k = 0; k < K; k++) {
      int l = k * B;
      int r = min(l + B, N);

      if(r <= a || b <= l) {

      } else if(a <= l && r <= b) {
        block_add[k]++;
        if(0 <= L - block_add[k] && L - block_add[k] < sum[k].size()) {
          lsum[k] += sum[k][L - block_add[k]];
        }
      } else {
        for(int i = max(a, l); i < min(b, r); i++) {
          del(i);
          elem_add[i]++;
          set(i);
        }
      }
    }
  }


  void sub(int a, int b) {
    for(int k = 0; k < K; k++) {
      int l = k * B;
      int r = min(l + B, N);

      if(r <= a || b <= l) {

      } else if(a <= l && r <= b) {
        if(0 <= L - block_add[k] && L - block_add[k] < sum[k].size()) {
          lsum[k] -= sum[k][L - block_add[k]];
        }
        block_add[k]--;
      } else {
        if(0 <= L - block_add[k] && L - block_add[k] < sum[k].size()) {
          lsum[k] -= sum[k][L - block_add[k]];
        }
        block_add[k]--;
        for(int i = l; i < max(a, l); i++) {
          del(i);
          elem_add[i]++;
          set(i);
        }
        for(int i = min(b, r); i < r; i++) {
          del(i);
          elem_add[i]++;
          set(i);
        }
      }
    }
  }


  T query(int a, int b, E x) {
    T ret = 0;
    for(int k = 0; k < K; k++) {
      int l = k * B;
      int r = min(l + B, N);

      if(r <= a || b <= l) {

      } else if(a <= l && r <= b) {
        if(0 <= x - block_add[k] && x - block_add[k] < sum[k].size()) {
          ret += sum[k][x - block_add[k]];
        }
      } else {
        for(int i = max(a, l); i < min(b, r); i++) {
          if(block_add[k] + elem_add[i] == x) ret += data[i];
        }
      }
    }
    return ret;
  }


  T query_low(int a, int b) {
    T ret = 0;
    for(int k = 0; k < K; k++) {
      int l = k * B;
      int r = min(l + B, N);

      if(r <= a || b <= l) {

      } else if(a <= l && r <= b) {
        ret += lsum[k];
      } else {
        for(int i = max(a, l); i < min(b, r); i++) {
          if(block_add[k] + elem_add[i] >= L) ret += data[i];
        }
      }
    }
    return ret;
  }
};


##################################################
########### priority-sum-structure.cpp ###########
##################################################

template< typename T, typename Compare = less< T >, typename RCompare = greater< T > >
struct PrioritySumStructure {

  size_t k;
  T sum;

  priority_queue< T, vector< T >, Compare > in, d_in;
  priority_queue< T, vector< T >, RCompare > out, d_out;

  PrioritySumStructure(int k) : k(k), sum(0) {}

  void modify() {
    while(in.size() - d_in.size() < k && !out.empty()) {
      auto p = out.top();
      out.pop();
      if(!d_out.empty() && p == d_out.top()) {
        d_out.pop();
      } else {
        sum += p;
        in.emplace(p);
      }
    }
    while(in.size() - d_in.size() > k) {
      auto p = in.top();
      in.pop();
      if(!d_in.empty() && p == d_in.top()) {
        d_in.pop();
      } else {
        sum -= p;
        out.emplace(p);
      }
    }
    while(!d_in.empty() && in.top() == d_in.top()) {
      in.pop();
      d_in.pop();
    }
  }

  T query() const {
    return sum;
  }

  void insert(T x) {
    in.emplace(x);
    sum += x;
    modify();
  }

  void erase(T x) {
    assert(size());
    if(!in.empty() && in.top() == x) {
      sum -= x;
      in.pop();
    } else if(!in.empty() && RCompare()(in.top(), x)) {
      sum -= x;
      d_in.emplace(x);
    } else {
      d_out.emplace(x);
    }
    modify();
  }

  void set_k(size_t kk) {
    k = kk;
    modify();
  }

  size_t get_k() const {
    return k;
  }

  size_t size() const {
    return in.size() + out.size() - d_in.size() - d_out.size();
  }
};

template< typename T >
using MaximumSum = PrioritySumStructure< T, greater< T >, less< T > >;

template< typename T >
using MinimumSum = PrioritySumStructure< T, less< T >, greater< T > >;



##################################################
############### link-cut-tree.cpp ################
##################################################

template< typename Monoid = int, typename OperatorMonoid = Monoid >
struct LinkCutTree {
  using F = function< Monoid(Monoid, Monoid) >;
  using G = function< Monoid(Monoid, OperatorMonoid, int) >;
  using H = function< OperatorMonoid(OperatorMonoid, OperatorMonoid) >;
  using S = function< Monoid(Monoid) >;

  struct Node {
    Node *l, *r, *p;
    int idx;
    Monoid key, sum;
    OperatorMonoid lazy;

    bool rev;
    int sz;

    bool is_root() {
      return !p || (p->l != this && p->r != this);
    }

    Node(int idx, const Monoid &key, const OperatorMonoid &om) :
        idx(idx), key(key), sum(key), lazy(om), sz(1),
        l(nullptr), r(nullptr), p(nullptr), rev(false) {}
  };

  const Monoid M1;
  const OperatorMonoid OM0;
  const F f;
  const G g;
  const H h;
  const S s;

  LinkCutTree() : LinkCutTree([](Monoid a, Monoid b) { return a + b; }, [](Monoid a) { return a; }, Monoid()) {}

  LinkCutTree(const F &f, const S &s, const Monoid &M1) :
      LinkCutTree(f, G(), H(), s, M1, OperatorMonoid()) {}

  LinkCutTree(const F &f, const G &g, const H &h, const S &s,
              const Monoid &M1, const OperatorMonoid &OM0) :
      f(f), g(g), h(h), s(s), M1(M1), OM0(OM0) {}

  Node *make_node(int idx, const Monoid &v = Monoid()) {
    return new Node(idx, v, OM0);
  }

  void propagate(Node *t, const OperatorMonoid &x) {
    t->lazy = h(t->lazy, x);
    t->key = g(t->key, x, 1);
    t->sum = g(t->sum, x, t->sz);
  }

  void toggle(Node *t) {
    assert(t);
    swap(t->l, t->r);
    t->sum = s(t->sum);
    t->rev ^= true;
  }

  void push(Node *t) {
    if(t->lazy != OM0) {
      if(t->l) propagate(t->l, t->lazy);
      if(t->r) propagate(t->r, t->lazy);
      t->lazy = OM0;
    }
    if(t->rev) {
      if(t->l) toggle(t->l);
      if(t->r) toggle(t->r);
      t->rev = false;
    }
  }

  void update(Node *t) {
    t->sz = 1;
    t->sum = t->key;
    if(t->l) t->sz += t->l->sz, t->sum = f(t->l->sum, t->sum);
    if(t->r) t->sz += t->r->sz, t->sum = f(t->sum, t->r->sum);
  }

  void rotr(Node *t) {
    auto *x = t->p, *y = x->p;
    if((x->l = t->r)) t->r->p = x;
    t->r = x, x->p = t;
    update(x), update(t);
    if((t->p = y)) {
      if(y->l == x) y->l = t;
      if(y->r == x) y->r = t;
      update(y);
    }
  }

  void rotl(Node *t) {
    auto *x = t->p, *y = x->p;
    if((x->r = t->l)) t->l->p = x;
    t->l = x, x->p = t;
    update(x), update(t);
    if((t->p = y)) {
      if(y->l == x) y->l = t;
      if(y->r == x) y->r = t;
      update(y);
    }
  }

  void splay(Node *t) {
    push(t);
    while(!t->is_root()) {
      auto *q = t->p;
      if(q->is_root()) {
        push(q), push(t);
        if(q->l == t) rotr(t);
        else rotl(t);
      } else {
        auto *r = q->p;
        push(r), push(q), push(t);
        if(r->l == q) {
          if(q->l == t) rotr(q), rotr(t);
          else rotl(t), rotr(t);
        } else {
          if(q->r == t) rotl(q), rotl(t);
          else rotr(t), rotl(t);
        }
      }
    }
  }

  Node *expose(Node *t) {
    Node *rp = nullptr;
    for(Node *cur = t; cur; cur = cur->p) {
      splay(cur);
      cur->r = rp;
      update(cur);
      rp = cur;
    }
    splay(t);
    return rp;
  }

  void link(Node *child, Node *parent) {
    expose(child);
    expose(parent);
    child->p = parent;
    parent->r = child;
    update(parent);
  }

  void cut(Node *child) {
    expose(child);
    auto *parent = child->l;
    child->l = nullptr;
    parent->p = nullptr;
    update(child);
  }

  void evert(Node *t) {
    expose(t);
    toggle(t);
    push(t);
  }

  Node *lca(Node *u, Node *v) {
    if(get_root(u) != get_root(v)) return nullptr;
    expose(u);
    return expose(v);
  }

  vector< int > get_path(Node *x) {
    vector< int > vs;
    function< void(Node *) > dfs = [&](Node *cur) {
      if(!cur) return;
      push(cur);
      dfs(cur->r);
      vs.push_back(cur->idx);
      dfs(cur->l);
    };
    expose(x);
    dfs(x);
    return vs;
  }

  void set_propagate(Node *t, const OperatorMonoid &x) {
    expose(t);
    propagate(t, x);
    push(t);
  }

  Node *get_kth(Node *x, int k) {
    expose(x);
    while(x) {
      push(x);
      if(x->r && x->r->sz > k) {
        x = x->r;
      } else {
        if(x->r) k -= x->r->sz;
        if(k == 0) return x;
        k -= 1;
        x = x->l;
      }
    }
    return nullptr;
  }

  Node *get_root(Node *x) {
    expose(x);
    while(x->l) {
      push(x);
      x = x->l;
    }
    return x;
  }
};



##################################################
########### persistent-union-find.cpp ############
##################################################

struct PersistentUnionFind
{
  PersistentArray< int, 3 > data;

  PersistentUnionFind() {}

  PersistentUnionFind(int sz)
  {
    data.build(vector< int >(sz, -1));
  }

  int find(int k)
  {
    int p = data.get(k);
    return p >= 0 ? find(p) : k;
  }

  int size(int k)
  {
    return (-data.get(find(k)));
  }

  PersistentUnionFind unite(int x, int y)
  {
    x = find(x);
    y = find(y);
    if(x == y) return *this;
    auto u = data.get(x);
    auto v = data.get(y);

    if(u < v) {
      auto a = data.mutable_get(x);
      *a += v;
      auto b = data.mutable_get(y);
      *b = x;
    } else {
      auto a = data.mutable_get(y);
      *a += u;
      auto b = data.mutable_get(x);
      *b = y;
    }
    return *this;
  }
};


