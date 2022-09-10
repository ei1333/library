struct PartiallyPersistentUnionFind {
  vector< int > data;
  vector< int > last;
  vector< vector< pair< int, int > > > add;

  PartiallyPersistentUnionFind() {}

  PartiallyPersistentUnionFind(int sz) : data(sz, -1), last(sz, 1e9), add(sz) {
    for(auto &vs : add) vs.emplace_back(-1, -1);
  }

  bool unite(int t, int x, int y) {
    x = find(t, x);
    y = find(t, y);
    if(x == y) return false;
    if(data[x] > data[y]) swap(x, y);
    data[x] += data[y];
    add[x].emplace_back(t, data[x]);
    data[y] = x;
    last[y] = t;
    return true;
  }

  int find(int t, int x) {
    if(t < last[x]) return x;
    return find(t, data[x]);
  }

  int size(int t, int x) {
    x = find(t, x);
    return -prev(lower_bound(begin(add[x]), end(add[x]), make_pair(t, 0)))->second;
  }
};
