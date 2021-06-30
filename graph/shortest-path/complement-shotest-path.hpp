#pragma once

#include "../graph-template.hpp"

/**
 * @brief Complement-Shortest-Path(補グラフ最短路)
 */
template< typename T >
struct ComplementShortestPath : Graph< T > {
  using Graph< T >::Graph;
  using Graph< T >::g;

  vector< vector< T > > dists;

  void build() {
    for(auto &es : g) {
      sort(begin(es), end(es), [&](const Edge< T > &a, const Edge< T > &b) {
        return a.to < b.to;
      });
    }
    const int N = (int) g.size();
    dists.resize(N);
    for(int i = 0; i < N; i++) {
      if((int) g[i].size() >= N / 2 - 1) {
        dists[i] = complement_bfs(i);
      }
    }
  }

  T query(int s, int t) const {
    if(!dists[s].empty()) {
      return dists[s][t];
    } else if(!dists[t].empty()) {
      return dists[t][s];
    } else if([&]() -> bool {
      int ok = 0, ng = (int) g[s].size();
      while(ng - ok > 1) {
        int mid = (ok + ng) >> 1;
        if(g[s][mid].to <= t) ok = mid;
        else ng = mid;
      }
      return ok < (int) g[s].size() and g[s][ok].to == t;
    }()) {
      return 2;
    } else {
      return 1;
    }
  }

  vector< T > complement_bfs(int s) {
    vector< T > dist(g.size(), -1);
    queue< int > que;
    dist[s] = 0;
    que.emplace(s);
    vector< int > not_visited;
    for(int i = 0; i < g.size(); i++) {
      if(s != i) {
        not_visited.emplace_back(i);
      }
    }
    while(!que.empty()) {
      int idx = que.front();
      que.pop();
      int ptr = 0;
      vector< int > nxt_visited;
      for(auto &to : not_visited) {
        while(ptr < (int) g[idx].size() and g[idx][ptr].to < to) {
          ++ptr;
        }
        if(ptr < (int) g[idx].size() and to == g[idx][ptr].to) {
          nxt_visited.emplace_back(to);
        } else {
          dist[to] = dist[idx] + 1;
          que.emplace(to);
        }
      }
      not_visited = move(nxt_visited);
    }
    return dist;
  }
};
