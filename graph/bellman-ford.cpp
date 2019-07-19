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

