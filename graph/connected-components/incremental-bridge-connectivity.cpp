/**
 * @brief Incremental-Bridge-Connectivity
 * @see https://scrapbox.io/data-structures/Incremental_Bridge-Connectivity
 */
struct IncrementalBridgeConnectivity {
private:
  UnionFind cc, bcc;
  vector< int > bbf;

  int size() {
    return bbf.size();
  }

  int par(int x) {
    return bbf[x] == size() ? size() : bcc.find(bbf[x]);
  }

  int lca(int x, int y) {
    unordered_set< int > used;
    for(;;) {
      if(x != size()) {
        if(!used.insert(x).second) return x;
        x = par(x);
      }
      swap(x, y);
    }
  }

  void compress(int x, int y) {
    while(bcc.find(x) != bcc.find(y)) {
      int nxt = par(x);
      bbf[x] = bbf[y];
      bcc.unite(x, y);
      x = nxt;
    }
  }

  void link(int x, int y) {
    int v = x, pre = y;
    while(v != size()) {
      int nxt = par(v);
      bbf[v] = pre;
      pre = v;
      v = nxt;
    }
  }

public:
  explicit IncrementalBridgeConnectivity(int sz) : cc(sz), bcc(sz), bbf(sz, sz) {}

  int find(int k) {
    return bcc.find(k);
  }

  void add_edge(int x, int y) {
    x = bcc.find(x);
    y = bcc.find(y);
    if(cc.find(x) == cc.find(y)) {
      int w = lca(x, y);
      compress(x, w);
      compress(y, w);
    } else {
      if(cc.size(x) > cc.size(y)) swap(x, y);
      link(x, y);
      cc.unite(x, y);
    }
  }
};
