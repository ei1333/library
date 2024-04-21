#pragma once

#include "../graph-template.hpp"

/**
 * @brief Namori Graph
 * 
 */
template< typename T = int >
struct NamoriGraph : Graph< T > {
public:
  using Graph< T >::Graph;
  using Graph< T >::g;

  vector< Graph< T > > forest;
  Edges< T > loop_edges;

  struct Info {
    int tree_id, id;
  };

  Info operator[](const int &k) const {
    return (Info) {mark_id[k], id[k]};
  }

  int inv(int tree_id, int k) {
    return iv[tree_id][k];
  }

  void build() {
    int n = (int) g.size();
    vector< int > deg(n), used(n);
    queue< int > que;
    for(int i = 0; i < n; i++) {
      deg[i] = (int) g[i].size();
      if(deg[i] == 1) {
        que.emplace(i);
        used[i] = true;
      }
    }
    while(not que.empty()) {
      int idx = que.front();
      que.pop();
      for(auto &e : g[idx]) {
        if(used[e.to]) {
          continue;
        }
        --deg[e.to];
        if(deg[e.to] == 1) {
          que.emplace(e.to);
          used[e.to] = true;
        }
      }
    }
    int mx = 0;
    for(auto &edges : g) {
      for(auto &e : edges) mx = max(mx, e.idx);
    }
    vector< int > edge_used(mx + 1);
    vector< int > loop;
    for(int v = 0; v < n; v++) {
      if(!used[v]) {
        for(bool update = true; update;) {
          update = false;
          loop.emplace_back(v);
          for(auto &e : g[v]) {
            if(used[e.to] or edge_used[e.idx]) {
              continue;
            }
            edge_used[e.idx] = true;
            loop_edges.emplace_back(v, e.to, e.cost, e.idx);
            v = e.to;
            update = true;
            break;
          }
        }
        break;
      }
    }
    loop.pop_back();
    mark_id.resize(n);
    id.resize(n);
    for(int i = 0; i < (int) loop.size(); i++) {
      int pre = loop[(i + loop.size() - 1) % loop.size()];
      int nxt = loop[(i + 1) % loop.size()];
      int sz = 0;
      mark_id[loop[i]] = i;
      iv.emplace_back();
      id[loop[i]] = sz++;
      iv.back().emplace_back(loop[i]);
      for(auto &e : g[loop[i]]) {
        if(e.to != pre and e.to != nxt) {
          mark_dfs(e.to, loop[i], i, sz);
        }
      }
      Graph< T > tree(sz);
      for(auto &e : g[loop[i]]) {
        if(e.to != pre and e.to != nxt) {
          tree.g[id[loop[i]]].emplace_back(id[loop[i]], id[e.to], e.cost, e.idx);
          tree.g[id[e.to]].emplace_back(id[e.to], id[loop[i]], e.cost, e.idx);
          build_dfs(e.to, loop[i], tree);
        }
      }
      forest.emplace_back(tree);
    }
  }

private:
  vector< vector< int > > iv;
  vector< int > mark_id, id;

  void mark_dfs(int idx, int par, int k, int &l) {
    mark_id[idx] = k;
    id[idx] = l++;
    iv.back().emplace_back(idx);
    for(auto &e : g[idx]) {
      if(e.to != par) {
        mark_dfs(e.to, idx, k, l);
      }
    }
  }

  void build_dfs(int idx, int par, Graph< T > &tree) {
    for(auto &e : g[idx]) {
      if(e.to != par) {
        tree.g[id[idx]].emplace_back(id[idx], id[e.to], e.cost, e.idx);
        tree.g[id[e.to]].emplace_back(id[e.to], id[idx], e.cost, e.idx);
        build_dfs(e.to, idx, tree);
      }
    }
  }
};
