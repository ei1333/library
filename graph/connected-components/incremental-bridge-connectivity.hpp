#pragma once

#include "../../structure/union-find/union-find.cpp"

/**
 * @brief Incremental Bridge Connectivity
 * @docs docs/incremental-bridge-connectivity.md
 * @see https://scrapbox.io/data-structures/Incremental_Bridge-Connectivity
 */
struct IncrementalBridgeConnectivity {
private:
  UnionFind cc, bcc;
  vector< int > bbf;
  size_t bridge;

  int size() {
    return bbf.size();
  }

  int par(int x) {
    return bbf[x] == size() ? size() : bcc.find(bbf[x]);
  }

  int lca(int x, int y) {
    unordered_set< int > used;
    for(;;) {
      if(x != size()) {
        if(!used.insert(x).second) return x;
        x = par(x);
      }
      swap(x, y);
    }
  }

  void compress(int x, int y) {
    while(bcc.find(x) != bcc.find(y)) {
      int nxt = par(x);
      bbf[x] = bbf[y];
      bcc.unite(x, y);
      x = nxt;
      --bridge;
    }
  }

  void link(int x, int y) {
    int v = x, pre = y;
    while(v != size()) {
      int nxt = par(v);
      bbf[v] = pre;
      pre = v;
      v = nxt;
    }
  }

public:
  IncrementalBridgeConnectivity() = default;

  explicit IncrementalBridgeConnectivity(int sz) : cc(sz), bcc(sz), bbf(sz, sz), bridge(0) {}

  int find(int k) {
    return bcc.find(k);
  }

  size_t bridge_size() const {
    return bridge;
  }

  void add_edge(int x, int y) {
    x = bcc.find(x);
    y = bcc.find(y);
    if(cc.find(x) == cc.find(y)) {
      int w = lca(x, y);
      compress(x, w);
      compress(y, w);
    } else {
      if(cc.size(x) > cc.size(y)) swap(x, y);
      link(x, y);
      cc.unite(x, y);
      ++bridge;
    }
  }
};
