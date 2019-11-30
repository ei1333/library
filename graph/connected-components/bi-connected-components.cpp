template< typename G >
struct BiConnectedComponents : LowLink< G > {
  using LL = LowLink< G >;
 
  vector< int > used;
  vector< vector< pair< int, int > > > bc;
  vector< pair< int, int > > tmp;
 
  BiConnectedComponents(const G &g) : LL(g) {}
 
  void dfs(int idx, int par) {
    used[idx] = true;
    for(auto &to : this->g[idx]) {
      if(to == par) continue;
      if(!used[to] || this->ord[to] < this->ord[idx]) {
        tmp.emplace_back(minmax(idx, to));
      }
      if(!used[to]) {
        dfs(to, idx);
        if(this->low[to] >= this->ord[idx]) {
          bc.emplace_back();
          for(;;) {
            auto e = tmp.back();
            bc.back().emplace_back(e);
            tmp.pop_back();
            if(e.first == min(idx, to) && e.second == max(idx, to)) {
              break;
            }
          }
        }
      }
    }
  }
 
  void build() override {
    LL::build();
    used.assign(this->g.size(), 0);
    for(int i = 0; i < used.size(); i++) {
      if(!used[i]) dfs(i, -1);
    }
  }
};
