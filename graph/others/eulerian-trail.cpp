/**
 * @brief Eulerian-Trail(オイラー路)
 */
template< typename T >
Edges< T > eulerian_trail(Edges< T > &es, bool directed, int s = -1) {
  int V = 0;
  for(auto &e : es) V = max(V, max(e.to, e.from) + 1);
  vector< vector< pair< Edge< T >, int > > > g(V);
  for(auto e : es) {
    int sz_to = (int) g[e.to].size();
    g[e.from].emplace_back(e, sz_to);
    if(!directed) {
      int sz_src = (int) g[e.from].size() - 1;
      swap(e.from, e.to);
      g[e.from].emplace_back(e, sz_src);
    }
  }
  if(directed) {
    vector< int > deg(V), used(V);
    for(auto &e : es) deg[e.from]++, used[e.from] = true;
    for(auto &e : es) deg[e.to]--, used[e.to] = true;
    vector< int > latte, malta;
    for(int i = 0; i < V; i++) {
      if(abs(deg[i]) >= 2) return {};
      else if(deg[i] == 1) latte.emplace_back(i);
      else if(deg[i] == -1) malta.emplace_back(i);
    }
    if(latte.size() > 1 || malta.size() > 1) return {};
    if(s != -1 && !latte.empty() && latte[0] != s) return {};
    if(s == -1) {
      for(int i = 0; i < V; i++) {
        if(used[i]) s = i;
      }
      if(!latte.empty()) s = latte[0];
    }
  } else {
    vector< int > odd;
    for(int i = 0; i < V; i++) {
      if(g[i].size() & 1) odd.emplace_back(i);
    }
    if(odd.size() > 2) return {};
    if(s != -1 && odd[0] != s && odd[1] != s) return {};
    if(s == -1) {
      for(int i = 0; i < V; i++) {
        if(g[i].size()) s = i;
      }
      if(!odd.empty()) s = odd[0];
    }
  }
  vector< Edge< T > > ord;
  stack< pair< int, Edge< T > > > st;
  st.emplace(s, Edge< T >(-1, -1));
  while(st.size()) {
    int idx = st.top().first;
    if(g[idx].empty()) {
      ord.emplace_back(st.top().second);
      st.pop();
    } else {
      auto e = g[idx].back();
      g[idx].pop_back();
      if(e.second == -1) continue;
      if(!directed) g[e.first.to][e.second].second = -1;
      st.emplace(e.first.to, e.first);
    }
  }
  ord.pop_back();
  reverse(begin(ord), end(ord));
  if(ord.size() != es.size()) return {};
  return ord;
}
