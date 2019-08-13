template< typename G >
G convert_rooted_tree(const G &g, int r = 0) {
  int N = (int) g.size();
  G rg(N);
  vector< int > v(N);
  v[r] = 1;
  queue< int > que;
  que.emplace(r);
  while(!que.empty()) {
    auto p = que.front();
    que.pop();
    for(auto &to : g[p]) {
      if(v[to] == 0) {
        v[to] = 1;
        que.emplace(to);
        rg[p].emplace_back(to);
      }
    }
  }
  return rg;
}
