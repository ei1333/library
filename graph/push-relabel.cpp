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
