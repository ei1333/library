#include "../../structure/union-find/union-find.hpp"

/**
 * @brief Boruvka(最小全域木)
 * 
 */
template< typename T >
struct Boruvka {
private:
  size_t V;
  UnionFind uf;
  const T INF;

public:
  explicit Boruvka(size_t V, T INF = numeric_limits< T >::max()) : V(V), uf(V), INF(INF) {}

  inline int find(int k) {
    return uf.find(k);
  }

  template< typename F >
  T build(const F &update) {
    T ret = T();
    while(uf.size(0) < (int)V) {
      vector< pair< T, int > > v(V, make_pair(INF, -1));
      update(v);
      bool con = false;
      for(int i = 0; i < (int)V; i++) {
        if(v[i].second >= 0 && uf.unite(i, v[i].second)) {
          ret += v[i].first;
          con = true;
        }
      }
      if(!con) return INF;
    }
    return ret;
  }
};
