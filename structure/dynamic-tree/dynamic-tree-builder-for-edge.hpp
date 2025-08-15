template <template <typename> typename DynamicTree, typename TreeDPInfo>
struct DynamicTreeBuilderForEdge : DynamicTree<TreeDPInfo> {
 private:
  using DT = DynamicTree<TreeDPInfo>;
  using Info = typename TreeDPInfo::Info;

  int n, e_sz;
  vector<vector<pair<int, int> > > g;

 public:
  using DT::alloc;
  using DT::link;

  vector<typename DT::NP> vs, es;

  explicit DynamicTreeBuilderForEdge(int n)
      : n(n), g(n), vs(n), es(n), e_sz(0) {}

  void set_vertex(int u, const Info& info) {
    assert(0 <= u and u < n);
    vs[u] = this->alloc(info);
  }

  void add_edge(int u, int v, const Info& info, int id = -1) {
    assert(0 <= u and u < n);
    assert(0 <= v and v < n);
    assert(u != v);
    if (id == -1) id = e_sz++;
    assert(0 <= id and id < n);
    g[u].emplace_back(v, id);
    g[v].emplace_back(u, id);
    es[id] = alloc(info);
  }

  void build(int r = 0) {
    vector<pair<int, int> > que;
    que.reserve(n);
    que.emplace_back(r, -1);
    while (not que.empty()) {
      auto [u, p] = que.back();
      que.pop_back();
      for (auto& [v, id] : g[u]) {
        if (v == p) continue;
        que.emplace_back(v, u);
        link(es[id], vs[u]);
        link(vs[v], es[id]);
      }
    }
  }
};
