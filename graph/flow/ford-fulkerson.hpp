/**
 * @brief Ford Fulkerson(最大流)
 * 
 */
template< typename flow_t >
struct FordFulkerson {
  struct edge {
    int to;
    flow_t cap;
    int rev;
    bool isrev;
    int idx;
  };

  const flow_t INF;
  vector< vector< edge > > graph;
  vector< int > used;
  int timestamp;

  explicit FordFulkerson(int V) : INF(numeric_limits< flow_t >::max()), graph(V), used(V, -1), timestamp(0) {}

  void add_edge(int from, int to, flow_t cap, int idx = -1) {
    graph[from].emplace_back((edge) {to, cap, (int) graph[to].size(), false, idx});
    graph[to].emplace_back((edge) {from, 0, (int) graph[from].size() - 1, true, idx});
  }

  flow_t find_augment_path(int idx, const int t, flow_t flow) {
    if(idx == t) return flow;
    used[idx] = timestamp;
    for(auto &e : graph[idx]) {
      if(e.cap > 0 && used[e.to] != timestamp) {
        flow_t d = find_augment_path(e.to, t, min(flow, e.cap));
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
    for(flow_t f; (f = find_augment_path(s, t, INF)) > 0; timestamp++) {
      flow += f;
    }
    timestamp++;
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
