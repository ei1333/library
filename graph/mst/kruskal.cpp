template< typename T >
struct MinimumSpanningTree {
  T cost;
  Edges< T > edges;
};

template< typename T >
MinimumSpanningTree< T > kruskal(Edges< T > &edges, int V) {
  sort(begin(edges), end(edges), [](const edge< T > &a, const edge< T > &b) {
    return a.cost < b.cost;
  });
  UnionFind tree(V);
  T total = T();
  Edges< T > es;
  for(auto &e : edges) {
    if(tree.unite(e.src, e.to)) {
      es.emplace_back(e);
      total += e.cost;
    }
  }
  return {total, es};
}
