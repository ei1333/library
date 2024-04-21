#pragma once

#include "../graph-template.hpp"
#include "../../structure/others/plus-minus-one-rmq.hpp"

/**
 * @brief PMORMQ-Lowest-Common-Ancestor(最小共通祖先)
 * 
 **/
template< typename T = int >
struct PMORMQLowestCommonAncestor : Graph< T > {
public:
  using Graph< T >::Graph;
  using Graph< T >::g;
  using F = function< int(int, int) >;

  void build(int root = 0) {
    ord.reserve(g.size() * 2 - 1);
    dep.reserve(g.size() * 2 - 1);
    in.resize(g.size());
    dfs(root, -1, 0);
    vector< int > vs(g.size() * 2 - 1);
    iota(begin(vs), end(vs), 0);
    st = PlusMinusOneRMQ< int >(dep);
  }

  int lca(int x, int y) const {
    if(in[x] > in[y]) swap(x, y);
    return ord[st.fold(in[x], in[y] + 1).second];
  }

private:
  vector< int > ord, dep, in;
  PlusMinusOneRMQ< int > st;

  void dfs(int idx, int par, int d) {
    in[idx] = (int) ord.size();
    ord.emplace_back(idx);
    dep.emplace_back(d);
    for(auto &to : g[idx]) {
      if(to != par) {
        dfs(to, idx, d + 1);
        ord.emplace_back(idx);
        dep.emplace_back(d);
      }
    }
  }
};
