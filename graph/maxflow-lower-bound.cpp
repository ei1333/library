template< typename flow_t, template< typename > class F >
struct MaxFlowLowerBound {
  F< flow_t > flow;
  int X, Y;
  flow_t low_sum;

  MaxFlowLowerBound(int V) : flow(V + 2), X(V), Y(V + 1), low_sum(0) {}

  void add_edge(int from, int to, flow_t low, flow_t high) {
    flow.add_edge(from, to, high - low);
    flow.add_edge(X, to, low);
    flow.add_edge(from, Y, low);
    low_sum += low;
  }

  flow_t max_flow(int s, int t) {
    auto a = flow.max_flow(X, Y);
    auto b = flow.max_flow(s, Y);
    auto c = flow.max_flow(X, t);
    auto d = flow.max_flow(s, t);
    return b == c && a + b == low_sum ? b + d : -1;
  }
};
