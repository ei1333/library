#pragma once

#include "../graph-template.hpp"
#include "../../structure/union-find/union-find.hpp"

/**
 * @brief Kruskal(最小全域木)
 * 
 */
template< typename T >
struct MinimumSpanningTree {
  T cost;
  Edges< T > edges;
};

template< typename T >
MinimumSpanningTree< T > kruskal(Edges< T > &edges, int V) {
  sort(begin(edges), end(edges), [](const Edge< T > &a, const Edge< T > &b) {
    return a.cost < b.cost;
  });
  UnionFind tree(V);
  T total = T();
  Edges< T > es;
  for(auto &e : edges) {
    if(tree.unite(e.from, e.to)) {
      es.emplace_back(e);
      total += e.cost;
    }
  }
  return {total, es};
}
