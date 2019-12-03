template< typename T >
vector< T > dijkstra_radix_heap(WeightedGraph< T > &g, int s) {
  const auto INF = numeric_limits< T >::max();
  vector< T > dist(g.size(), INF);

  using Pi = pair< T, int >;
  RadixHeap< T, int > heap;
  dist[s] = 0;
  heap.push(dist[s], s);
  while(!heap.empty()) {
    T cost;
    int idx;
    tie(cost, idx) = heap.pop();
    if(dist[idx] < cost) continue;
    for(auto &e : g[idx]) {
      auto next_cost = cost + e.cost;
      if(dist[e.to] <= next_cost) continue;
      dist[e.to] = next_cost;
      heap.push(dist[e.to], e.to);
    }
  }
  return dist;
}
