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

