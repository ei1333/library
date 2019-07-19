template< typename T, typename F >
T boruvka(int N, F f) {
  vector< int > rev(N), belong(N);
  UnionFind uf(N);
  T ret = T();
  while(uf.size(0) != N) {
    int ptr = 0;
    for(int i = 0; i < N; i++) {
      if(uf.find(i) == i) {
        belong[i] = ptr++;
        rev[belong[i]] = i;
      }
    }
    for(int i = 0; i < N; i++) {
      belong[i] = belong[uf.find(i)];
    }
    auto v = f(ptr, belong);
    bool update = false;
    for(int i = 0; i < ptr; i++) {
      if(~v[i].second && uf.unite(rev[i], rev[v[i].second])) {
        ret += v[i].first;
        update = true;
      }
    }
    if(!update) return -1; // notice!!
  }
  return ret;
}
