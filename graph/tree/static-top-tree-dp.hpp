#include "static-top-tree.hpp"

template <typename TreeDPInfo, typename G>
struct StaticTopTreeDP {
  using Path = typename TreeDPInfo::Path;
  using Point = typename TreeDPInfo::Point;

  using STT = StaticTopTree<G>;

  const STT &g;

  const TreeDPInfo &info;

  explicit StaticTopTreeDP(const STT &g, const TreeDPInfo &info)
      : g(g), info(info) {
    dp.resize(g.size());
    dfs(g.root);
  }

  Path update_vertex(int u) {
    while (u != -1) {
      modify(u);
      u = g[u].p;
    }
    return get<Path>(dp[g.root]);
  }

  Path update_edge(int e) { return update_vertex(g.edge_to_vs[e]); }

 private:
  vector<variant<Point, Path> > dp;

  void modify(int k) {
    switch (g[k].op) {
      case STT::Vertex:
        dp[k] = info.vertex(k);
        return;
      case STT::Compress:
        dp[k] = info.compress(get<Path>(dp[g[k].l]), get<Path>(dp[g[k].r]),
                              g[k].e_id);
        return;
      case STT::Rake:
        dp[k] = info.rake(get<Point>(dp[g[k].l]), get<Point>(dp[g[k].r]));
        return;
      case STT::AddEdge:
        dp[k] = info.add_edge(get<Path>(dp[g[k].l]), g[k].e_id);
        return;
      case STT::AddVertex:
        dp[k] = info.add_vertex(get<Point>(dp[g[k].l]), k);
        return;
    }
  }

  void dfs(int u) {
    if (u == -1) return;
    dfs(g[u].l);
    dfs(g[u].r);
    modify(u);
  }
};

/*
struct TreeDPInfo {
  struct Point {};
  struct Path {};

  vector< int > A;

  TreeDPInfo(int n): A(n) {}

  Path vertex(int u) const {};
  Path add_vertex(Point d, int u) const {}
  Point add_edge(Path d, int e) const {}
  Point rake(Point l, Point r) const {}
  Path compress(Path p, Path c, int e) const {}
};
*/
