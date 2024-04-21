#pragma once

#include "../graph-template.hpp"
#include "../../structure/heap/fibonacchi-heap.hpp"

/**
 * @brief Prim Fibonacchi Heap(最小全域木)
 * 
 */
template< typename T >
struct MinimumSpanningTree {
  T cost;
  Edges< T > edges;
};

template< typename T >
MinimumSpanningTree< T > prim_fibonacchi_heap(Graph< T > &g) {
  using Heap = FibonacchiHeap< T, int >;
  using Node = typename Heap::Node;

  T total = 0;
  vector< Edge< T > * > dist(g.size());
  vector< int > used(g.size());
  Heap heap;
  vector< Node * > keep(g.size(), nullptr);
  keep[0] = heap.push(0, 0);
  Edges< T > es;
  while(!heap.empty()) {
    T cost;
    int idx;
    tie(cost, idx) = heap.pop();
    if(used[idx]) continue;
    used[idx] = true;
    total += cost;
    if(dist[idx]) es.emplace_back(*dist[idx]);
    for(auto &e : g[idx]) {
      if(used[e.to] || (dist[e.to] && dist[e.to]->cost <= e.cost)) continue;
      if(keep[e.to] == nullptr) {
        dist[e.to] = &e;
        keep[e.to] = heap.push(e.cost, e.to);
      } else {
        T d = dist[e.to]->cost - e.cost;
        heap.decrease_key(keep[e.to], d);
        dist[e.to] = &e;
      }
    }
  }
  return {total, es};
}

