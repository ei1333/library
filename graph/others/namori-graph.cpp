/**
 * @brief Namori-Graph
 * @docs docs/namori-graph.md
 */
template< typename T = int >
struct NamoriGraph : Graph< T > {
public:
  using Graph< T >::Graph;
  using Graph< T >::g;

  vector< Graph< T > > forest;
  Edges< T > loop_edges;

  struct Info {
    int forest_id, id;
  };

  Info operator[](const int &k) const {
    return (Info) {mark_id[k], id[k]};
  }

  int inv(int forest_id, int k) {
    return iv[forest_id][k];
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
      if(used[v]) {
        continue;
      }
      while(!used[v]) {
        loop.emplace_back(v);
        for(auto &e : g[v]) {
          if(used[e.to] or edge_used[e.idx]) {
            continue;
          }
          loop_edges.emplace_back(loop.size() - 1, loop.size(), e.cost, e.idx);
          v = e.to;
          used[e.to] = true;
          edge_used[e.idx] = true;
          break;
        }
      }
      break;
    }
    loop_edges.back().to = 0;
    mark_id.resize(n);
    id.resize(n);
    int ptr = 0;
    for(int i = 0; i < (int) loop.size(); i++) {
      int pre = loop[(i + loop.size() - 1) % loop.size()];
      int nxt = loop[(i + 1) % loop.size()];
      int sz = 0;
      mark_id[loop[i]] = ptr;
      iv.emplace_back();
      id[loop[i]] = sz++;
      iv.back().emplace_back(loop[i]);
      for(auto &e : g[loop[i]]) {
        if(e.to != pre and e.to != nxt) {
          mark_dfs(e.to, loop[i], ptr, sz);
          build_dfs(e.to, loop[i]);
        }
      }
      Graph< T > tree(sz);
      for(auto &e : g[loop_vers[i]]) {
        if(e.to != pre and e.to != nxt) {
          tree.add_edge(id[loop_vers[i]], id[e.to], e.cost, e.idx);
          build_dfs(e.to, loop_vers[i], tree);
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
        mark_dfs(e.to, idx, k);
      }
    }
  }

  void build_dfs(int idx, int par, Graph< T > &tree) {
    for(auto &e : g[idx]) {
      if(e.to != par) {
        tree.add_edge(id[idx], id[e.to], e.cost, e.idx);
        build_dfs(e.to, idx, tree);
      }
    }
  }
};
