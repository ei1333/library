template< typename T >
T prim_fibonacchi_heap(WeightedGraph< T > &g) {
  const auto INF = numeric_limits< T >::max();
  using Heap = FibonacchiHeap< T, int >;
  using Node = typename Heap::Node;
  using Pi = pair< T, int >;

  T total = 0;
  vector< T > dist(g.size(), INF);
  vector< int > used(g.size());
  Heap heap;
  vector< Node * > keep(g.size(), nullptr);
  dist[0] = 0;
  keep[0] = heap.push(0, 0);

  while(!heap.empty()) {
    T cost;
    int idx;
    tie(cost, idx) = heap.pop();
    if(used[idx]) continue;
    used[idx] = true;
    total += cost;
    for(auto &e : g[idx]) {
      if(used[e.to] || dist[e.to] <= e.cost) continue;
      if(keep[e.to] == nullptr) {
        dist[e.to] = e.cost;
        keep[e.to] = heap.push(e.cost, e.to);
      } else {
        T d = dist[e.to] - e.cost;
        heap.decrease_key(keep[e.to], d);
        dist[e.to] -= d;
      }
    }
  }
  return total;
}
