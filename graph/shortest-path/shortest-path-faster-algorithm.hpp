#pragma once

#include "../graph-template.hpp"

/**
 * @brief Shortest-Path-Faster-Algorithm(単一始点最短路)
 */
template< typename T >
vector< T > shortest_path_faster_algorithm(const Graph< T > &g, int s) {
  const auto INF = numeric_limits< T >::max();
  vector< T > dist(g.size(), INF);
  vector< int > pending(g.size(), 0), times(g.size(), 0);
  queue< int > que;

  que.emplace(s);
  pending[s] = true;
  ++times[s];
  dist[s] = 0;

  while(!que.empty()) {
    int p = que.front();
    que.pop();
    pending[p] = false;
    for(auto &e : g[p]) {
      T next_cost = dist[p] + e.cost;
      if(next_cost >= dist[e.to]) continue;
      dist[e.to] = next_cost;
      if(!pending[e.to]) {
        if(++times[e.to] >= (int)g.size()) return vector< T >();
        pending[e.to] = true;
        que.emplace(e.to);
      }
    }
  }
  return dist;
}
