#include "suffix-array.hpp"

/**
 * @brief LCP Array
 */
template< typename T >
vector< int > lcp_array(const SuffixArray< T > &sa) {
  int n = (int) sa.size() - 1;
  vector< int > lcp(n + 1), rank(n + 1);
  for(int i = 0; i <= n; i++) {
    rank[sa[i]] = i;
  }
  int h = 0;
  for(int i = 0; i <= n; i++) {
    if(rank[i] < n) {
      int j = sa[rank[i] + 1];
      for(; j + h < n && i + h < n; h++) {
        if(sa.vs[j + h] != sa.vs[i + h]) break;
      }
      lcp[rank[i] + 1] = h;
      if(h > 0) h--;
    }
  }
  return lcp;
}

