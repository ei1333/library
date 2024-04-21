#pragma once

#include "../graph-template.hpp"

/**
 * @brief Enumerate Triangles(三角形全列挙)
 * 
 */
template< typename T >
vector< tuple< int, int, int > > enumerate_triangles(const Graph< T > &g) {
  int N = (int) g.size();
  using pi = pair< int, int >;
  vector< pi > vp(N);
  for(int i = 0; i < N; i++) {
    vp[i] = {(int) g[i].size(), i};
  }
  vector< vector< int > > h(N);
  for(int i = 0; i < N; i++) {
    for(auto &j : g[i]) {
      if(vp[i] > vp[j]) {
        h[i].emplace_back(j);
      }
    }
  }
  vector< tuple< int, int, int > > triangle;
  vector< int > used(N);
  for(int x = 0; x < N; x++) {
    for(int z : h[x]) used[z] = true;
    for(int y : h[x]) {
      for(int z : h[y]) {
        if(used[z]) triangle.emplace_back(x, y, z);
      }
    }
    for(int z : h[x]) used[z] = false;
  }

  return triangle;
}
