template <template <typename> typename DynamicTree, typename TreeDPInfo>
struct DynamicTreeBuilderForVertex : DynamicTree<TreeDPInfo> {
 private:
  using DT = DynamicTree<TreeDPInfo>;
  using Info = typename TreeDPInfo::Info;

  int n;
  vector<vector<int> > g;

 public:
  using DT::alloc;
  using DT::link;

  vector<typename DT::NP> vs;

  explicit DynamicTreeBuilderForVertex(int n) : n(n), g(n), vs(n) {}

  void set_vertex(int u, const Info& info) {
    assert(0 <= u and u < n);
    vs[u] = this->alloc(info);
  }

  void add_edge(int u, int v) {
    assert(0 <= u and u < n);
    assert(0 <= v and v < n);
    assert(u != v);
    g[u].emplace_back(v);
    g[v].emplace_back(u);
  }

  void build(int r = 0) {
    vector<pair<int, int> > que;
    que.reserve(n);
    que.emplace_back(r, -1);
    while (not que.empty()) {
      auto [u, p] = que.back();
      que.pop_back();
      for (auto& v : g[u]) {
        if (v == p) continue;
        que.emplace_back(v, u);
        link(vs[v], vs[u]);
      }
    }
  }
};
