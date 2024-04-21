#pragma once

#include "../graph-template.hpp"

/**
 * @brief Centroid(木の重心)
 * 
 */
template< typename T >
vector< int > centroid(const Graph< T > &g) {
  const int N = (int) g.size();

  stack< pair< int, int > > st;
  st.emplace(0, -1);
  vector< int > sz(N), par(N);
  while(!st.empty()) {
    auto p = st.top();
    if(sz[p.first] == 0) {
      sz[p.first] = 1;
      for(auto &to : g[p.first]) if(to != p.second) st.emplace(to, p.first);
    } else {
      for(auto &to : g[p.first]) if(to != p.second) sz[p.first] += sz[to];
      par[p.first] = p.second;
      st.pop();
    }
  }

  vector< int > ret;
  int size = N;
  for(int i = 0; i < N; i++) {
    int val = N - sz[i];
    for(auto &to : g[i]) if(to != par[i]) val = max(val, sz[to]);
    if(val < size) size = val, ret.clear();
    if(val == size) ret.emplace_back(i);
  }

  return ret;
}
