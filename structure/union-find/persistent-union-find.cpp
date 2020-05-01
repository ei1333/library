/*
 * @brief Persistent-Union-Find(永続Union-Find)
 */
struct PersistentUnionFind {
  PersistentArray< int, 3 > data;

  PersistentUnionFind() {}

  PersistentUnionFind(int sz) {
    data.build(vector< int >(sz, -1));
  }

  int find(int k) {
    int p = data.get(k);
    return p >= 0 ? find(p) : k;
  }

  int size(int k) {
    return (-data.get(find(k)));
  }

  bool unite(int x, int y) {
    x = find(x);
    y = find(y);
    if(x == y) return false;
    auto u = data.get(x);
    auto v = data.get(y);

    if(u < v) {
      auto a = data.mutable_get(x);
      *a += v;
      auto b = data.mutable_get(y);
      *b = x;
    } else {
      auto a = data.mutable_get(y);
      *a += u;
      auto b = data.mutable_get(x);
      *b = y;
    }
    return true;
  }
};
