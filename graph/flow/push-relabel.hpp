class Stack {
private:
  const int N, H;
  vector< int > node;
 
public:
  Stack(const int N, const int H) : N(N), H(H), node(N + H) { clear(); }
 
  inline bool empty(const int h) const { return node[N + h] == N + h; }
 
  inline int top(const int h) const { return node[N + h]; }
 
  inline void pop(const int h) { node[N + h] = node[node[N + h]]; }
 
  inline void push(const int h, const int u) { node[u] = node[N + h], node[N + h] = u; }
 
  inline void clear() { iota(node.begin() + N, node.end(), N); }
};
 
class List {
public:
  struct node {
    int prev, next;
  };
  const int N, H;
  vector< node > dat;
 
  List(const int N, const int H) : N(N), H(H), dat(N + H) { clear(); }
 
  inline bool empty(const int h) const { return (dat[N + h].next == N + h); }
 
  inline bool more_one(const int h) const { return dat[N + h].prev != dat[N + h].next; }
 
  inline void insert(const int h, const int u) {
    dat[u].prev = dat[N + h].prev, dat[u].next = N + h;
    dat[dat[N + h].prev].next = u, dat[N + h].prev = u;
  }
 
  inline void erase(const int u) {
    dat[dat[u].prev].next = dat[u].next, dat[dat[u].next].prev = dat[u].prev;
  }
 
  inline void clear() {
    for(int i = N; i < N + H; ++i) dat[i].prev = dat[i].next = i;
  }
};

template< typename flow_t >
struct PushRelabel {
  struct edge {
    int to;
    flow_t cap;
    int rev;
    bool isrev;
    int idx;
  };

  int V, height, relabels;
  vector< flow_t > ex;
  vector< int > potential, cur_edge;
  List all_ver;
  Stack act_ver;
  vector< vector< edge > > graph;

  PushRelabel(int V)
      : V(V), height(-1), relabels(0), ex(V, flow_t(0)), potential(V, 0), cur_edge(V), all_ver(V, V), act_ver(V, V), graph(V) {}

  void add_edge(int from, int to, flow_t cap, int idx = -1) {
    graph[from].emplace_back((edge) {to, cap, (int) graph[to].size(), false, idx});
    graph[to].emplace_back((edge) {from, 0, (int) graph[from].size() - 1, true, idx});
  }

  int calc_active(int t) {
    height = -1;
    for(int i = 0; i < V; i++) {
      if(potential[i] < V) {
        cur_edge[i] = 0;
        height = max(height, potential[i]);
        all_ver.insert(potential[i], i);
        if(ex[i] > 0 && i != t) act_ver.push(potential[i], i);
      } else {
        potential[i] = V + 1;
      }
    }
    return height;
  }

  void bfs(int t) {
    for(int i = 0; i < V; i++) {
      potential[i] = max(potential[i], V);
    }
    potential[t] = 0;
    queue< int > que;
    que.emplace(t);
    while(!que.empty()) {
      int p = que.front();
      que.pop();
      for(auto &e : graph[p]) {
        if(potential[e.to] == V && graph[e.to][e.rev].cap > 0) {
          potential[e.to] = potential[p] + 1;
          que.emplace(e.to);
        }
      }
    }
  }

  int init(int s, int t) {
    potential[s] = V + 1;
    bfs(t);
    for(auto &e : graph[s]) {
      if(potential[e.to] < V) {
        graph[e.to][e.rev].cap = e.cap;
        ex[s] -= e.cap;
        ex[e.to] += e.cap;
      }
      e.cap = 0;
    }
    return calc_active(t);
  }

  bool push(int u, int t, edge &e) {
    flow_t f = min(e.cap, ex[u]);
    int v = e.to;
    e.cap -= f, ex[u] -= f;
    graph[v][e.rev].cap += f, ex[v] += f;
    if(ex[v] == f && v != t) act_ver.push(potential[v], v);
    return ex[u] == 0;
  }

  int discharge(int u, int t) {
    for(int &i = cur_edge[u]; i < (int)graph[u].size(); i++) {
      auto &e = graph[u][i];
      if(potential[u] == potential[e.to] + 1 && e.cap > 0) {
        if(push(u, t, e)) return potential[u];
      }
    }
    return relabel(u);
  }

  int global_relabel(int t) {
    bfs(t);
    all_ver.clear(), act_ver.clear();
    return calc_active(t);
  }

  void gap_relabel(const int u) {
    for(int i = potential[u]; i <= height; ++i) {
      for(int id = all_ver.dat[V + i].next; id < V; id = all_ver.dat[id].next) {
        potential[id] = V + 1;
      }
      all_ver.dat[V + i].prev = all_ver.dat[V + i].next = V + i;
    }
  }

  int relabel(const int u) {
    ++relabels;
    int prv = potential[u], cur = V;
    for(int i = 0; i < (int) graph[u].size(); ++i) {
      const edge &e = graph[u][i];
      if(cur > potential[e.to] + 1 && e.cap > 0) {
        cur_edge[u] = i;
        cur = potential[e.to] + 1;
      }
    }
    if(all_ver.more_one(prv)) {
      all_ver.erase(u);
      if((potential[u] = cur) == V) return potential[u] = V + 1, prv;
      act_ver.push(cur, u);
      all_ver.insert(cur, u);
      height = max(height, cur);
    } else {
      gap_relabel(u);
      return height = prv - 1;
    }
    return cur;
  }

  flow_t max_flow(int s, int t) {
    int level = init(s, t);
    while(level >= 0) {
      if(act_ver.empty(level)) {
        --level;
        continue;
      }
      int u = act_ver.top(level);
      act_ver.pop(level);
      level = discharge(u, t);
      if(relabels * 2 >= V) {
        level = global_relabel(t);
        relabels = 0;
      }
    }
    return ex[t];
  }
};
