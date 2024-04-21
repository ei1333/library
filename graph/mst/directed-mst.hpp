#pragma once

#include "../graph-template.hpp"
#include "../../structure/heap/skew-heap.hpp"

/**
 * @brief Directed MST(最小有向全域木)
 * 
 */
template< typename T >
struct MinimumSpanningTree {
  T cost;
  Edges< T > edges;
};

template< typename T >
MinimumSpanningTree< T > directed_mst(int V, int root, Edges< T > edges) {
  for(int i = 0; i < V; ++i) {
    if(i != root) edges.emplace_back(i, root, 0);
  }

  int x = 0;
  vector< int > par(2 * V, -1), vis(par), link(par);

  using Heap = SkewHeap< T, true >;
  using Node = typename Heap::Node;

  Heap heap;
  vector< Node * > ins(2 * V, heap.make_root());

  for(int i = 0; i < (int) edges.size(); i++) {
    auto &e = edges[i];
    ins[e.to] = heap.push(ins[e.to], e.cost, i);
  }
  vector< int > st;
  auto go = [&](int x) {
    x = edges[ins[x]->idx].from;
    while(link[x] != -1) {
      st.emplace_back(x);
      x = link[x];
    }
    for(auto &p : st) {
      link[p] = x;
    }
    st.clear();
    return x;
  };
  for(int i = V; ins[x]; i++) {
    for(; vis[x] == -1; x = go(x)) vis[x] = 0;
    for(; x != i; x = go(x)) {
      auto w = ins[x]->key;
      auto v = heap.pop(ins[x]);
      v = heap.add(v, -w);
      ins[i] = heap.meld(ins[i], v);
      par[x] = i;
      link[x] = i;
    }
    for(; ins[x] && go(x) == x; ins[x] = heap.pop(ins[x]));
  }
  T cost = 0;
  Edges< T > ans;
  for(int i = root; i != -1; i = par[i]) {
    vis[i] = 1;
  }
  for(int i = x; i >= 0; i--) {
    if(vis[i] == 1) continue;
    cost += edges[ins[i]->idx].cost;
    ans.emplace_back(edges[ins[i]->idx]);
    for(int j = edges[ins[i]->idx].to; j != -1 && vis[j] == 0; j = par[j]) {
      vis[j] = 1;
    }
  }
  return {cost, ans};
}
