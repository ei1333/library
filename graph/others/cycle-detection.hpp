#pragma once

#include "../graph-template.hpp"

/**
 * @brief Cycle Detection(閉路検出)
 * 
 */
template< typename T = int >
struct CycleDetection : Graph< T > {
  using Graph< T >::Graph;
  using Graph< T >::g;

  vector< int > used;
  Edges< T > pre, cycle;

  bool dfs(int idx) {
    used[idx] = 1;
    for(auto &e : g[idx]) {
      if(used[e] == 0) {
        pre[e] = e;
        if(dfs(e)) return true;
      } else if(used[e] == 1) {
        int cur = idx;
        while(cur != e) {
          cycle.emplace_back(pre[cur]);
          cur = pre[cur].from;
        }
        cycle.emplace_back(e);
        return true;
      }
    }

    used[idx] = 2;
    return false;
  }

  Edges< T > build() {
    used.assign(g.size(), 0);
    pre.resize(g.size());
    for(int i = 0; i < (int) g.size(); i++) {
      if(used[i] == 0 && dfs(i)) {
        reverse(begin(cycle), end(cycle));
        return cycle;
      }
    }
    return {};
  }
};
