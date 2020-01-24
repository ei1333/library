template< typename T >
struct MinimumSpanningTree {
  T cost;
  Edges< T > edges;
};

template< typename T >
MinimumSpanningTree< T > prim(WeightedGraph< T > &g) {
  T total = T();
  vector< int > used(g.size());
  used[0] = true;
  auto cmp = [](const edge< T > &a, const edge< T > &b) {
    return a.cost > b.cost;
  };
  priority_queue< edge< T >, vector< edge< T > >, decltype(cmp) > que(cmp);
  Edges< T > edges;
  for(auto e : g[0]) {
    e.src = 0;
    que.emplace(e);
  }
  while(!que.empty()) {
    auto p = que.top();
    que.pop();
    if(used[p.to]) continue;
    used[p.to] = true;
    total += p.cost;
    que.emplace(p);
    for(auto e : g[p.to]) {
      if(used[e.to]) continue;
      e.src = p.to;
      que.emplace(e);
    }
  }
  return {total, edges};
}
