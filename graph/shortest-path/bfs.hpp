#pragma once

#include "../graph-template.hpp"

/**
 * @brief BFS(幅優先探索)
 */
template< typename T >
vector< T > bfs(const Graph< T > &g, int s) {
  T max_cost = 0, beet = 0;
  for(auto &es : g.g) {
    for(auto &e : es) max_cost = max(max_cost, e.cost);
  }
  ++max_cost;
  const auto INF = numeric_limits< T >::max();
  vector< T > dist(g.size(), INF);
  vector< queue< int > > ques(max_cost + 1);
  dist[s] = 0;
  ques[0].emplace(s);
  for(T cost = 0; cost <= beet; cost++) {
    auto &que = ques[cost % max_cost];
    while(!que.empty()) {
      int idx = que.front();
      que.pop();
      if(dist[idx] < cost) continue;
      for(auto &e : g[idx]) {
        auto next_cost = cost + e.cost;
        if(dist[e.to] <= next_cost) continue;;
        dist[e.to] = next_cost;
        beet = max(beet, dist[e.to]);
        ques[dist[e.to] % max_cost].emplace(e.to);
      }
    }
  }
  return dist;
}
