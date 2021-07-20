#pragma once

#include "../graph-template.hpp"
#include "../connected-components/bi-connected-components.hpp"

/**
 * @brief Block Cut Tree
 * @see https://ei1333.hateblo.jp/entry/2020/03/25/010057
 */
template< typename T = int >
struct BlockCutTree : BiConnectedComponents< T > {
public:
  using BiConnectedComponents< T >::BiConnectedComponents;
  using BiConnectedComponents< T >::g;
  using BiConnectedComponents< T >::articulation;
  using BiConnectedComponents< T >::bc;

  vector< int > rev;
  vector< vector< int > > group;
  Graph< T > tree;

  explicit BlockCutTree(const Graph< T > &g) : Graph< T >(g) {}

  int operator[](const int &k) const {
    return rev[k];
  }

  void build() override {
    BiConnectedComponents< T >::build();
    rev.assign(g.size(), -1);
    int ptr = (int) bc.size();
    for(auto &idx : articulation) {
      rev[idx] = ptr++;
    }
    vector< int > last(ptr, -1);
    tree = Graph< T >(ptr);
    for(int i = 0; i < (int) bc.size(); i++) {
      for(auto &e : bc[i]) {
        for(auto &ver : {e.from, e.to}) {
          if(rev[ver] >= (int) bc.size()) {
            if(exchange(last[rev[ver]], i) != i) {
              tree.add_edge(rev[ver], i, e.cost);
            }
          } else {
            rev[ver] = i;
          }
        }
      }
    }
    group.resize(ptr);
    for(int i = 0; i < (int) g.size(); i++) {
      group[rev[i]].emplace_back(i);
    }
  }
};
