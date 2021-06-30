#pragma once

#include "../template.hpp"

template< typename T >
void warshall_floyd(Matrix< T > &g, T INF) {
  for(size_t k = 0; k < g.size(); k++) {
    for(size_t i = 0; i < g.size(); i++) {
      for(size_t j = 0; j < g.size(); j++) {
        if(g[i][k] == INF || g[k][j] == INF) continue;
        g[i][j] = min(g[i][j], g[i][k] + g[k][j]);
      }
    }
  }
}
