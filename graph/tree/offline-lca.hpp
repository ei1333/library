#include "../../structure/union-find/union-find.hpp"
#include "../graph-template.hpp"

/**
 * @brief Offline LCA(オフライン最小共通祖先)
 **/
template <typename T>
vector<int> offline_lca(const Graph<T> &g, vector<pair<int, int> > &qs,
                        int root = 0) {
  int n = (int)g.size();
  UnionFind uf(n);
  vector<int> st(n), mark(n), ptr(n), ans(qs.size(), -1);
  int top = 0;
  st[top] = root;
  for (auto &[l, r] : qs) mark[l]++, mark[r]++;
  vector<vector<pair<int, int> > > q(n);
  for (int i = 0; i < n; i++) {
    q[i].reserve(mark[i]);
    mark[i] = -1;
    ptr[i] = (int)g[i].size();
  }
  for (int i = 0; i < qs.size(); i++) {
    q[qs[i].first].emplace_back(qs[i].second, i);
    q[qs[i].second].emplace_back(qs[i].first, i);
  }
  auto run = [&](int u) -> bool {
    while (ptr[u]) {
      int v = g[u][--ptr[u]];
      if (mark[v] == -1) {
        st[++top] = v;
        return true;
      }
    }
    return false;
  };
  while (~top) {
    int u = st[top];
    if (mark[u] == -1) {
      mark[u] = u;
    } else {
      uf.unite(u, g[u][ptr[u]]);
      mark[uf.find(u)] = u;
    }
    if (not run(u)) {
      for (auto &[v, i] : q[u]) {
        if (~mark[v] and ans[i] == -1) {
          ans[i] = mark[uf.find(v)];
        }
      }
      --top;
    }
  }
  return ans;
}
