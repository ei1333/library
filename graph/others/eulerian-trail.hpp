#pragma once

#include "../../structure/union-find/union-find.hpp"

/**
 * @brief Eulerian Trail(オイラー路)
 * 
 */
template< bool directed >
struct EulerianTrail {
  vector< vector< pair< int, int > > > g;
  vector< pair< int, int > > es;
  int M;
  vector< int > used_vertex, used_edge, deg;

  explicit EulerianTrail(int V) : g(V), M(0), used_vertex(V), deg(V) {}

  void add_edge(int a, int b) {
    es.emplace_back(a, b);
    g[a].emplace_back(b, M);
    if(directed) {
      deg[a]++;
      deg[b]--;
    } else {
      g[b].emplace_back(a, M);
      deg[a]++;
      deg[b]++;
    }
    M++;
  }

  pair< int, int > get_edge(int idx) const {
    return es[idx];
  }

  vector< vector< int > > enumerate_eulerian_trail() {
    if(directed) {
      for(auto &p : deg) if(p != 0) return {};
    } else {
      for(auto &p : deg) if(p & 1) return {};
    }
    used_edge.assign(M, 0);
    vector< vector< int > > ret;
    for(int i = 0; i < (int) g.size(); i++) {
      if(g[i].empty() || used_vertex[i]) continue;
      ret.emplace_back(go(i));
    }
    return ret;
  }

  vector< vector< int > > enumerate_semi_eulerian_trail() {
    UnionFind uf(g.size());
    for(auto &p : es) uf.unite(p.first, p.second);
    vector< vector< int > > group(g.size());
    for(int i = 0; i < (int) g.size(); i++) group[uf.find(i)].emplace_back(i);
    vector< vector< int > > ret;
    used_edge.assign(M, 0);
    for(auto &vs : group) {
      if(vs.empty()) continue;
      int latte = -1, malta = -1;
      if(directed) {
        for(auto &p : vs) {
          if(abs(deg[p]) > 1) {
            return {};
          } else if(deg[p] == 1) {
            if(latte >= 0) return {};
            latte = p;
          }
        }
      } else {
        for(auto &p : vs) {
          if(deg[p] & 1) {
            if(latte == -1) latte = p;
            else if(malta == -1) malta = p;
            else return {};
          }
        }
      }
      ret.emplace_back(go(latte == -1 ? vs.front() : latte));
      if(ret.back().empty()) ret.pop_back();
    }
    return ret;
  }

  vector< int > go(int s) {
    stack< pair< int, int > > st;
    vector< int > ord;
    st.emplace(s, -1);
    while(!st.empty()) {
      int idx = st.top().first;
      used_vertex[idx] = true;
      if(g[idx].empty()) {
        ord.emplace_back(st.top().second);
        st.pop();
      } else {
        auto e = g[idx].back();
        g[idx].pop_back();
        if(used_edge[e.second]) continue;
        used_edge[e.second] = true;
        st.emplace(e);
      }
    }
    ord.pop_back();
    reverse(ord.begin(), ord.end());
    return ord;
  }
};
