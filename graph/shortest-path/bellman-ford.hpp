#pragma once

#include "../graph-template.hpp"

/**
 * @brief Bellman-Ford(単一始点最短路)
 * 
 */
template< typename T >
vector< T > bellman_ford(const Edges< T > &edges, int V, int s) {
  const auto INF = numeric_limits< T >::max();
  vector< T > dist(V, INF);
  dist[s] = 0;
  for(int i = 0; i < V - 1; i++) {
    for(auto &e : edges) {
      if(dist[e.from] == INF) continue;
      dist[e.to] = min(dist[e.to], dist[e.from] + e.cost);
    }
  }
  for(auto &e : edges) {
    if(dist[e.from] == INF) continue;
    if(dist[e.from] + e.cost < dist[e.to]) return vector< T >();
  }
  return dist;
}
