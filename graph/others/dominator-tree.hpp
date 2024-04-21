#pragma once

#include "../graph-template.hpp"

/**
 * @brief Dominator Tree
 * 
 * @see http://sigma425.hatenablog.com/entry/2015/12/25/224053
 */
template< typename T = int >
struct DominatorTree : Graph< T > {
public:
  using Graph< T >::Graph;
  using Graph< T >::g;

  void build(int root) {
    rg = Graph< T >(g.size());
    par.assign(g.size(), 0);
    idom.assign(g.size(), -1);
    semi.assign(g.size(), -1);
    ord.reserve(g.size());
    UnionFind uf(semi);

    const int N = (int) g.size();
    dfs(root);
    for(int i = 0; i < N; i++) {
      for(auto &to : g[i]) {
        if(~semi[i]) rg.add_directed_edge(to, i);
      }
    }

    vector< vector< int > > bucket(N);
    vector< int > U(N);
    for(int i = (int) ord.size() - 1; i >= 0; i--) {
      int x = ord[i];
      for(int v : rg[x]) {
        v = uf.eval(v);
        if(semi[x] > semi[v]) semi[x] = semi[v];
      }
      bucket[ord[semi[x]]].emplace_back(x);
      for(int v : bucket[par[x]]) U[v] = uf.eval(v);
      bucket[par[x]].clear();
      uf.link(par[x], x);
    }
    for(int i = 1; i < (int)ord.size(); i++) {
      int x = ord[i], u = U[x];
      idom[x] = semi[x] == semi[u] ? semi[x] : idom[u];
    }
    for(int i = 1; i < (int)ord.size(); i++) {
      int x = ord[i];
      idom[x] = ord[idom[x]];
    }
    idom[root] = root;
  }

  int operator[](const int &k) const {
    return idom[k];
  }

private:
  Graph< T > rg;

  struct UnionFind {
    const vector< int > &semi;
    vector< int > par, m;

    explicit UnionFind(const vector< int > &semi) : semi(semi), par(semi.size()), m(semi.size()) {
      iota(begin(par), end(par), 0);
      iota(begin(m), end(m), 0);
    }

    int find(int v) {
      if(par[v] == v) return v;
      int r = find(par[v]);
      if(semi[m[v]] > semi[m[par[v]]]) m[v] = m[par[v]];
      return par[v] = r;
    }

    int eval(int v) {
      find(v);
      return m[v];
    }

    void link(int p, int c) {
      par[c] = p;
    }
  };

  vector< int > ord, par;
  vector< int > idom, semi;

  void dfs(int idx) {
    semi[idx] = (int) ord.size();
    ord.emplace_back(idx);
    for(auto &to : g[idx]) {
      if(~semi[to]) continue;
      dfs(to);
      par[to] = idx;
    }
  }
};
