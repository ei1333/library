template <typename G>
struct StaticTopTree {
  enum OpType { Vertex, AddVertex, AddEdge, Rake, Compress };

  struct Node {
    OpType op;

    int l, r, p;

    int e_id;

    Node(OpType op, int l, int r) : op{op}, l{l}, r{r}, p{-1}, e_id{-1} {}
  };

  vector<Node> vs;

  vector<int> edge_to_vs;

  int root;

  explicit StaticTopTree(G &g, int r = 0) : g(g), edge_to_vs(g.size() - 1) {
    int e_sz = 0;
    for (int i = 0; i < g.size(); i++) e_sz += g[i].size();
    if (e_sz + 1 != g.size()) {
      throw std::runtime_error("`g` must be a directed tree.");
    }
    dfs(r);

    vs.assign(g.size(), {Vertex, -1, -1});
    vs.reserve(g.size() * 4);
    root = compress(r).first;
    vs.shrink_to_fit();
  }

  const Node &operator[](int k) const { return vs[k]; }

  size_t size() const { return vs.size(); }

 private:
  G &g;

  using P = pair<int, int>;

  int dfs(int u) {
    int size = 1, heavy = 0;
    for (auto &v : g[u]) {
      int subtree_size = dfs(v);
      size += subtree_size;
      if (heavy < subtree_size) {
        heavy = subtree_size;
        swap(v, g[u][0]);
      }
    }
    return size;
  }

  int make_node(OpType t, int l, int r, int k = -1) {
    if (k == -1) {
      k = (int)vs.size();
      vs.emplace_back(t, l, r);
    } else {
      vs[k] = {t, l, r};
    }
    if (l != -1) vs[l].p = k;
    if (r != -1) vs[r].p = k;
    return k;
  }

  P merge_forRake(const vector<P> &a) {
    if (a.size() == 1) return a[0];
    int size_sum = 0;
    for (auto &[_, size] : a) {
      size_sum += size;
    }
    vector<P> b, c;
    for (auto &[it, size] : a) {
      (size_sum > size ? b : c).emplace_back(it, size);
      size_sum -= size * 2;
    }
    auto [l, l_size] = merge_forRake(b);
    auto [r, r_size] = merge_forRake(c);
    return {make_node(Rake, l, r), l_size + r_size};
  }

  P merge_forCompress(const vector<pair<P, int>> &a) {
    if (a.size() == 1) return a[0].first;
    int size_sum = 0;
    for (auto &[it, _] : a) {
      size_sum += it.second;
    }
    vector<pair<P, int>> b, c;
    for (auto &[it, _] : a) {
      (size_sum > it.second ? b : c).emplace_back(it, _);
      size_sum -= it.second * 2;
    }
    auto [l, l_size] = merge_forCompress(b);
    auto [r, r_size] = merge_forCompress(c);
    int idx = make_node(Compress, l, r);
    edge_to_vs[c[0].second] = idx;
    vs[idx].e_id = c[0].second;
    return {idx, l_size + r_size};
  }

  P add_edge(int u, int e_idx) {
    auto [it, size] = compress(u);
    int idx = make_node(AddEdge, it, -1);
    edge_to_vs[e_idx] = idx;
    vs[idx].e_id = e_idx;
    return {idx, size};
  }

  P rake(int u) {
    vector<P> chs;
    for (int j = 1; j < (int)g[u].size(); j++) {
      chs.emplace_back(add_edge(g[u][j].to, g[u][j].idx));
    }
    return merge_forRake(chs);
  }

  P add_vertex(int u) {
    if (g[u].size() < 2) {
      return {make_node(OpType::Vertex, -1, -1, u), 1};
    } else {
      auto [it, size] = rake(u);
      return {make_node(OpType::AddVertex, it, -1, u), size + 1};
    }
  }

  P compress(int u) {
    vector<pair<P, int>> chs{{add_vertex(u), -1}};
    vector<int> ids{-1};
    while (not g[u].empty()) {
      int e_idx = g[u][0].idx;
      u = g[u][0];
      chs.emplace_back(add_vertex(u), e_idx);
    }
    return merge_forCompress(chs);
  }
};
