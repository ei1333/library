template< typename T >
struct WeightedUnionFind {
  vector< int > data;
  vector< T > ws;

  WeightedUnionFind() {}

  WeightedUnionFind(int sz) : data(sz, -1), ws(sz) {}

  int find(int k) {
    if(data[k] < 0) return k;
    auto par = find(data[k]);
    ws[k] += ws[data[k]];
    return data[k] = par;
  }

  T weight(int t) {
    find(t);
    return ws[t];
  }

  bool unite(int x, int y, T w) {
    w += weight(x);
    w -= weight(y);
    x = find(x), y = find(y);
    if(x == y) return false;
    if(data[x] > data[y]) {
      swap(x, y);
      w *= -1;
    }
    data[x] += data[y];
    data[y] = x;
    ws[y] = w;
    return true;
  }

  T diff(int x, int y) {
    return weight(y) - weight(x);
  }
};
