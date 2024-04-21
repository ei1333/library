#pragma once

#include "../graph-template.hpp"

/**
 * @brief Dijkstra(単一始点最短路)
 * 
 */
template< typename T >
struct ShortestPath {
  vector< T > dist;
  vector< int > from, id;
};

template< typename T >
ShortestPath< T > dijkstra(const Graph< T > &g, int s) {
  const auto INF = numeric_limits< T >::max();
  vector< T > dist(g.size(), INF);
  vector< int > from(g.size(), -1), id(g.size(), -1);
  using Pi = pair< T, int >;
  priority_queue< Pi, vector< Pi >, greater<> > que;
  dist[s] = 0;
  que.emplace(dist[s], s);
  while(!que.empty()) {
    T cost;
    int idx;
    tie(cost, idx) = que.top();
    que.pop();
    if(dist[idx] < cost) continue;
    for(auto &e : g[idx]) {
      auto next_cost = cost + e.cost;
      if(dist[e.to] <= next_cost) continue;
      dist[e.to] = next_cost;
      from[e.to] = idx;
      id[e.to] = e.idx;
      que.emplace(dist[e.to], e.to);
    }
  }
  return {dist, from, id};
}
