#pragma once

#include "../graph-template.hpp"

/**
 * @brief Prim(最小全域木)
 * 
 */
template< typename T >
struct MinimumSpanningTree {
  T cost;
  Edges< T > edges;
};

template< typename T >
MinimumSpanningTree< T > prim(const Graph< T > &g) {
  T total = T();
  vector< int > used(g.size());
  vector< Edge< T > * > dist(g.size());
  using pi = pair< T, int >;
  priority_queue< pi, vector< pi >, greater<> > que;
  que.emplace(T(), 0);
  Edges< T > edges;
  while(!que.empty()) {
    auto p = que.top();
    que.pop();
    if(used[p.second]) continue;
    used[p.second] = true;
    total += p.first;
    if(dist[p.second]) edges.emplace_back(*dist[p.second]);
    for(auto &e : g[p.second]) {
      if(used[e.to] || (dist[e.to] && dist[e.to]->cost <= e.cost)) continue;
      que.emplace(e.cost, e.to);
    }
  }
  return {total, edges};
}
