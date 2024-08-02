#include "../../graph/tree/heavy-light-decomposition.hpp"
#include "../../structure/segment-tree/lazy-segment-tree.hpp"
#include "../others/extreme-vertex-set.hpp"

template <typename T>
struct GlobalMinimumCutofDynamicStarAugmentedGraph {
 private:
  int n{};
  HeavyLightDecomposition<T> hld;
  vector<T> cur;

  struct RangeAddRangeMin {
    using S = T;
    using F = T;
    static constexpr S op(const S &a, const S &b) { return min(a, b); }
    static constexpr S e() { return numeric_limits<T>::max(); }
    static constexpr F mapping(const S &x, const F &f) { return x + f; }
    static constexpr F composition(const F &f, const F &g) { return f + g; }
    static constexpr F id() { return {0}; }
  };

  LazySegmentTree<RangeAddRangeMin> seg;

 public:
  GlobalMinimumCutofDynamicStarAugmentedGraph() = default;

  explicit GlobalMinimumCutofDynamicStarAugmentedGraph(int n,
                                                       const Edges<T> &es)
      : n(n),
        hld(extreme_vertex_set(n, es)),
        cur(n),
        seg(RangeAddRangeMin(), 2 * n - 1) {
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
