/**
 * @brief Union-Find
 * @docs docs/union-find.md
 */
struct UnionFind {
  vector< int > data;

  UnionFind() = default;

  explicit UnionFind(size_t sz) : data(sz, -1) {}

  bool unite(int x, int y) {
    x = find(x), y = find(y);
    if(x == y) return false;
    if(data[x] > data[y]) swap(x, y);
    data[x] += data[y];
    data[y] = x;
    return true;
  }

  int find(int k) {
    if(data[k] < 0) return (k);
    return data[k] = find(data[k]);
  }

  int size(int k) {
    return -data[find(k)];
  }

  bool same(int x, int y) {
    return find(x) == find(y);
  }

  vector< vector< int > > groups() {
    int n = (int) data.size();
    vector< vector< int > > ret(n);
    for(int i = 0; i < n; i++) {
      ret[find(i)].emplace_back(i);
    }
    ret.erase(remove_if(begin(ret), end(ret), [&](const vector< int > &v) {
      return v.empty();
    }));
    return ret;
  }
};
