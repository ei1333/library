#pragma once

#include "../graph-template.hpp"
#include "../others/low-link.hpp"

/**
 * @brief Two Edge Connected Components(二重辺連結成分分解)
 * @docs docs/two-edge-connected-components.md
 */
template< typename T = int >
struct TwoEdgeConnectedComponents : LowLink< T > {
public:
  using LowLink< T >::LowLink;
  using LowLink< T >::g;
  using LowLink< T >::ord;
  using LowLink< T >::low;
  using LowLink< T >::bridge;

  vector< int > comp;
  Graph< T > tree;
  vector< vector< int > > group;

  int operator[](const int &k) const {
    return comp[k];
  }

  void build() override {
    LowLink< T >::build();
    comp.assign(g.size(), -1);
    int k = 0;
    for(int i = 0; i < (int) comp.size(); i++) {
      if(comp[i] == -1) dfs(i, -1, k);
    }
    group.resize(k);
    for(int i = 0; i < (int) g.size(); i++) {
      group[comp[i]].emplace_back(i);
    }
    tree = Graph< T >(k);
    for(auto &e : bridge) {
      tree.add_edge(comp[e.from], comp[e.to], e.cost);
    }
  }

  explicit TwoEdgeConnectedComponents(const Graph< T > &g) : Graph< T >(g) {}

private:
  void dfs(int idx, int par, int &k) {
    if(par >= 0 && ord[par] >= low[idx]) comp[idx] = comp[par];
    else comp[idx] = k++;
    for(auto &to : g[idx]) {
      if(comp[to] == -1) dfs(to, idx, k);
    }
  }
};
