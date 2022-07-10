#pragma once

#include "../../structure/union-find/union-find.hpp"
#include "dinic.hpp"

/**
 * @brief BurnBury(燃やす埋める)
 */
template< typename T, bool minimize = true >
struct BurnBury {
private:
  using MaxFlow = Dinic< T >;
  using UF = UnionFind;
  using arr2 = array< T, 2 >;
  using arr4 = array< T, 4 >;

  int n;
  T alpha;
  vector< arr2 > theta;
  vector< map< int, arr4 > > phi;

public:
  explicit BurnBury(int n) : n{n}, alpha{}, theta(n), phi(n) {}

  void add_cost(T cost) {
    if(not minimize) cost *= -1;
    alpha += cost;
  }

  void add_cost(int x, T cost) {
    if(not minimize) cost *= -1;
    int a = max(~x, x);
    theta[a][x >= 0] += cost;
  }

  void add_cost(int x, int y, T cost) {
    assert(x != y);
    if(not minimize) cost *= -1;
    int a = max(~x, x), b = max(~y, y);
    if(a < b) phi[a][b][((x >= 0) << 1) | (y >= 0)] += cost;
    else phi[b][a][((y >= 0) << 1) | (x >= 0)] += cost;
  }

  optional< T > solve() {
    vector< int > flip(2 * n, -1);
    {
      UF uf(n + n);
      for(int i = 0; i < n; i++) {
        for(auto&[j, cs]: phi[i]) {
          T c = -cs[0] + cs[1] + cs[2] - cs[3];
          if(c < 0) {
            uf.unite(i, j + n);
            uf.unite(i + n, j);
          } else {
            uf.unite(i, j);
            uf.unite(i + n, j + n);
          }
        }
      }
      for(int i = 0; i < n; i++) {
        int x = uf.find(i);
        int y = uf.find(i + n);
        if(x == y) return {};
        if(flip[x] < 0) {
          flip[x] = 0;
          flip[y] = 1;
        }
      }
      for(int i = 0; i < n; i++) {
        if(flip[i] < 0) {
          flip[i] = flip[uf.find(i)];
        }
      }
      flip.resize(n);
    }
    {
      for(int i = 0; i < n; i++) {
        for(auto&[j, cs]: phi[i]) {
          if(flip[i]) {
            swap(cs[0], cs[2]);
            swap(cs[1], cs[3]);
          }
          if(flip[j]) {
            swap(cs[0], cs[1]);
            swap(cs[2], cs[3]);
          }
          T c = -cs[0] + cs[1] + cs[2] - cs[3];
          alpha += cs[0];
          theta[i][not flip[i]] += cs[2] - cs[0];
          theta[j][not flip[j]] += cs[3] - cs[2];
          cs[1] = c;
          cs[0] = cs[2] = cs[3] = 0;
        }
      }
    }
    {
      for(int i = 0; i < n; i++) {
        auto &cs = theta[i];
        if(flip[i]) {
          swap(cs[0], cs[1]);
        }
        if(cs[0] <= cs[1]) {
          alpha += cs[0];
          cs[1] -= cs[0];
          cs[0] = 0;
        } else {
          alpha += cs[1];
          cs[0] -= cs[1];
          cs[1] = 0;
        }
      }
    }
    MaxFlow flow(n + 2);
    int s = n, t = n + 1;
    {
      for(int i = 0; i < n; i++) {
        auto &cs = theta[i];
        if(cs[1] > 0) {
          flow.add_edge(i, t, cs[1]);
        }
        if(cs[0] > 0) {
          flow.add_edge(s, i, cs[0]);
        }
      }
      for(int i = 0; i < n; i++) {
        for(auto&[j, cs]: phi[i]) {
          if(cs[2] > 0) {
            flow.add_edge(i, j, cs[2]);
          }
          if(cs[1] > 0) {
            flow.add_edge(j, i, cs[1]);
          }
        }
      }
    }
    return flow.max_flow(s, t) + alpha;
  }
};
