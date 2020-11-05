/**
 * @brief RMQ-Lowest-Common-Ancestor(最小共通祖先)
 */
template< typename T = int >
struct RMQLowestCommonAncestor : Graph< T > {
public:
  using Graph< T >::Graph;
  using Graph< T >::g;

  void build(int root = 0) {
    ord.reserve(g.size() * 2 - 1);
    dep.reserve(g.size() * 2 - 1);
    in.resize(g.size());
    dfs(root, -1, 0);
    build_sparse_table();
  }

  int lca(int x, int y) const {
    if(in[x] > in[y]) swap(x, y);
    return x == y ? x : ord[rmq(in[x], in[y])];
  }

private:
  vector< int > ord, dep, in;
  vector< vector< int > > st;
  vector< char > lg;

  inline int chmin(int x, int y) const { return dep[x] < dep[y] ? x : y; }

  void build_sparse_table() {
    int b = 0;
    while((1 << b) <= dep.size()) ++b;
    st.assign(b, vector< T >(1 << b));
    lg.resize(dep.size() + 1);
    for(int i = 0; i <= dep.size(); i++) {
      lg[i] = 31 - __builtin_clz(i);
    }
    for(int i = 0; i < dep.size(); i++) {
      st[0][i] = i;
    }
    for(int i = 1; i < b; i++) {
      for(int j = 0; j + (1 << i) <= (1 << b); j++) {
        st[i][j] = chmin(st[i - 1][j], st[i - 1][j + (1 << (i - 1))]);
      }
    }
  }

  inline T rmq(int l, int r) const // [l, r)
  {
    auto b = lg[r - l];
    return chmin(st[b][l], st[b][r - (1 << b)]);
  }

  void dfs(int idx, int par, int d) {
    in[idx] = (int) ord.size();
    ord.emplace_back(idx);
    dep.emplace_back(d);
    for(auto &to : g[idx]) {
      if(to != par) {
        dfs(to, idx, d + 1);
        ord.emplace_back(idx);
        dep.emplace_back(d);
      }
    }
  }
};
