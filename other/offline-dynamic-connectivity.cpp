struct OfflineDynamicConnectivity {
  using edge = pair< int, int >;

  UnionFindUndo uf;
  int V, Q, segsz;
  vector< vector< edge > > seg;
  int comp;

  vector< pair< pair< int, int >, edge > > pend;
  map< edge, int > cnt, appear;

  OfflineDynamicConnectivity(int V, int Q) : uf(V), V(V), Q(Q), comp(V) {
    segsz = 1;
    while(segsz < Q) segsz <<= 1;
    seg.resize(2 * segsz - 1);
  }

  void insert(int idx, int s, int t) {
    auto e = minmax(s, t);
    if(cnt[e]++ == 0) appear[e] = idx;
  }

  void erase(int idx, int s, int t) {
    auto e = minmax(s, t);
    if(--cnt[e] == 0) pend.emplace_back(make_pair(appear[e], idx), e);
  }

  void add(int a, int b, const edge &e, int k, int l, int r) {
    if(r <= a || b <= l) return;
    if(a <= l && r <= b) {
      seg[k].emplace_back(e);
      return;
    }
    add(a, b, e, 2 * k + 1, l, (l + r) >> 1);
    add(a, b, e, 2 * k + 2, (l + r) >> 1, r);
  }

  void add(int a, int b, const edge &e) {
    add(a, b, e, 0, 0, segsz);
  }

  void build() {
    for(auto &p : cnt) {
      if(p.second > 0) pend.emplace_back(make_pair(appear[p.first], Q), p.first);
    }
    for(auto &s : pend) {
      add(s.first.first, s.first.second, s.second);
    }
  }

  int run(const function< void(int) > &f, int k = 0) {
    int add = 0;
    for(auto &e : seg[k]) {
      add += uf.unite(e.first, e.second);
    }
    comp -= add;
    if(k < segsz - 1) {
      run(f, 2 * k + 1);
      run(f, 2 * k + 2);
    } else if(k - (segsz - 1) < Q) {
      int query_index = k - (segsz - 1);
      f(query_index);
    }
    for(auto &e : seg[k]) {
      uf.undo();
    }
    comp += add;
  }
};
