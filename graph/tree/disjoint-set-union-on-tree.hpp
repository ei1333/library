#pragma once

#include "../graph-template.hpp"

/**
 * @brief Disjoint-Set-Union-On-Tree
 */
template< typename T >
struct DisjointSetUnionOnTree : Graph< T > {
  using F = function< void(int) >;
  using Graph< T >::g;
  vector< int > heavy, sz, in, out, ord;
  const F expand, shrink, query;
 
  explicit DisjointSetUnionOnTree(int n, F expand, F shrink, F query)
      : Graph< T >(n), expand(move(expand)), shrink(move(shrink)), query(move(query)) {}
 
private:
  queue< int > que;
 
  int build_subtree(int idx) {
    in[idx] = ord.size();
    ord.emplace_back(idx);
    for(auto &to : g[idx]) {
      int sub = build_subtree(to);
      sz[idx] += sub;
      if(heavy[idx] == -1 || sz[heavy[idx]] < sub) {
        heavy[idx] = to;
      }
    }
    out[idx] = ord.size();
    return sz[idx];
  }
 
  void dfs(int idx, bool keep) {
    for(auto &to : g[idx]) {
      if(heavy[idx] == to) continue;
      dfs(to, false);
    }
    if(heavy[idx] != -1) {
      dfs(heavy[idx], true);
    }
    for(auto &to : g[idx]) {
      if(heavy[idx] == to) continue;
      for(int p = in[to]; p < out[to]; p++) {
        expand(ord[p]);
      }
    }
    expand(idx);
    query(idx);
    if(!keep) {
      for(int p = in[idx]; p < out[idx]; p++) shrink(ord[p]);
    }
  }
 
public:
  void build(int root = 0) {
    g = convert_rooted_tree(*this, root).g;
    sz.assign(g.size(), 1);
    heavy.assign(g.size(), -1);
    in.resize(g.size());
    out.resize(g.size());
    build_subtree(root);
    dfs(root, false);
  }
};
