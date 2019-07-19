template< typename T >
T kruskal(Edges< T > &edges, int V) {
  sort(begin(edges), end(edges), [](const edge< T > &a, const edge< T > &b) {
    return (a.cost < b.cost);
  });
  UnionFind tree(V);
  T ret = 0;
  for(auto &e : edges) {
    if(tree.unite(e.src, e.to)) ret += e.cost;
  }
  return (ret);
}
