#include "../../graph/tree/heavy-light-decomposition.hpp"
#include "../../structure/segment-tree/lazy-segment-tree.hpp"
#include "../others/extreme-vertex-set.hpp"

template <typename T>
struct GlobalMinimumCutofDynamicStarAugmentedGraph {
 private:
  function<T(T, T)> f = [](T a, T b) -> T { return min(a, b); };
  function<T(T, T)> g = [](T a, T b) -> T { return a + b; };

  int n{};
  HeavyLightDecomposition<T> hld;
  vector<T> cur;
  LazySegmentTree<T, T, decltype(f), decltype(g), decltype(g)> seg;

 public:
  GlobalMinimumCutofDynamicStarAugmentedGraph() = default;

  explicit GlobalMinimumCutofDynamicStarAugmentedGraph(int n,
                                                       const Edges<T> &es)
      : n(n),
        hld(extreme_vertex_set(n, es)),
        cur(n),
        seg(2 * n - 1, f, g, g, numeric_limits<T>::max(), T()) {
    hld.build((int)hld.size() - 1);
    vector<int64> vs(2 * n - 1);
    for (int i = 0; i < 2 * n - 1; i++) {
      for (auto &e : hld[i]) {
        vs[hld.in[e.to]] = e.cost;
      }
    }
    seg.build(vs);
  }

  T update(int v, T cost) {
    assert(0 <= v and v < n);
    hld.add(v, (int)hld.size() - 1,
            [&](int l, int r) { seg.apply(l, r, cost - cur[v]); });
    cur[v] = cost;
    return seg.all_prod();
  }
};
