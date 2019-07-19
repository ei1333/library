struct BipartiteGraph : UnionFind
{
  vector< int > color;

  BipartiteGraph(int v) : color(v + v, -1), UnionFind(v + v) {}

  bool bipartite_graph_coloring()
  {
    for(int i = 0; i < color.size() / 2; i++) {
      int a = find(i);
      int b = find(i + (int) color.size() / 2);
      if(a == b) return (false);
      if(color[a] < 0) color[a] = 0, color[b] = 1;
    }
    return (true);
  }

  bool operator[](int k)
  {
    return (bool(color[find(k)]));
  }
};
