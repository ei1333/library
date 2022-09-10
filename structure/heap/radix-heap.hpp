template< typename key_t, typename val_t >
struct RadixHeap {
  static constexpr int bit = sizeof(key_t) * 8;
  array< vector< pair< key_t, val_t > >, bit > vs;

  size_t sz;
  key_t last;

  RadixHeap() : sz(0), last(0) {}

  bool empty() const { return sz == 0; }

  size_t size() const { return sz; }

  inline int getbit(int a) const {
    return a ? bit - __builtin_clz(a) : 0;
  }

  inline int getbit(int64_t a) const {
    return a ? bit - __builtin_clzll(a) : 0;
  }

  void push(const key_t &key, const val_t &val) {
    sz++;
    vs[getbit(key ^ last)].emplace_back(key, val);
  }

  pair< key_t, val_t > pop() {
    if(vs[0].empty()) {
      int idx = 1;
      while(vs[idx].empty()) idx++;
      last = min_element(vs[idx].begin(), vs[idx].end())->first;
      for(auto &p:vs[idx]) vs[getbit(p.first ^ last)].emplace_back(p);
      vs[idx].clear();
    }
    --sz;
    auto res = vs[0].back();
    vs[0].pop_back();
    return res;
  }
};
