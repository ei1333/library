#pragma once

#include "../graph-template.hpp"

/**
 * @brief Convert-Rooted-Tree(根付き木に変換)
 */
template< typename T >
Graph< T > convert_rooted_tree(const Graph< T > &g, int r = 0) {
  int N = (int) g.size();
  Graph< T > rg(N);
  vector< int > v(N);
  v[r] = 1;
  queue< int > que;
  que.emplace(r);
  while(!que.empty()) {
    auto p = que.front();
    que.pop();
    for(auto &to : g[p]) {
      if(v[to] == 0) {
        v[to] = 1;
        que.emplace(to);
        rg.add_directed_edge(p, to, to.cost);
      }
    }
  }
  return rg;
}
