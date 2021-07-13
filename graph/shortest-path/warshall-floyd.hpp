/**
 * @brief Warshall Floyd(全点対間最短路)
 */
template< typename Matrix, typename T >
void warshall_floyd(Matrix &g, T INF) {
  for(size_t k = 0; k < g.size(); k++) {
    for(size_t i = 0; i < g.size(); i++) {
      for(size_t j = 0; j < g.size(); j++) {
        if(g[i][k] == INF || g[k][j] == INF) continue;
        g[i][j] = min(g[i][j], g[i][k] + g[k][j]);
      }
    }
  }
}
